#pragma once

#include "pins.h"
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

class Storage {
public:
  static bool begin();
  static String get_sd_html_structure();
  static void print_sd_structure();
  static void print_sd_directory(File dir, int depth);
  static String resolve_parent_path(File dir, const char *targetFolder);

  static bool add_payload_sd(const JsonDocument &payload);
  static void remove_payload_sd(const JsonDocument &payload);

private:
  static void generate_html_directory(File dir, String &html);
  static bool remove_dir_recursive(String dirPath);
};