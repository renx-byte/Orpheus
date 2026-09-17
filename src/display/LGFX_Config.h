#pragma once
#define LGFX_USE_V1
#include "pins.h"
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX() {
    {
      auto cfg = _bus_instance.config();

      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 20000000;
      cfg.freq_read = 8000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;

      cfg.pin_sclk = PIN::TFT_SCLK;
      cfg.pin_mosi = PIN::TFT_MOSI;
      cfg.pin_miso = -1;
      cfg.pin_dc = PIN::TFT_DC;

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    { // ILI9341 panel
      auto cfg = _panel_instance.config();

      cfg.pin_cs = PIN::TFT_CS;
      cfg.pin_rst = PIN::TFT_RST;
      cfg.pin_busy = -1;

      cfg.panel_width = 240;
      cfg.panel_height = 320;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.readable = false;
      cfg.invert = false;    // flip to true if colours look inverted
      cfg.rgb_order = false; // flip to true if red/blue are swapped

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};