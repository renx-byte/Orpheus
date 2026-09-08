#ifndef STORAGE_H
#define STORAGE_H

#include "pins.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

class Storage {
public:
  static bool begin();
  static void print_sd_structure();
  static bool add_payload_sd(const JsonDocument &payload);
  static void remove_payload_sd(const JsonDocument &payload);

  static bool ensure_directories();
  static bool save_metadata_sd(const JsonDocument &metadata);
  static void upload_start_cover_sd(String song_name);
  static void upload_write_cover_sd(uint8_t *buf, size_t size);
  static void upload_end_cover_sd();

  static void upload_start_sd(String song_name, int chunk_index);
  static void upload_write_sd(uint8_t *buf, size_t size);
  static void upload_end_sd();
  static File download_file_sd(const String &path);

  static String get_sd_json_structure();
  static File get_cover_art_file(const String &fileName);

  static String get_songs_json();

private:
  static File currentFile;
  static File currentCoverFile;
  static void print_sd_directory(File dir, int depth);
  static void build_json_directory(File dir, JsonArray parentArray);
  static String resolve_parent_path(File dir, const char *targetFolder);
  static bool remove_dir_recursive(String dirPath);
};

#endif