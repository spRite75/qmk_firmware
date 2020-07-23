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
void setBlue(int i)                 { rgb_matrix_set_color(i,   0,      0,      255); }
void setYellow(int i)               { rgb_matrix_set_color(i,   255,    255,    0); }
void setMagenta(int i)              { rgb_matrix_set_color(i,   255,    0,      255); }
void turnOff(int i)                 { rgb_matrix_set_color(i,   0,      0,      0); }

void setDefaultColour(int i)        { s75_setCustomGradient(i, gradient_setups[s75_selected_gradient]); }

#include "lighting/chat.c"
#include "lighting/coding.c"
#include "lighting/csgo.c"
#include "lighting/default.c"
#include "lighting/genmod.c"
#include "lighting/overwatch.c"
#include "lighting/settings.c"

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
            handled = chatLighting(i);
        }

        if (!handled) {
            handled = overwatchLighting(i);
        }

        if (!handled) {
            handled = csgoLighting(i);
        }

        if (!handled) {
            defaultLighting(i);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
