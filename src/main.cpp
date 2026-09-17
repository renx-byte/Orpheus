#include "Display.h"
#include "GUI.h"
#include "ServerHandler.h"
#include "Storage.h"
#include <Arduino.h>

void setup() {
  delay(5000);
  Serial.begin(115200);
  Serial.println("Serial Monitor Initialized");

  ServerHandler::begin();

  Storage::begin();

  if (!Storage::ensure_directories()) {
    Serial.println("Warning: Failed to create required directories.");
  }

  Serial.println("SD Card Directory JSON endpoint ready.");

  Display::begin();

  GUI::begin();
}

void loop() {
  ServerHandler::update();
  GUI::update();
  delay(5);
}