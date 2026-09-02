#pragma once

#include "pins.h"
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <WiFi.h>

class Storage {
public:
  static File currentFile; // Keeps file open across UPLOAD_FILE_WRITE callbacks

  static bool begin();
  static String get_sd_html_structure();
  static void print_sd_structure();
  static void print_sd_directory(File dir, int depth);
  static String resolve_parent_path(File dir, const char *targetFolder);

  static bool add_payload_sd(const JsonDocument &payload);
  static void remove_payload_sd(const JsonDocument &payload);

  static void upload_start_sd(String song_name, int chunk_index);
  static void upload_write_sd(uint8_t *buf, size_t size);
  static void upload_end_sd();

  static File download_file_sd(const String &path);

private:
  static void generate_html_directory(File dir, String &html);
  static bool remove_dir_recursive(String dirPath);
};