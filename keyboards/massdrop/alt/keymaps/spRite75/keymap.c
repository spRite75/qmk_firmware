#include QMK_KEYBOARD_H

//---LAYER NAMES
enum {
    LO_BASE = 0,
    LO_CODING,
    LO_OVERWATCH,
    LO_CSGO,
    LO_CHAT,
    LO_GENMOD,
    LO_SETTINGS
};

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    // Custom Functionality
    CHAT_ENTR,          // tap enter and toggle chat layer
    CHAT_ESC,           // tap escape and toggle chat layer
    CSGO_U,             // tap U and toggle chat layer
    CSGO_Y,             // tap Y and toggle chat layer
};

//---TAPDANCES
enum {
  TD_LCADET = 0,
  TD_RCADET,
  TD_COLONS,
  TD_QUOTES,
  TD_DASH,
  TD_LALT,
};
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

static tap td_left_cadet_state = {
    .is_press_action = true,
    .state = 0
};

void td_left_cadet_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_left_cadet_state.state = cur_dance(state);
    switch (td_left_cadet_state.state) {
        case SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case SINGLE_TAP:
            SEND_STRING("(");
            break;
        case DOUBLE_TAP:
            SEND_STRING("[");
            break;
        case TRIPLE_TAP:
            SEND_STRING("{");
            break;
    }
}

void td_left_cadet_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_left_cadet_state.state) {
        case SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
    }
}

static tap td_right_cadet_state = {
    .is_press_action = true,
    .state = 0
};

void td_right_cadet_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_right_cadet_state.state = cur_dance(state);
    switch (td_right_cadet_state.state) {
        case SINGLE_HOLD:
            register_code(KC_RSFT);
            break;
        case SINGLE_TAP:
            SEND_STRING(")");
            break;
        case DOUBLE_TAP:
            SEND_STRING("]");
            break;
        case TRIPLE_TAP:
            SEND_STRING("}");
            break;
    }
}

void td_right_cadet_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_right_cadet_state.state) {
        case SINGLE_HOLD:
            unregister_code(KC_RSFT);
            break;
    }
}


static tap td_oneshot_lalt_state = {
    .is_press_action = true,
    .state = 0
};

void td_oneshot_lalt(qk_tap_dance_state_t *state, void *user_data) {
    td_oneshot_lalt_state.state = cur_dance(state);
    switch (td_oneshot_lalt_state.state) {
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        default:
            set_oneshot_layer(LO_GENMOD, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
    }
}

void td_oneshot_lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_oneshot_lalt_state.state) {
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
    }
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LCADET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_cadet_finished, td_left_cadet_reset),
    [TD_RCADET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_right_cadet_finished, td_right_cadet_reset),
    [TD_COLONS] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOTES] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_DASH] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
    [TD_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_oneshot_lalt, td_oneshot_lalt_reset),
};

keymap_config_t keymap_config;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* General Layout */
    [LO_BASE] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,    KC_2,        KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,       KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,       KC_RBRC, KC_BSLS, KC_MEDIA_PLAY_PAUSE, \
        KC_CAPS, KC_A,    KC_S,        KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                KC_ENT,  KC_AUDIO_VOL_UP, \
        KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                KC_UP,   KC_AUDIO_VOL_DOWN, \
        KC_LCTL, KC_LGUI, TD(TD_LALT),                            KC_SPC,                             KC_RALT, MO(LO_GENMOD), KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Coding Layout */
    [LO_CODING] = LAYOUT_65_ansi_blocker(
        KC_GRV,        KC_1,    KC_2,        KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          TD(TD_DASH),   KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,        KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_LBRC,       KC_RBRC, KC_BSLS, KC_MEDIA_PLAY_PAUSE, \
        KC_CAPS,       KC_A,    KC_S,        KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD_COLONS), TD(TD_QUOTES),          KC_ENT,  KC_AUDIO_VOL_UP, \
        TD(TD_LCADET), KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       TD(TD_RCADET),          KC_UP,   KC_AUDIO_VOL_DOWN, \
        KC_LCTL,       KC_LGUI, TD(TD_LALT),                            KC_SPC,                             KC_RALT,       MO(LO_GENMOD), KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Overwatch Layout */
    [LO_OVERWATCH] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,        KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,       KC_EQL,  KC_BSPC,   KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,       KC_RBRC, KC_BSLS,   KC_MEDIA_PLAY_PAUSE, \
        KC_CAPS, KC_A,    KC_S,        KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                CHAT_ENTR, KC_AUDIO_VOL_UP, \
        KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                KC_UP,     KC_AUDIO_VOL_DOWN, \
        KC_LCTL, KC_LGUI, TD(TD_LALT),                            KC_SPC,                             KC_RALT, MO(LO_GENMOD), KC_LEFT, KC_DOWN,   KC_RGHT  \
    ),
    /* CSGO Layout */
    [LO_CSGO] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,    KC_2,        KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,       KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,    CSGO_Y,  CSGO_U,  KC_I,    KC_O,    KC_P,    KC_LBRC,       KC_RBRC, KC_BSLS, KC_MEDIA_PLAY_PAUSE, \
        KC_CAPS, KC_A,    KC_S,        KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                KC_ENT,  KC_AUDIO_VOL_UP, \
        KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                KC_UP,   KC_AUDIO_VOL_DOWN, \
        KC_LCTL, KC_LGUI, TD(TD_LALT),                            KC_SPC,                             KC_RALT, MO(LO_GENMOD), KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Chat Mode */
    [LO_CHAT] = LAYOUT_65_ansi_blocker(
        CHAT_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, \
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, \
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CHAT_ENTR, _______, \
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   _______, \
        _______,  _______, _______,                            _______,                            _______, XXXXXXX, _______, _______,   _______  \
    ),
    /* General Modifiers */
    [LO_GENMOD] = LAYOUT_65_ansi_blocker(
        KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                       _______, _______, \
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______,                      _______, KC_HOME,  \
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                               _______, KC_PGUP, \
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                               _______, KC_PGDN, \
        _______,    _______, KC_LALT,                            _______,                            TG(LO_SETTINGS),  _______, KC_MEDIA_PREV_TRACK, _______, KC_MEDIA_NEXT_TRACK   \
    ),
    /* Keyboad Settings Mode */
    [LO_SETTINGS] = LAYOUT_65_ansi_blocker(
        XXXXXXX, DF(0),   DF(1),   DF(2),    DF(3),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,  RGB_M_B, RGB_TOG, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, MD_BOOT, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  RGB_VAI, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                             TG(LO_SETTINGS),  XXXXXXX, RGB_RMOD, RGB_VAD, RGB_MOD  \
    ),
    /*
    [X] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
//---KEY DEFS
        case CHAT_ENTR:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ENTER));
                layer_invert(LO_CHAT);
            }
            return false;
        case CHAT_ESC:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE));
                layer_off(LO_CHAT);
            }
            return false;
        case CSGO_Y:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_Y));
                layer_on(LO_CHAT);
            }
            return false;
        case CSGO_U:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_U));
                layer_on(LO_CHAT);
            }
            return false;
//---
        default:
            return true; //Process all other keycodes normally
    }
}
