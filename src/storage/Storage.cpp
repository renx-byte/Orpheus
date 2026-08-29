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
      "    <button class=\"result-button\" id=\"add-file\">ADD FILE</button>\n";
  html += "    <button class=\"result-button\" id=\"remove-file\">REMOVE "
          "FILE</button>\n";
  html += "  </div>\n";

  html += "</div>";
  return html;
}

bool Storage::begin() {
  SPI.begin(PIN::SD_SCLK, PIN::SD_MISO, PIN::SD_MOSI, PIN::SD_CS);

  if (!SD.begin(PIN::SD_CS, SPI, 10000000)) {
    Serial.println("SD mount failed");
    return false;
  }

  Serial.println("SD card initialized successfully.");
  return true;
}