#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MACWORK] = LAYOUT(
    DF(_HYPER),    C(KC_MINUS),   C(KC_EQUAL),
    HYPR(KC_KP_4), HYPR(KC_KP_5), SCMD(KC_4),
    C(KC_LEFT),    C(KC_UP),      C(KC_RIGHT)
  ),

  [_HYPER] = LAYOUT(
    DF(_RGB),      HYPR(KC_KP_8), HYPR(KC_KP_9),
    HYPR(KC_KP_4), HYPR(KC_KP_5), HYPR(KC_KP_6),
    HYPR(KC_KP_1), HYPR(KC_KP_2), HYPR(KC_KP_3)),

  [_RGB] = LAYOUT(
    DF(_MACWORK), RGB_RMOD, RGB_MOD,
    RGB_HUI,    RGB_VAI, RGB_SAI,
    RGB_HUD,    RGB_VAD, RGB_SAD),
};
