#include "GUI.h"
#include "lvgl.h"

void GUI::begin() {

  LV_FONT_DECLARE(pokemonDP_12);
  LV_FONT_DECLARE(pokemonDP_8);

  LV_IMG_DECLARE(bg);
  LV_IMG_DECLARE(pikachu_top);

  lv_obj_t *home_screen = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(home_screen, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_style_bg_color(home_screen, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_screen, LV_OPA_COVER, LV_STATE_DEFAULT);

  lv_obj_t *orpheus_bg = lv_img_create(home_screen);
  lv_img_set_src(orpheus_bg, &bg);
  lv_obj_align(orpheus_bg, LV_ALIGN_CENTER, 0, 0);
  lv_image_set_scale(orpheus_bg, 550);

  lv_obj_t *orpheus_top = lv_img_create(home_screen);
  lv_img_set_src(orpheus_top, &pikachu_top);
  lv_obj_set_style_border_width(orpheus_top, 2, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(orpheus_top, lv_color_hex(0x000000),
                                LV_STATE_DEFAULT);
  lv_obj_set_style_radius(orpheus_top, 4, LV_STATE_DEFAULT);
  lv_obj_align(orpheus_top, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t *time = lv_label_create(orpheus_top);
  lv_label_set_text(time, "12:30");
  lv_obj_set_style_text_font(time, &pokemonDP_8, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(time, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
  lv_obj_align(time, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *white_play_shadow = lv_btn_create(home_screen);
  lv_obj_set_style_bg_color(white_play_shadow, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_width(white_play_shadow, 180);
  lv_obj_set_height(white_play_shadow, 18);
  lv_obj_set_style_border_width(white_play_shadow, 3, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(white_play_shadow, 4, LV_STATE_DEFAULT);
  lv_obj_align(white_play_shadow, LV_ALIGN_CENTER, 0, -38);

  lv_obj_t *play_button = lv_btn_create(home_screen);
  lv_obj_set_width(play_button, 200);
  lv_obj_set_height(play_button, 80);
  lv_obj_align(play_button, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_radius(play_button, 4, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(play_button, 3, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(play_button, lv_color_hex(0x000000),
                                LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(play_button, lv_color_hex(0xF13833),
                            LV_STATE_DEFAULT);

  lv_obj_t *play_label = lv_label_create(play_button);
  lv_label_set_text(play_label, "AUDIO PLAYER");
  lv_obj_set_style_text_font(play_label, &pokemonDP_12, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(play_label, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_align(play_label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *white_options_shadow = lv_btn_create(home_screen);
  lv_obj_set_style_bg_color(white_options_shadow, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_width(white_options_shadow, 80);
  lv_obj_set_height(white_options_shadow, 18);
  lv_obj_set_style_border_width(white_options_shadow, 3, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(white_options_shadow, 4, LV_STATE_DEFAULT);
  lv_obj_align(white_options_shadow, LV_ALIGN_BOTTOM_LEFT, 15, -43);

  lv_obj_t *options_button = lv_btn_create(home_screen);
  lv_obj_set_width(options_button, 100);
  lv_obj_set_height(options_button, 50);
  lv_obj_set_style_bg_color(options_button, lv_color_hex(0xE09A2A),
                            LV_STATE_DEFAULT);
  lv_obj_align(options_button, LV_ALIGN_BOTTOM_LEFT, 5, -5);
  lv_obj_set_style_radius(options_button, 4, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(options_button, 3, LV_STATE_DEFAULT);

  lv_obj_t *options_label = lv_label_create(options_button);
  lv_label_set_text(options_label, "OPTIONS");
  lv_obj_set_style_text_font(options_label, &pokemonDP_12, LV_STATE_DEFAULT);
  lv_obj_align(options_label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *white_exit_shadow = lv_btn_create(home_screen);
  lv_obj_set_style_bg_color(white_exit_shadow, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_width(white_exit_shadow, 80);
  lv_obj_set_height(white_exit_shadow, 18);
  lv_obj_set_style_border_width(white_exit_shadow, 3, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(white_exit_shadow, 4, LV_STATE_DEFAULT);
  lv_obj_align(white_exit_shadow, LV_ALIGN_BOTTOM_MID, 0, -30);

  lv_obj_t *exit_button = lv_btn_create(home_screen);
  lv_obj_set_width(exit_button, 100);
  lv_obj_set_height(exit_button, 50);
  lv_obj_set_style_bg_color(exit_button, lv_color_hex(0x2794CD),
                            LV_STATE_DEFAULT);
  lv_obj_align(exit_button, LV_ALIGN_BOTTOM_MID, 0, 8);
  lv_obj_set_style_radius(exit_button, 4, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(exit_button, 3, LV_STATE_DEFAULT);

  lv_obj_t *exit_label = lv_label_create(exit_button);
  lv_label_set_text(exit_label, "EXIT");
  lv_obj_set_style_text_font(exit_label, &pokemonDP_12, LV_STATE_DEFAULT);
  lv_obj_align(exit_label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *white_about_shadow = lv_btn_create(home_screen);
  lv_obj_set_style_bg_color(white_about_shadow, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_width(white_about_shadow, 80);
  lv_obj_set_height(white_about_shadow, 18);
  lv_obj_set_style_border_width(white_about_shadow, 3, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(white_about_shadow, 4, LV_STATE_DEFAULT);
  lv_obj_align(white_about_shadow, LV_ALIGN_BOTTOM_RIGHT, -15, -43);

  lv_obj_t *about_button = lv_btn_create(home_screen);
  lv_obj_set_width(about_button, 100);
  lv_obj_set_height(about_button, 50);
  lv_obj_set_style_bg_color(about_button, lv_color_hex(0x5DAF2F),
                            LV_STATE_DEFAULT);
  lv_obj_align(about_button, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
  lv_obj_set_style_radius(about_button, 4, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(about_button, 3, LV_STATE_DEFAULT);

  lv_obj_t *about_label = lv_label_create(about_button);
  lv_label_set_text(about_label, "ABOUT");
  lv_obj_set_style_text_font(about_label, &pokemonDP_12, LV_STATE_DEFAULT);
  lv_obj_align(about_label, LV_ALIGN_CENTER, 0, 0);

  lv_screen_load(home_screen);
}

void GUI::update() { lv_timer_handler(); }