#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    _SCREEN_ID_LAST = 1
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *obj0;
    lv_obj_t *label_numbergear;
    lv_obj_t *btn_left;
    lv_obj_t *btn_right;
    lv_obj_t *btn_headlight;
    lv_obj_t *btn_checkengine;
    lv_obj_t *btn_oil;
    lv_obj_t *btn_temp;
    lv_obj_t *obj1;
    lv_obj_t *label_time;
    lv_obj_t *label_dcvolt;
    lv_obj_t *bar_gaslevel;
    lv_obj_t *obj2;
    lv_obj_t *bar_rpm;
    lv_obj_t *label_speed;
    lv_obj_t *label_temp;
    lv_obj_t *label_avg;
    lv_obj_t *label_odo;
    lv_obj_t *label_trip;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/