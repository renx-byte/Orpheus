#include "Display.h"

LGFX Display::lcd;
// Initialize to matching initial state in begin()
uint8_t Display::currentOrientation = 3;

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
    Serial.println("Initializing Display");

    lcd.init();
    currentOrientation = 3;
    lcd.setRotation(currentOrientation); // 3

    lv_init();

    lv_tick_set_cb([]() -> uint32_t { return millis(); });

    lv_display_t *display = lv_display_create(320, 240);

    lv_display_set_buffers(display, drawBuffer, nullptr, sizeof(drawBuffer),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(display, flush_cb);

    lv_display_set_default(display);

    Serial.println("Display initialized.");
}

LGFX &Display::getLCD() { return lcd; }

void Display::toggleOrientation() {
    // 1. Toggle between UP (1) and DOWN (3)
    currentOrientation = (currentOrientation == 1) ? 3 : 1;

    // 2. Pass uint8_t value directly to LovyanGFX
    lcd.setRotation(currentOrientation);

    // 3. Update LVGL display rotation
    lv_display_t *disp = lv_display_get_default();
    if (disp != nullptr) {
        lv_display_rotation_t lv_rot = (currentOrientation == 1) 
                                       ? LV_DISPLAY_ROTATION_0 
                                       : LV_DISPLAY_ROTATION_180;
        lv_display_set_rotation(disp, lv_rot);
    }
}