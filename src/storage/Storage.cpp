#include "Storage.h"
#include "pins.h"

File Storage::currentFile;
File Storage::currentImageFile;
File Storage::audioUploadFile;
File Storage::metadataUploadFile;

// ============================================================
// SD Card Initialization
// ============================================================
bool Storage::begin() {
  SPI.begin(PIN::SD_SCLK, PIN::SD_MISO, PIN::SD_MOSI, PIN::SD_CS);

  if (!SD.begin(PIN::SD_CS, SPI, 40000000)) {
    Serial.println("SD mount failed");
    return false;
  }

  // Ensure required directories exist
  if (!SD.exists("/songs")) {
    if (SD.mkdir("/songs")) {
      Serial.println("Created /songs directory");
    } else {
      Serial.println("Failed to create /songs directory");
    }
  }
  if (!SD.exists("/metadata")) {
    if (SD.mkdir("/metadata")) {
      Serial.println("Created /metadata directory");
    } else {
      Serial.println("Failed to create /metadata directory");
    }
  }

  Serial.println("SD card initialized successfully.");
  print_sd_structure();
  return true;
}

// ============================================================
// Directory Printing (Legacy / Debug)
// ============================================================
void Storage::print_sd_directory(File dir, int depth) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    for (int i = 0; i < depth; i++) {
      Serial.print("  ");
    }

    if (entry.isDirectory()) {
      Serial.print("[DIR] ");
      Serial.println(entry.name());
      print_sd_directory(entry, depth + 1);
    } else {
      Serial.print("      ");
      Serial.print(entry.name());

      double bytes = entry.size();
      double size = (bytes < 1048576) ? (bytes / 1024.0) : (bytes / 1048576.0);
      const char *unit = (bytes < 1048576) ? " KB" : " MB";

      Serial.print(" (");
      Serial.print(size, 1);
      Serial.print(unit);
      Serial.println(")");
    }

    entry.close();
  }
}

void Storage::print_sd_structure() {
  File root = SD.open("/");
  if (!root) {
    Serial.println("Failed to open SD Card root directory");
    return;
  }

  Serial.println("--- SD Card Directory Structure ---");
  print_sd_directory(root, 0);
  root.close();
  Serial.println("----------------------------------");
}

// ============================================================
// Legacy Payload Management (Backlog - not currently used)
// ============================================================
String Storage::resolve_parent_path(File dir, const char *targetFolder) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    if (entry.isDirectory()) {
      if (strcmp(entry.name(), targetFolder) == 0) {
        String foundPath = String(entry.path());
        entry.close();
        return foundPath;
      }

      String nestedPath = resolve_parent_path(entry, targetFolder);
      if (nestedPath.length() > 0) {
        entry.close();
        return nestedPath;
      }
    }
    entry.close();
  }
  return "";
}

bool Storage::add_payload_sd(const JsonDocument &payload) {
  const char *name = payload["name"] | "";
  const char *type = payload["type"] | "";
  const char *parent = payload["parent"] | "";
  const char *content = payload["content"] | "";

  String targetPath = "";

  if (strcmp(parent, "root") == 0 || strcmp(parent, "/") == 0 ||
      strlen(parent) == 0) {
    targetPath = "/";
  } else {
    File root = SD.open("/");
    if (root) {
      targetPath = resolve_parent_path(root, parent);
      root.close();
    }

    if (targetPath.length() == 0) {
      Serial.print("Error: Could not locate parent folder anywhere on SD: ");
      Serial.println(parent);
      return false;
    }
  }

  if (!targetPath.endsWith("/")) {
    targetPath += "/";
  }

  String fullPath = targetPath + String(name);

  if (strcmp(type, "folder") == 0) {
    if (SD.mkdir(fullPath.c_str())) {
      Serial.print("Created folder: ");
      Serial.println(fullPath);
      return true;
    } else {
      Serial.print("Failed to create folder: ");
      Serial.println(fullPath);
      return false;
    }
  } else if (strcmp(type, "file") == 0) {
    File newFile = SD.open(fullPath.c_str(), FILE_WRITE);
    if (newFile) {
      if (strlen(content) > 0) {
        newFile.print(content);
      }
      newFile.close();
      return true;
    } else {
      return false;
    }
  }

  return false;
}

bool Storage::remove_dir_recursive(String dirPath) {
  File dir = SD.open(dirPath);
  if (!dir)
    return false;

  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    String entryPath = dirPath;
    if (!entryPath.endsWith("/"))
      entryPath += "/";
    entryPath += entry.name();

    if (entry.isDirectory()) {
      entry.close();
      remove_dir_recursive(entryPath);
    } else {
      entry.close();
      SD.remove(entryPath);
    }
  }

  dir.close();
  return SD.rmdir(dirPath);
}

void Storage::remove_payload_sd(const JsonDocument &payload) {
  String path = payload["path"] | "";

  if (path.isEmpty() || path == "/")
    return;

  File f = SD.open(path);
  if (!f)
    return;
  bool isDir = f.isDirectory();
  f.close();

  if (isDir) {
    remove_dir_recursive(path);
  } else {
    SD.remove(path);
  }
}

File Storage::download_file_sd(const String &path) { return SD.open(path); }

// ============================================================
// Legacy JSON Directory Generation (Backlog)
// ============================================================
void Storage::build_json_directory(File dir, JsonArray parentArray) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    JsonObject obj = parentArray.add<JsonObject>();
    obj["name"] = String(entry.name());

    if (entry.isDirectory()) {
      obj["type"] = "folder";
      JsonArray subChildren = obj["children"].to<JsonArray>();
      build_json_directory(entry, subChildren);
    } else {
      obj["type"] = "file";
      obj["size"] = entry.size();
    }

    entry.close();
  }
}

String Storage::get_sd_json_structure() {
  JsonDocument doc;
  doc["path"] = "/";
  doc["type"] = "folder";
  JsonArray children = doc["children"].to<JsonArray>();

  File root = SD.open("/");
  if (!root) {
    doc["error"] = "Failed to open root";
    String json;
    serializeJson(doc, json);
    return json;
  }

  build_json_directory(root, children);
  root.close();

  String json;
  serializeJson(doc, json);
  return json;
}

// ============================================================
// Legacy chunked upload functions (kept for backward compatibility)
// ============================================================
void Storage::upload_start_sd(String song_name, int chunk_index) {
  if (!song_name.startsWith("/")) {
    song_name = "/" + song_name;
  }

  const char *mode = (chunk_index == 0) ? FILE_WRITE : FILE_APPEND;
  currentFile = SD.open(song_name, mode);
  if (!currentFile) {
    Serial.print("Error: Failed to open file on SD for path: ");
    Serial.println(song_name);
  }
}

void Storage::upload_write_sd(uint8_t *buf, size_t size) {
  if (currentFile) {
    currentFile.write(buf, size);
  } else {
    Serial.println("Error: Attempted write with no file open");
  }
}

void Storage::upload_end_sd() {
  if (currentFile) {
    currentFile.close();
  }
}

bool Storage::upload_image_start_sd(String image_name, int chunk_index) {
  if (!image_name.startsWith("/")) {
    image_name = "/" + image_name;
  }

  const char *mode = (chunk_index == 0) ? FILE_WRITE : FILE_APPEND;
  currentImageFile = SD.open(image_name, mode);
  if (!currentImageFile) {
    Serial.print("Error: Failed to open image file on SD for path: ");
    Serial.println(image_name);
    return false;
  }
  return true;
}

void Storage::upload_image_write_sd(uint8_t *buf, size_t size) {
  if (currentImageFile) {
    currentImageFile.write(buf, size);
  } else {
    Serial.println("Error: Attempted image write with no file open");
  }
}

void Storage::upload_image_end_sd() {
  if (currentImageFile) {
    currentImageFile.close();
  }
}

// ============================================================
// NEW: Streaming upload for audio (MP3) into /songs/
// ============================================================
void Storage::start_audio_upload(const char *fullPath) {
  audioUploadFile = SD.open(fullPath, FILE_WRITE);
  if (!audioUploadFile) {
    Serial.printf("Error: Failed to open audio file for writing: %s\n",
                  fullPath);
  }
}

void Storage::write_audio_chunk(const uint8_t *data, size_t len) {
  if (audioUploadFile) {
    audioUploadFile.write(data, len);
  } else {
    Serial.println("Error: Attempted audio write with no file open");
  }
}

void Storage::end_audio_upload() {
  if (audioUploadFile) {
    audioUploadFile.close();
  }
}

// ============================================================
// NEW: Streaming upload for metadata JSON into /metadata/
// ============================================================
void Storage::start_metadata_upload(const char *fullPath) {
  metadataUploadFile = SD.open(fullPath, FILE_WRITE);
  if (!metadataUploadFile) {
    Serial.printf("Error: Failed to open metadata file for writing: %s\n",
                  fullPath);
  }
}

void Storage::write_metadata_chunk(const uint8_t *data, size_t len) {
  if (metadataUploadFile) {
    metadataUploadFile.write(data, len);
  } else {
    Serial.println("Error: Attempted metadata write with no file open");
  }
}

void Storage::end_metadata_upload() {
  if (metadataUploadFile) {
    metadataUploadFile.close();
  }
}

// ============================================================
// Metadata Saving (legacy JSON body method – kept for old clients)
// ============================================================
bool Storage::save_metadata_sd(const JsonDocument &payload) {
  const char *filePath = payload["file_path"] | "";
  const char *songName = payload["song_name"] | "";
  const char *artist = payload["artist"] | "";
  const char *album = payload["album"] | "";
  const char *releaseDate = payload["release_date"] | "";
  const char *duration = payload["duration"] | "";
  const char *colorPrimary = payload["color_primary"] | "#c1afa0";
  const char *colorDark = payload["color_dark"] | "#6c584c";
  const char *colorShadow = payload["color_shadow"] | "#3f352f";
  const char *imageFile = payload["image_file"] | "";

  if (strlen(filePath) == 0) {
    Serial.println("Error: file_path missing in metadata");
    return false;
  }

  // Save next to MP3 as .json (legacy behavior)
  String jsonPath = String(filePath) + ".json";

  File metaFile = SD.open(jsonPath.c_str(), FILE_WRITE);
  if (!metaFile) {
    Serial.print("Error: cannot open metadata file for writing: ");
    Serial.println(jsonPath);
    return false;
  }

  JsonDocument metaDoc;
  metaDoc["song_name"] = songName;
  metaDoc["artist"] = artist;
  metaDoc["album"] = album;
  metaDoc["release_date"] = releaseDate;
  metaDoc["duration"] = duration;
  metaDoc["color_primary"] = colorPrimary;
  metaDoc["color_dark"] = colorDark;
  metaDoc["color_shadow"] = colorShadow;
  metaDoc["image_file"] = imageFile;

  String json;
  serializeJson(metaDoc, json);
  metaFile.print(json);
  metaFile.close();

  Serial.print("Metadata saved to: ");
  Serial.println(jsonPath);
  return true;
}

// ============================================================
// Songs Listing (returns JSON array of all songs from /metadata/)
// ============================================================
String Storage::get_songs_json() {
  JsonDocument root;
  JsonArray songs = root.to<JsonArray>();

  File dir = SD.open("/metadata");
  if (!dir) {
    return "[]";
  }

  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    if (!entry.isDirectory() && String(entry.name()).endsWith(".json")) {
      File metaFile = SD.open(entry.path());
      if (metaFile) {
        JsonDocument meta;
        DeserializationError err = deserializeJson(meta, metaFile);
        metaFile.close();

        if (!err) {
          // Ensure file_path is present (derive from filename if missing)
          if (!meta.containsKey("file_path")) {
            String base = String(entry.name());
            base.remove(base.length() - 5); // remove ".json"
            meta["file_path"] = "/songs/" + base + ".mp3";
          }
          songs.add(meta);
        } else {
          Serial.printf("Failed to parse metadata JSON: %s\n", entry.name());
        }
      }
    }

    entry.close();
  }
  dir.close();

  String json;
  serializeJson(root, json);
  return json;
}

// ============================================================
// Delete Song (removes MP3 and corresponding metadata JSON)
// ============================================================
bool Storage::delete_song(const String &filePath) {
  // filePath is expected to be like "/songs/My_Song.mp3"
  String baseName;
  if (filePath.startsWith("/songs/")) {
    baseName = filePath.substring(7); // remove "/songs/"
  } else {
    baseName = filePath;
  }
  // Remove extension
  int dotIndex = baseName.lastIndexOf('.');
  if (dotIndex > 0) {
    baseName.remove(dotIndex);
  }

  String mp3Path = "/songs/" + baseName + ".mp3";
  String jsonPath = "/metadata/" + baseName + ".json";

  bool success = true;
  if (SD.exists(mp3Path)) {
    if (!SD.remove(mp3Path)) {
      Serial.printf("Failed to delete MP3: %s\n", mp3Path.c_str());
      success = false;
    }
  }
  if (SD.exists(jsonPath)) {
    if (!SD.remove(jsonPath)) {
      Serial.printf("Failed to delete metadata JSON: %s\n", jsonPath.c_str());
      success = false;
    }
  }

  return success;
}