#pragma once

#include "LGFX_Config.h"
#include <LovyanGFX.hpp>
#include <lvgl.h>

class Display {
public:
  static void begin();

  static LGFX &getLCD();

private:
  static LGFX lcd;
};