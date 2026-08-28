#pragma once

#include "pins.h"
#include <SD.h>
#include <SPI.h>

class Storage {
public:
  static bool begin();
  static String get_sd_html_structure();

private:
  static void generate_html_directory(File dir, String &html);
};