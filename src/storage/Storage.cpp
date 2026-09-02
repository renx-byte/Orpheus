#include "Storage.h"

void Storage::generate_html_directory(File dir, String &html) {
  html += "<ul>\n";

  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    html += "  <li>";

    if (entry.isDirectory()) {
      html += "<span class=\"folder\">" + String(entry.name()) + "/</span>\n";
      generate_html_directory(entry, html);
    } else {
      html += "<span class=\"file\">" + String(entry.name()) + "</span>";

      double bytes = entry.size();
      double size = (bytes < 1000000) ? (bytes / 1000.0) : (bytes / 1000000.0);
      const char *unit = (bytes < 1000000) ? " kb" : " Mb";

      html += " <span class=\"size\">(" + String(size, 1) + unit + ")</span>\n";
    }

    html += "</li>\n";
    entry.close();
  }

  html += "</ul>\n";
}

String Storage::get_sd_html_structure() {
  File root = SD.open("/");
  if (!root) {
    return "<div id=\"sd-directory\"><p>Failed to open SD Card root "
           "directory</p></div>";
  }

  String html = "<div id=\"sd-directory\">\n";

  generate_html_directory(root, html);
  root.close();

  html += "  <div class=\"options-container\">\n";
  html +=
      "    <button class=\"result-button\" id=\"add-file\">ADD ITEM</button>\n";
  html += "    <button class=\"result-button\" id=\"remove-file\">REMOVE "
          "ITEM</button>\n";
  html += "    <button class=\"result-button\" id=\"download-file\">GET "
          "ITEM</button>\n";
  html += "  </div>\n";

  html += "</div>";
  return html;
}

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
      double size = (bytes < 1000000) ? (bytes / 1000.0) : (bytes / 1000000.0);
      const char *unit = (bytes < 1000000) ? " KB" : " MB";

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

File Storage::currentFile;

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

File Storage::download_file_sd(const String &path) { return SD.open(path); }

bool Storage::begin() {
  SPI.begin(PIN::SD_SCLK, PIN::SD_MISO, PIN::SD_MOSI, PIN::SD_CS);

  if (!SD.begin(PIN::SD_CS, SPI, 40000000)) {
    Serial.println("SD mount failed");
    return false;
  }

  Serial.println("SD card initialized successfully.");

  print_sd_structure();
  return true;
}