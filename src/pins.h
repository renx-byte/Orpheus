#pragma once
#include <Arduino.h>

namespace PIN {
// Safe GPIOs for ILI9341 Display (FSPI / SPI2_HOST)
constexpr uint8_t TFT_SCLK = 12; // Native SCLK
constexpr uint8_t TFT_MOSI = 11; // Native MOSI
constexpr uint8_t TFT_MISO = 13; // Native MISO (or -1 if unused)
constexpr uint8_t TFT_CS = 10;   // Native CS
constexpr uint8_t TFT_DC = 14;   // General IO
constexpr uint8_t TFT_RST = 21;  // General IO

// SD Card (Moved to HSPI / SPI3_HOST using safe general GPIOs)
constexpr uint8_t SD_SCLK = 4;
constexpr uint8_t SD_MOSI = 6;
constexpr uint8_t SD_MISO = 5;
constexpr uint8_t SD_CS = 7;
} // namespace PIN