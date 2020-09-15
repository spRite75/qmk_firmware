#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(HYPR(KC_KP_7), HYPR(KC_KP_8), HYPR(KC_KP_9),
               HYPR(KC_KP_4), TG(1),         HYPR(KC_KP_6),
               HYPR(KC_KP_1), HYPR(KC_KP_2), HYPR(KC_KP_3)),

  [1] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI,  TG(1),   RGB_SAI,
               RGB_HUD,  RGB_VAD, RGB_SAD),

};
