#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

class Storage {
public:
  static bool begin();
  static void print_sd_structure();
  static String resolve_parent_path(File dir, const char *targetFolder);
  static bool add_payload_sd(const JsonDocument &payload);
  static void remove_payload_sd(const JsonDocument &payload);
  static File download_file_sd(const String &path);
  static String get_sd_json_structure();

  // Song upload
  static void upload_start_sd(String song_name, int chunk_index);
  static void upload_write_sd(uint8_t *buf, size_t size);
  static void upload_end_sd();

  // Image upload
  static bool upload_image_start_sd(String image_name, int chunk_index);
  static void upload_image_write_sd(uint8_t *buf, size_t size);
  static void upload_image_end_sd();

  // Metadata and songs listing
  static bool save_metadata_sd(const JsonDocument &payload);
  static String get_songs_json();
  static bool delete_song(const String &filePath);

  static void start_audio_upload(const char *fullPath);
  static void write_audio_chunk(const uint8_t *data, size_t len);
  static void end_audio_upload();

  static void start_metadata_upload(const char *fullPath);
  static void write_metadata_chunk(const uint8_t *data, size_t len);
  static void end_metadata_upload();

private:
  static File currentFile;      // for song upload
  static File currentImageFile; // for image upload
  static void print_sd_directory(File dir, int depth);
  static void build_json_directory(File dir, JsonArray parentArray);
  static bool remove_dir_recursive(String dirPath);

  static File audioUploadFile;
  static File metadataUploadFile;
};

#endif