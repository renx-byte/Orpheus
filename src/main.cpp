#include "Storage.h"
#include "credentials.h"
#include "index_html.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>

WebServer server(80);

// Global variable to hold current upload base name (without extension)
String currentUploadBaseName = "";

void serve_webpage() { server.send(200, "text/html", index_html); }

// ------------------------------------------------------------
// Legacy chunked upload handlers (kept for backward compatibility)
// ------------------------------------------------------------
void handle_song_upload() {
  HTTPUpload &upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    String song_name = server.header("X-Song-Name");
    int chunk_index = server.header("X-Chunk-Index").toInt();
    Storage::upload_start_sd(song_name, chunk_index);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Storage::upload_write_sd(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Storage::upload_end_sd();
  }
}

void handle_image_upload() {
  HTTPUpload &upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    String image_name = server.header("X-File-Name");
    int chunk_index = server.header("X-Chunk-Index").toInt();
    Storage::upload_image_start_sd(image_name, chunk_index);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Storage::upload_image_write_sd(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Storage::upload_image_end_sd();
  }
}

String sanitizeBaseName(const String &original) {
  // Remove extension
  String base = original;
  int dotIndex = base.lastIndexOf('.');
  if (dotIndex > 0) {
    base = base.substring(0, dotIndex);
  }

  // Replace any character that is NOT alphanumeric, underscore, or hyphen with
  // underscore
  for (size_t i = 0; i < base.length(); i++) {
    char c = base.charAt(i);
    if (!isalnum(c) && c != '_' && c != '-') {
      base.setCharAt(i, '_');
    }
  }

  // Collapse consecutive underscores
  while (base.indexOf("__") >= 0) {
    base.replace("__", "_");
  }

  // Trim leading and trailing underscores
  while (base.startsWith("_")) {
    base.remove(0, 1);
  }
  while (base.endsWith("_")) {
    base.remove(base.length() - 1, 1);
  }

  // Fallback if empty
  if (base.length() == 0) {
    base = "song";
  }
  return base;
}

// ------------------------------------------------------------
// New multipart upload handler (for /api/songs/upload)
// ------------------------------------------------------------
void fixMetadataFilePath(const String &jsonPath, const String &actualBase) {
  // Read the metadata JSON, update file_path, and write back
  if (!SD.exists(jsonPath))
    return;

  File metaFile = SD.open(jsonPath, FILE_READ);
  if (!metaFile) {
    Serial.println("Failed to open metadata for fixing file_path");
    return;
  }

  // Read entire file (metadata is small, so this is safe)
  String jsonContent = "";
  while (metaFile.available()) {
    jsonContent += (char)metaFile.read();
  }
  metaFile.close();

  // Parse JSON
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, jsonContent);
  if (err) {
    Serial.println("Failed to parse metadata JSON for fixing");
    return;
  }

  // Update file_path
  doc["file_path"] = "/songs/" + actualBase + ".mp3";

  // Write back
  File outFile = SD.open(jsonPath, FILE_WRITE);
  if (!outFile) {
    Serial.println("Failed to open metadata for writing fixed file_path");
    return;
  }
  serializeJson(doc, outFile);
  outFile.close();
  Serial.printf("Updated file_path to /songs/%s.mp3\n", actualBase.c_str());
}

void handle_new_upload() {
  HTTPUpload &upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    if (upload.name == "audio") {
      // Use the same sanitization as the frontend
      String base = sanitizeBaseName(upload.filename);
      currentUploadBaseName = base;

      // Check for collision and adjust base name
      String originalBase = base;
      int suffix = 0;
      String fullPath = "/songs/" + base + ".mp3";
      while (SD.exists(fullPath)) {
        suffix++;
        base = originalBase + "_" + String(suffix);
        fullPath = "/songs/" + base + ".mp3";
      }
      // If suffix was added, update currentUploadBaseName
      if (suffix > 0) {
        currentUploadBaseName = base;
      }

      Storage::start_audio_upload(fullPath.c_str());
      Serial.printf("Upload started: audio -> %s\n", fullPath.c_str());
    } else if (upload.name == "metadata") {
      // Use the same base name determined from the audio part
      if (currentUploadBaseName.length() > 0) {
        String fullPath = "/metadata/" + currentUploadBaseName + ".json";
        Storage::start_metadata_upload(fullPath.c_str());
        Serial.printf("Upload started: metadata -> %s\n", fullPath.c_str());
      }
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (upload.name == "audio") {
      Storage::write_audio_chunk(upload.buf, upload.currentSize);
    } else if (upload.name == "metadata") {
      Storage::write_metadata_chunk(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (upload.name == "audio") {
      Storage::end_audio_upload();
      Serial.printf("Upload finished: audio\n");
    } else if (upload.name == "metadata") {
      Storage::end_metadata_upload();
      // Fix the metadata file_path to match the actual saved MP3 name
      String jsonPath = "/metadata/" + currentUploadBaseName + ".json";
      fixMetadataFilePath(jsonPath, currentUploadBaseName);
      Serial.printf("Upload finished: metadata\n");
    }
  }
}

// ------------------------------------------------------------
// GET /api/metadata
// ------------------------------------------------------------
void handle_get_metadata() {
  String json = Storage::get_songs_json();
  server.send(200, "application/json", json);
}

// ------------------------------------------------------------
// GET /api/songs/<filename>
// ------------------------------------------------------------
void handle_stream_song() {
  String uri = server.uri(); // e.g., "/api/songs/My_Song.mp3"
  if (!uri.startsWith("/api/songs/")) {
    server.send(400, "text/plain", "Bad request");
    return;
  }
  String filename = uri.substring(strlen("/api/songs/"));
  if (filename.length() == 0 || filename.indexOf("..") != -1 ||
      !filename.endsWith(".mp3")) {
    server.send(400, "text/plain", "Invalid filename");
    return;
  }
  String path = "/songs/" + filename;
  if (!SD.exists(path)) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  File file = SD.open(path);
  if (!file) {
    server.send(500, "text/plain", "Failed to open file");
    return;
  }
  server.streamFile(file, "audio/mpeg");
  file.close();
}

// ------------------------------------------------------------
// Legacy endpoints (kept for backward compatibility)
// ------------------------------------------------------------
void handle_save_metadata() {
  String body = server.arg("plain");
  JsonDocument json_obj;
  DeserializationError err = deserializeJson(json_obj, body);

  if (err) {
    server.send(400, "application/json",
                "{\"success\":false,\"error\":\"Invalid JSON\"}");
    return;
  }

  bool success = Storage::save_metadata_sd(json_obj);
  if (success) {
    server.send(200, "application/json", "{\"success\":true}");
  } else {
    server.send(500, "application/json",
                "{\"success\":false,\"error\":\"Failed to save metadata\"}");
  }
}

void handle_songs() {
  String json = Storage::get_songs_json();
  server.send(200, "application/json", json);
}

void handle_delete_song() {
  String body = server.arg("plain");
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }
  String filePath = doc["file_path"] | "";
  if (filePath.length() == 0) {
    server.send(400, "application/json", "{\"error\":\"Missing file_path\"}");
    return;
  }
  bool success = Storage::delete_song(filePath);
  if (success) {
    server.send(200, "application/json", "{\"success\":true}");
  } else {
    server.send(500, "application/json", "{\"success\":false}");
  }
}

void handle_download() {
  if (!server.hasArg("path")) {
    server.send(400, "text/plain", "Missing path");
    return;
  }

  String path = server.arg("path");

  if (path.indexOf("..") != -1 || !path.startsWith("/")) {
    server.send(400, "text/plain", "Invalid path");
    return;
  }

  File file = SD.open(path);
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }

  String filename = path.substring(path.lastIndexOf('/') + 1);
  server.sendHeader("Content-Disposition",
                    "attachment; filename=\"" + filename + "\"");
  server.streamFile(file, "application/octet-stream");
  file.close();
}

void handle_image() {
  String uri = server.uri();      // e.g., "/images/Songs/file.png"
  String path = uri.substring(7); // remove "/images" -> "/Songs/file.png"
  if (!path.startsWith("/"))
    path = "/" + path;

  if (path.indexOf("..") != -1) {
    server.send(400, "text/plain", "Invalid path");
    return;
  }

  File imgFile = SD.open(path);
  if (!imgFile) {
    server.send(404, "text/plain", "Image not found");
    return;
  }

  String contentType = "image/jpeg";
  if (path.endsWith(".png"))
    contentType = "image/png";
  else if (path.endsWith(".gif"))
    contentType = "image/gif";

  server.streamFile(imgFile, contentType);
  imgFile.close();
}

void handle_sd_directory() {
  String json = Storage::get_sd_json_structure();
  server.send(200, "application/json", json);
}

void add_handle() {
  String body = server.arg("plain");
  JsonDocument json_obj;
  DeserializationError err = deserializeJson(json_obj, body);
  if (err) {
    server.send(400, "application/json",
                "{\"success\":false,\"error\":\"Invalid JSON\"}");
    return;
  }
  bool success = Storage::add_payload_sd(json_obj);
  if (success) {
    server.send(200, "application/json", "{\"success\":true}");
  } else {
    server.send(500, "application/json",
                "{\"success\":false,\"error\":\"Failed to add payload\"}");
  }
}

void remove_handle() {
  String body = server.arg("plain");
  JsonDocument json_obj;
  DeserializationError err = deserializeJson(json_obj, body);
  if (err) {
    server.send(400, "application/json",
                "{\"success\":false,\"error\":\"Invalid JSON\"}");
    return;
  }
  Storage::remove_payload_sd(json_obj);
  server.send(200, "application/json", "{\"success\":true}");
}

void click_handle() { server.send(200, "text/plain", "OK"); }

void setup() {
  delay(5000);
  Serial.begin(115200);
  Serial.println("Serial Monitor Initialized");

  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.localIP());

  const char *headerKeys[] = {"X-Song-Name", "X-Chunk-Index", "X-Total-Chunks",
                              "X-File-Name", "Content-Length"};
  size_t headerKeysCount = sizeof(headerKeys) / sizeof(char *);
  server.collectHeaders(headerKeys, headerKeysCount);

  // Legacy upload endpoints (still available, but not used by new frontend)
  server.on(
      "/upload_song", HTTP_POST, []() { server.send(200, "text/plain", "OK"); },
      handle_song_upload);
  server.on(
      "/upload_image", HTTP_POST,
      []() { server.send(200, "text/plain", "OK"); }, handle_image_upload);

  // New API endpoints
  server.on(
      "/api/songs/upload", HTTP_POST,
      []() { server.send(200, "text/plain", "OK"); }, handle_new_upload);
  server.on("/api/metadata", HTTP_GET, handle_get_metadata);
  server.on("/api/songs", HTTP_GET, handle_stream_song);

  // Legacy endpoints
  server.on("/save_metadata", HTTP_POST, handle_save_metadata);
  server.on("/songs", HTTP_GET, handle_songs);
  server.on("/delete_song", HTTP_POST, handle_delete_song);
  server.on("/download_file", HTTP_GET, handle_download);
  server.on("/images", HTTP_GET, handle_image);
  server.on("/sd_directory", HTTP_GET, handle_sd_directory);
  server.on("/create_payload", HTTP_POST, add_handle);
  server.on("/remove_payload", HTTP_POST, remove_handle);
  server.on("/selection_click", HTTP_POST, click_handle);

  // Serve main page
  server.on("/", HTTP_GET, serve_webpage);

  Storage::begin();
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() { server.handleClient(); }