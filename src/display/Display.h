#pragma once

#include "LGFX_Config.h"
#include <LovyanGFX.hpp>
#include <lvgl.h>

class Display {
public:
    static void begin();
    static LGFX &getLCD();

    // Toggle orientation function
    static void toggleOrientation();

private:
    static LGFX lcd;
    static uint8_t currentOrientation;
};