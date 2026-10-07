#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_background_home;
extern const lv_img_dsc_t img_headlight;
extern const lv_img_dsc_t img_left_arrow;
extern const lv_img_dsc_t img_right_arrow;
extern const lv_img_dsc_t img_temp;
extern const lv_img_dsc_t img_check_enginge;
extern const lv_img_dsc_t img_check_oil;
extern const lv_img_dsc_t img_oil_off;
extern const lv_img_dsc_t img_headlight_off;
extern const lv_img_dsc_t img_left_off;
extern const lv_img_dsc_t img_right_off;
extern const lv_img_dsc_t img_temp_off;
extern const lv_img_dsc_t img_check_enginge_off;
extern const lv_img_dsc_t img_gas;
extern const lv_img_dsc_t img_gas_low;
extern const lv_img_dsc_t img_gas_avg;
extern const lv_img_dsc_t img_gas_full;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[17];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/