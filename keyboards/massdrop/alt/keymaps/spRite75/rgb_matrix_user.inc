RGB_MATRIX_EFFECT(S75_GENERAL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void setDefaultColour(int i) {
    rgb_matrix_set_color(i, 24, 215, 204);
}

void turnOff(int i) {
    rgb_matrix_set_color(i, 0, 0, 0);
}

void defaultLighting(int i) {
    switch (i) {
        case 29: // 2nd right hand button
        case 43: // 3rd right hand button
        case 57: // 4th right hand button
            turnOff(i);
            return;
        default:
            setDefaultColour(i);
            return;
    }
}

bool genmodLighting(int i) {
    if (IS_LAYER_OFF(_GENMOD)) {
        return false;
    }

    switch (i) {
        case 0: // esc
            rgb_matrix_set_color(i, 255, 0, 0);
            return true;
        case 1 ... 12: // func keys
        case 64: // Left Arrow
        case 66: // Right Arrow
            rgb_matrix_set_color(i, 255, 102, 0);
            return true;
        case 62: // Right Alt
            rgb_matrix_set_color(i, 0, 255, 0);
            return true;
        case 29: // 2nd right hand button
        case 43: // 3rd right hand button
        case 57: // 4th right hand button
            setDefaultColour(i);
            return true;
        default:
            return false;
    }
}

bool codingLighting(int i) {
    if (_CODING != biton32(default_layer_state)) {
        return false;
    }

    switch (i) {
        case 40: // ;
        case 41: // '
        case 44: // Left Shift
        case 55: // Right Shift
        case 11: // -
            rgb_matrix_set_color(i, 200, 200, 200);
            return true;
        default:
            return false;
    }
}

bool settingsLighting(int i) {
    if (IS_LAYER_OFF(_SETTINGS)) {
        return false;
    }

    switch (i) {
        default:
            turnOff(i);
            return true;
    }
}

bool S75_GENERAL(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        bool handled = settingsLighting(i);

        if (!handled) {
            handled = genmodLighting(i);
        }

        if (!handled) {
            handled = codingLighting(i);
        }

        if (!handled) {
            defaultLighting(i);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
