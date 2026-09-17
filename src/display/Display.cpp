#include "Display.h"

LGFX Display::lcd;

// Partial render buffer — 320 x 40 px @ RGB565 = ~25.6 KB
static lv_color_t drawBuffer[320 * 40];

static void flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px) {
  const uint32_t w = (area->x2 - area->x1 + 1);
  const uint32_t h = (area->y2 - area->y1 + 1);

  Display::getLCD().startWrite();
  Display::getLCD().setAddrWindow(area->x1, area->y1, w, h);
  Display::getLCD().writePixels(reinterpret_cast<lgfx::rgb565_t *>(px), w * h);
  Display::getLCD().endWrite();

  lv_display_flush_ready(disp);
}

void Display::begin() {

  Serial.println("1: Initializing Display");

  lcd.init();
  Serial.println("2: lcd.init() complete");

  lcd.setRotation(3); // 320 x 240 landscape
  Serial.println("3: setRotation() complete");

  lv_init();
  Serial.println("4: lv_init() complete");

  // Give LVGL a millisecond tick source.
  lv_tick_set_cb([]() -> uint32_t { return millis(); });
  Serial.println("5: lv_tick_set_cb() complete");

  lv_display_t *display = lv_display_create(320, 240);
  Serial.println("6: lv_display_create() complete");

  lv_display_set_buffers(display, drawBuffer, nullptr, sizeof(drawBuffer),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
  Serial.println("7: lv_display_set_buffers() complete");

  lv_display_set_flush_cb(display, flush_cb);
  Serial.println("8: lv_display_set_flush_cb() complete");

  lv_display_set_default(display);
  Serial.println("9: lv_display_set_default() complete");

  Serial.println("10: Display initialized.");
}

LGFX &Display::getLCD() { return lcd; }