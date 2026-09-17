#include "ServerHandler.h"
#include "Storage.h"
#include "compendium.h"
#include "home.h"
#include <Arduino.h>

static WebServer server(80);

// ---------------------------------------------------------------------------
// Page / simple handlers
// ---------------------------------------------------------------------------

void ServerHandler::serve_webpage() {
  server.send(200, "text/html", home_html);
}

void ServerHandler::serve_compendium() {
  server.send(200, "text/html", compendium_html);
}

void ServerHandler::serve_songs_json() {
  String json = Storage::get_songs_json();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", json);
}

void ServerHandler::serve_coverart() {
  String fileName = "";
  if (server.hasArg("file")) {
    fileName = server.arg("file");
  } else {
    String uri = server.uri();
    int queryIndex = uri.indexOf('?');
    if (queryIndex >= 0) {
      String query = uri.substring(queryIndex + 1);
      int filePos = query.indexOf("file=");
      if (filePos >= 0) {
        fileName = query.substring(filePos + 5);
        int ampPos = fileName.indexOf('&');
        if (ampPos >= 0) {
          fileName = fileName.substring(0, ampPos);
        }
        fileName.replace("%20", " ");
      }
    }
  }

  if (fileName.length() == 0) {
    server.send(400, "text/plain", "Missing 'file' parameter");
    return;
  }

  File file = Storage::get_cover_art_file(fileName);
  if (!file) {
    server.send(404, "text/plain", "Cover art not found");
    return;
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Content-Type", "image/png");
  server.sendHeader("Content-Length", String(file.size()));

  const size_t bufferSize = 1024;
  uint8_t buffer[bufferSize];
  while (file.available()) {
    size_t bytesRead = file.read(buffer, bufferSize);
    server.client().write(buffer, bytesRead);
  }
  file.close();
}

void ServerHandler::serve_song_upload_ok() {
  server.send(200, "text/plain", "OK");
}

void ServerHandler::click_handle() { server.send(200, "text/plain", "OK"); }

// ---------------------------------------------------------------------------
// Payload / metadata handlers
// ---------------------------------------------------------------------------

void ServerHandler::add_handle() {
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

void ServerHandler::remove_handle() {
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

void ServerHandler::handle_metadata_upload() {
  String body = server.arg("plain");
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, body);

  if (err) {
    server.send(400, "application/json",
                "{\"success\":false,\"error\":\"Invalid JSON\"}");
    return;
  }

  if (Storage::save_metadata_sd(doc)) {
    server.send(200, "application/json", "{\"success\":true}");
  } else {
    server.send(500, "application/json",
                "{\"success\":false,\"error\":\"Failed to save metadata\"}");
  }
}

// ---------------------------------------------------------------------------
// File transfer handlers
// ---------------------------------------------------------------------------

void ServerHandler::handle_song_upload() {
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

void ServerHandler::handle_cover_upload() {
  server.send(200, "text/plain", "OK");
}

void ServerHandler::handle_cover_file_upload() {
  HTTPUpload &upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    String song_name = server.header("X-Song-Name");
    Storage::upload_start_cover_sd(song_name);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Storage::upload_write_cover_sd(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Storage::upload_end_cover_sd();
  }
}

void ServerHandler::handle_download() {
  if (!server.hasArg("path")) {
    server.send(400, "text/plain", "Missing path");
    return;
  }

  String path = server.arg("path");

  if (path.indexOf("..") != -1 || !path.startsWith("/")) {
    server.send(400, "text/plain", "Invalid path");
    return;
  }

  File file = Storage::download_file_sd(path);

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

void ServerHandler::handle_sd_directory() {
  String json = Storage::get_sd_json_structure();
  server.send(200, "application/json", json);
}

// ---------------------------------------------------------------------------
// Setup / loop
// ---------------------------------------------------------------------------

void ServerHandler::begin() {
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

  if (MDNS.begin("orpheus")) {
    Serial.println("MDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  const char *headerKeys[] = {"X-Song-Name", "X-Chunk-Index", "X-Total-Chunks",
                              "Content-Length"};
  size_t headerKeysCount = sizeof(headerKeys) / sizeof(char *);
  server.collectHeaders(headerKeys, headerKeysCount);

  server.on("/upload_song", HTTP_POST, serve_song_upload_ok,
            handle_song_upload);
  server.on("/", HTTP_GET, serve_webpage);
  server.on("/compendium", HTTP_GET, serve_compendium);
  server.on("/songs.json", HTTP_GET, serve_songs_json);
  server.on("/coverart", HTTP_GET, serve_coverart);
  server.on("/selection_click", HTTP_POST, click_handle);
  server.on("/create_payload", HTTP_POST, add_handle);
  server.on("/remove_payload", HTTP_POST, remove_handle);
  server.on("/download_file", HTTP_GET, handle_download);
  server.on("/sd_directory", HTTP_GET, handle_sd_directory);
  server.on("/upload_metadata", HTTP_POST, handle_metadata_upload);
  server.on("/upload_cover", HTTP_POST, handle_cover_upload,
            handle_cover_file_upload);

  server.begin();
}

void ServerHandler::update() { server.handleClient(); }