RGB_MATRIX_EFFECT(S75_GENERAL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "custom_state.h"
#include "s75_custom_gradient.c"
#include "s75_gradients.c"

bool s75_choosing_gradient = false;
int s75_selected_gradient = 0;
int s75_gradient_count = gradient_setups_count;

void setWhite(int i)                { rgb_matrix_set_color(i,   255,    255,    255); }
void setDullWhite(int i)            { rgb_matrix_set_color(i,   200,    200,    200); }
void setRed(int i)                  { rgb_matrix_set_color(i,   255,    0,      0); }
void setOrange(int i)               { rgb_matrix_set_color(i,   255,    102,    0); }
void setGreen(int i)                { rgb_matrix_set_color(i,   0,      255,    0); }
void turnOff(int i)                 { rgb_matrix_set_color(i,   0,      0,      0); }

void setDefaultColour(int i)        { s75_setCustomGradient(i, gradient_setups[s75_selected_gradient]); }

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
            setRed(i);
            return true;
        case 1 ... 12: // func keys
        case 64: // Left Arrow
        case 66: // Right Arrow
            setOrange(i);
            return true;
        case 62: // Right Alt
            setGreen(i);
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
            setDullWhite(i);
            return true;
        default:
            return false;
    }
}

bool defaultLayerIndicator(int i, int layer) {
    if (layer == biton32(default_layer_state)) {
        setGreen(i);
    } else {
        setWhite(i);
    }

    return true;
}

bool settingsLighting(int i) {
    if (IS_LAYER_OFF(_SETTINGS)) {
        return false;
    }

    // Gradient choooser
    if (s75_choosing_gradient && (i == 26 || i == 27) ) {
        setOrange(i);
        return true;
    }
    // Display a preview when selecting a gradient
    if (s75_choosing_gradient && ((i >= 45 && i <= 54) || (i >= 31 && i <= 41))) {
        setDefaultColour(i);
        return true;
    }

    switch (i) {
        /* Default Layer Selection */
        case 1: return defaultLayerIndicator(i, _BASE);
        case 2: return defaultLayerIndicator(i, _CODING);
        case 3: return defaultLayerIndicator(i, _OVERWATCH);
        case 4: return defaultLayerIndicator(i, _CSGO);
        /* End */
        case 25: // P
            if (s75_choosing_gradient) {
                setGreen(i);
            } else {
                setWhite(i);
            }
            return true;
        case 49: // B
            setRed(i);
            return true;
        case 50: // N
            setWhite(i);
            return true;
        case 62: // Right Alt
            setOrange(i);
            return true;
        default:
            // Turn off unhandled keys
            if (i >= 0 && i <= 66){
                turnOff(i);
            } else {
                setDefaultColour(i);
            }
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
