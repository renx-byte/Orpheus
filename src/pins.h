#pragma once
#include <Arduino.h>

namespace PIN {
// Safe GPIOs for ILI9341 Display (FSPI / SPI2_HOST)
constexpr uint8_t TFT_SCLK = 12;
constexpr uint8_t TFT_MOSI = 11;
constexpr uint8_t TFT_MISO = 13;
constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 14;
constexpr uint8_t TFT_RST = 21;

// SD Card (Moved to HSPI / SPI3_HOST using safe general GPIOs)
constexpr uint8_t SD_SCLK = 4;
constexpr uint8_t SD_MOSI = 6;
constexpr uint8_t SD_MISO = 5;
constexpr uint8_t SD_CS = 7;
} // namespace PIN