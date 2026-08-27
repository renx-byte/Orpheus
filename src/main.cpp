#include "credentials.h"
#include "index_html.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>

WebServer server(80);

void serve_webpage() { server.send(200, "text/html", index_html); }

void click_handle() {
  Serial.println("A button was pressed, no idea which one.");

  String body = server.arg("plain");

  Serial.println(body);

  server.send(200, "text/plain", "OK");
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

  server.begin();
}

void loop() { server.handleClient(); }