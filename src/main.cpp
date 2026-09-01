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

  server.on("/", HTTP_GET, serve_webpage);

  server.on("/selection_click", HTTP_POST, click_handle);

  server.on("/create_payload", HTTP_POST, add_handle);

  server.on("/remove_payload", HTTP_POST, remove_handle);

  server.begin();

  Storage::begin();

  response_web = Storage::get_sd_html_structure();

  Serial.println("SD Card Directory Observed.");
}

void loop() { server.handleClient(); }