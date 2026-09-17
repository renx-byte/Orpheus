#include "Display.h"
#include "GUI.h"
#include "ServerHandler.h"
#include "Storage.h"
#include <Arduino.h>

void setup() {

  delay(5000);
  Serial.begin(115200);
  Serial.println("Serial Monitor Initialized");

  Storage::begin();

  Display::begin();

  GUI::begin();

  if (!Storage::ensure_directories()) {
    Serial.println("Warning: Failed to create required directories.");
  }

  Serial.println("SD Card Directory JSON endpoint ready.");

  ServerHandler::begin();
}

void loop() {
  ServerHandler::update();
  GUI::update();
  delay(5);
}