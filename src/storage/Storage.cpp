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
  html += "  </div>\n";

  html += "</div>";
  return html;
}

void Storage::print_sd_directory(File dir, int depth) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    // Indent based on directory tree depth
    for (int i = 0; i < depth; i++) {
      Serial.print("  ");
    }

    if (entry.isDirectory()) {
      Serial.print("[DIR] ");
      Serial.println(entry.name());

      // Recurse into subdirectories with increased depth
      print_sd_directory(entry, depth + 1);
    } else {
      Serial.print("      ");
      Serial.print(entry.name());

      // Calculate file size formatting
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

// Call this function to start printing from root
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

// Helper function: Recursively searches the SD card to locate a folder by name
String Storage::resolve_parent_path(File dir, const char *targetFolder) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry)
      break;

    if (entry.isDirectory()) {
      // Check if current directory name matches the target parent name
      if (strcmp(entry.name(), targetFolder) == 0) {
        String foundPath = String(entry.path());
        entry.close();
        return foundPath;
      }

      // Recurse into subdirectories
      String nestedPath = resolve_parent_path(entry, targetFolder);
      if (nestedPath.length() > 0) {
        entry.close();
        return nestedPath;
      }
    }
    entry.close();
  }
  return ""; // Not found in this branch
}

bool Storage::add_payload_sd(const JsonDocument &payload) {
  const char *name = payload["name"] | "";
  const char *type = payload["type"] | "";
  const char *parent = payload["parent"] | "";
  const char *content = payload["content"] | "";

  String targetPath = "";

  // 1. Handle Root Path
  if (strcmp(parent, "root") == 0 || strcmp(parent, "/") == 0 ||
      strlen(parent) == 0) {
    targetPath = "/";
  } else {
    // 2. Perform Recursive Search to find the folder's real absolute path
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

  // Ensure trailing slash for building the full file/folder path
  if (!targetPath.endsWith("/")) {
    targetPath += "/";
  }

  String fullPath = targetPath + String(name);

  // 3. Create Folder
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
  }
  // 4. Create File
  else if (strcmp(type, "file") == 0) {
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

  // Protect against root deletion
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