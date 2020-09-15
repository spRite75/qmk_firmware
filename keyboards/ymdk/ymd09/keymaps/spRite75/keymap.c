#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_HYPER] = LAYOUT(HYPR(KC_KP_7), HYPR(KC_KP_8), HYPR(KC_KP_9),
               HYPR(KC_KP_4), DF(_RGB),         HYPR(KC_KP_6),
               HYPR(KC_KP_1), HYPR(KC_KP_2), HYPR(KC_KP_3)),

  [_RGB] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI, DF(_HYPER), RGB_SAI,
               RGB_HUD, RGB_VAD, RGB_SAD),
};

const rgblight_segment_t PROGMEM rgb_hyper_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_WHITE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_hyper_layer,
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_HYPER, layer_state_cmp(state, _HYPER));
    return state;
}
