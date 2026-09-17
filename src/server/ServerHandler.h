#pragma once

#include "credentials.h"
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>

#include "compendium.h"
#include "home.h"


class ServerHandler {
public:
  static void begin();
  static void update();

private:
  // Page / simple handlers
  static void serve_webpage();
  static void serve_compendium();
  static void serve_songs_json();
  static void serve_coverart();
  static void serve_song_upload_ok();
  static void click_handle();

  // Payload / metadata handlers
  static void add_handle();
  static void remove_handle();
  static void handle_metadata_upload();

  // File transfer handlers
  static void handle_song_upload();
  static void handle_cover_upload();
  static void handle_cover_file_upload();
  static void handle_download();
  static void handle_sd_directory();
};