#include "Storage.h"
#include "credentials.h"
#include "index_html.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>

String response_web;

WebServer server(80);

void serve_webpage() { server.send(200, "text/html", index_html); }

void click_handle() {

  String body = server.arg("plain");

  JsonDocument json_obj;

  DeserializationError err = deserializeJson(json_obj, body);

  if (err) {
    Serial.println("JSON parsing failed.");
  }

  String title = json_obj["title"];

  Serial.println(title);

  if (title == "SD CARD") {
    server.send(200, "text/html", response_web);
  } else {
    server.send(200, "text/html", "<h1>NOT SD CARD</h1>");
  }
}

void add_handle() {

  String body = server.arg("plain");

  JsonDocument json_obj;

  DeserializationError err = deserializeJson(json_obj, body);

  if (err) {
    Serial.println("JSON parsing failed.");
  }

  Serial.println(body);

  Storage::add_payload_sd(json_obj);

  response_web = Storage::get_sd_html_structure();

  server.send(200, "text/html", response_web);
}

void remove_handle() {

  String body = server.arg("plain");
  JsonDocument json_obj;
  DeserializationError err = deserializeJson(json_obj, body);

  if (err) {
    Serial.println("JSON parsing failed in remove_handle.");
  }

  Storage::remove_payload_sd(json_obj);

  response_web = Storage::get_sd_html_structure();

  server.send(200, "text/html", response_web);
}

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
    // Update the cached SD directory after upload completes
    response_web = Storage::get_sd_html_structure();
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
                              "Content-Length"};
  size_t headerKeysCount = sizeof(headerKeys) / sizeof(char *);
  server.collectHeaders(headerKeys, headerKeysCount);

  server.on(
      "/upload_song", HTTP_POST, []() { server.send(200, "text/plain", "OK"); },
      handle_song_upload);

  server.on("/", HTTP_GET, serve_webpage);

  server.on("/selection_click", HTTP_POST, click_handle);

  server.on("/create_payload", HTTP_POST, add_handle);

  server.on("/remove_payload", HTTP_POST, remove_handle);

  server.on("/download_file", HTTP_GET, handle_download);

  server.begin();

  Storage::begin();

  response_web = Storage::get_sd_html_structure();

  Serial.println("SD Card Directory Observed.");
}

void loop() { server.handleClient(); }