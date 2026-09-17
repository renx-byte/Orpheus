#pragma once

#include <lvgl.h>

class GUI {

private:
  static lv_obj_t *bootup_scr;
  static lv_obj_t *home_scr;

public:
  static void begin();

  static void create_bootup_scr();
  static void create_home_scr();

  static void show_bootup_scr();
  static void show_home_scr();

  static void update();
};