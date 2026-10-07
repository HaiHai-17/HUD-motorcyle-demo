#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#include "ui.h"

namespace {
constexpr uint16_t SCREEN_WIDTH = 320;
constexpr uint16_t SCREEN_HEIGHT = 240;
constexpr uint8_t TFT_ROTATION = 1;
constexpr uint16_t LVGL_BUFFER_LINES = 20;
constexpr uint32_t HUD_UPDATE_INTERVAL_MS = 700;
constexpr uint32_t BUTTON_PULSE_MS = 180;

TFT_eSPI tft;
lv_display_t* display;
lv_color_t displayBuffer[SCREEN_WIDTH * LVGL_BUFFER_LINES];
uint32_t lastHudUpdate = 0;
uint32_t buttonPressedUntil = 0;
lv_obj_t* pressedButton = nullptr;

void flushDisplay(lv_display_t* display, const lv_area_t* area, uint8_t* pixels) {
    const uint32_t width = static_cast<uint32_t>(area->x2 - area->x1 + 1);
    const uint32_t height = static_cast<uint32_t>(area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, width, height);
    tft.pushColors(reinterpret_cast<uint16_t*>(pixels), width * height, true);
    tft.endWrite();
    lv_display_flush_ready(display);
}

void initDisplay() {
    tft.begin();
    tft.setRotation(TFT_ROTATION);
    tft.fillScreen(TFT_BLACK);

    lv_init();
    display = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_buffers(
        display,
        displayBuffer,
        nullptr,
        sizeof(displayBuffer),
        LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, flushDisplay);
}

void pulseRandomButton() {
    static lv_obj_t* const buttons[] = {
        objects.btn_left,
        objects.btn_headlight,
        objects.btn_checkengine,
        objects.btn_oil,
        objects.btn_temp,
        objects.btn_right
    };

    if (pressedButton != nullptr) {
        lv_obj_remove_state(pressedButton, LV_STATE_PRESSED);
    }

    pressedButton = buttons[random(0, sizeof(buttons) / sizeof(buttons[0]))];
    lv_obj_add_state(pressedButton, LV_STATE_PRESSED);
    buttonPressedUntil = millis() + BUTTON_PULSE_MS;
}

void setFloatLabel(lv_obj_t* label, float value, uint8_t decimals,
                   const char* suffix = "") {
    char text[24];
    char format[8];
    snprintf(format, sizeof(format), "%%.%uf%%s", decimals);
    snprintf(text, sizeof(text), format, value, suffix);
    lv_label_set_text(label, text);
}

void updateGearStyle(int gear) {
    lv_obj_set_style_text_color(
        objects.label_numbergear,
        gear == 0 ? lv_color_hex(0x00ff1d) : lv_color_white(),
        LV_PART_MAIN | LV_STATE_DEFAULT);
}

void updateGasLevel(int gasLevel) {
    lv_bar_set_value(objects.bar_gaslevel, gasLevel, LV_ANIM_OFF);

    const lv_color_t color = gasLevel < 30
        ? lv_color_hex(0xff2020)
        : gasLevel < 70
            ? lv_color_hex(0xf3a621)
            : lv_color_hex(0x2080ff);
    lv_obj_set_style_bg_color(
        objects.bar_gaslevel, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

void updateRandomHud() {
    char text[24];

    const int gear = random(0, 6);
    snprintf(text, sizeof(text), "%c", gear == 0 ? 'N' : static_cast<char>('0' + gear));
    lv_label_set_text(objects.label_numbergear, text);
    updateGearStyle(gear);

    lv_label_set_text_fmt(objects.label_speed, "%d", random(0, 181));
    lv_label_set_text_fmt(objects.label_time, "%02d:%02d",
                          random(0, 24), random(0, 60));
    setFloatLabel(objects.label_dcvolt, random(118, 145) / 10.0f, 1, "V");
    setFloatLabel(objects.label_trip, random(0, 5000) / 10.0f, 1);
    lv_label_set_text_fmt(objects.label_odo, "%d",
                          random(1000, 120000));
    setFloatLabel(objects.label_avg, random(20, 1000) / 10.0f, 1);
    lv_label_set_text_fmt(objects.label_temp, "%d",
                          random(20, 121));
    updateGasLevel(random(0, 101));
    lv_bar_set_value(objects.bar_rpm, random(0, 101), LV_ANIM_OFF);

    pulseRandomButton();
}

void updateRandomHudState() {
    const uint32_t now = millis();
    if (pressedButton != nullptr &&
        static_cast<int32_t>(now - buttonPressedUntil) >= 0) {
        lv_obj_remove_state(pressedButton, LV_STATE_PRESSED);
        pressedButton = nullptr;
    }

    if (now - lastHudUpdate >= HUD_UPDATE_INTERVAL_MS) {
        lastHudUpdate = now;
        updateRandomHud();
    }
}
}

void setup() {
    Serial.begin(115200);
    delay(200);
    randomSeed(micros());
    initDisplay();
    ui_init();
    updateRandomHud();
    Serial.println("HUD display ready");
}

void loop() {
    static uint32_t lastTick = millis();
    const uint32_t now = millis();
    lv_tick_inc(now - lastTick);
    lastTick = now;

    ui_tick();
    updateRandomHudState();
    lv_timer_handler();
    delay(5);
}
