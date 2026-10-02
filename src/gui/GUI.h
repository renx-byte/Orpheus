#pragma once

#include <lvgl.h>

class GUI {
public:
  static void begin();

  static void update();
  
  static void create_debug_screen();
  static void load_debug_screen();
  static void create_home_screen();
  static void load_home_screen();
};