#pragma once

#include <Arduino.h>

namespace PIN {
//! constexpr uint8_t TFT_SCLK = 12; (NOT IMPLEMENTED)
//! constexpr uint8_t TFT_MISO = 13; (NOT IMPLEMENTED)
//! constexpr uint8_t TFT_CS = 10; (NOT IMPLEMENTED)
//! constexpr uint8_t TFT_DC = 9; (NOT IMPLEMENTED)
//! constexpr uint8_t TFT_RST = 14; (NOT IMPLEMENTED)

constexpr uint8_t SD_SCLK = 12;
constexpr uint8_t SD_MOSI = 11;
constexpr uint8_t SD_MISO = 13;
constexpr uint8_t SD_CS = 10;

// tentaive final pins for kicad routing

// MOSI = 35
// CLK = 36
// MISO = 37
// CS = 38

// end

//! constexpr uint8_t TOUCH_CS = 17; (NOT IMPLEMENTED)
} // namespace PIN