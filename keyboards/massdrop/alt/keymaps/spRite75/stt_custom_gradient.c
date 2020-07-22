/*
  Custom gradient effect by SirTimmyTimbit
  source: https://github.com/SirTimmyTimbit/customizable-gradient-effect-for-drop-alt/blob/master/stt_custom_gradient.c

  Modified to work with my S75_GENERAL RGB effect
*/

HSV STT_INTERPOLATE_HSV(float step, HSV gradient_0, HSV gradient_100) {
    uint8_t cw, ccw;
    HSV color;

    cw = (gradient_0.h >= gradient_100.h) ? 255 + gradient_100.h - gradient_0.h : gradient_100.h - gradient_0.h;  // Hue range is 0 to 255.
    ccw = (gradient_0.h >= gradient_100.h) ? gradient_0.h - gradient_100.h : 255 + gradient_0.h - gradient_100.h;

    if( cw < ccw ) { // going clockwise
        color.h = gradient_0.h + (uint8_t)(step * cw);
    } else { // Going counter clockwise
        color.h = gradient_0.h - (uint8_t)(step * ccw);
    }

    color.s = gradient_0.s + step * (gradient_100.s - gradient_0.s);

    // Scale V with global RGB Matrix's V, so users can still control overall brightness with RGB_VAI & RGB_VAD0
    color.v = round((gradient_0.v + step * (gradient_100.v - gradient_0.v)) * ((float)rgb_matrix_config.hsv.v / 255));

    return color;
}

HSV STT_CUSTOM_GRADIENT_math(
  uint8_t led_x,
  uint8_t min_x,
  uint8_t max_x,
  HSV stt_gradient_0,
  HSV stt_gradient_100,
  bool stt_reflected_gradient
) {
    float step = (float)led_x / (max_x - min_x);
    float mid_gradient_pos = 0.5;

    if( stt_reflected_gradient ) {
        if( step <= mid_gradient_pos ) {
            return STT_INTERPOLATE_HSV(step * (1/mid_gradient_pos), stt_gradient_0, stt_gradient_100);
        } else {
            return STT_INTERPOLATE_HSV((step - mid_gradient_pos) * (1/(1-mid_gradient_pos)), stt_gradient_100, stt_gradient_0);
        }

    } else {
        return STT_INTERPOLATE_HSV(step, stt_gradient_0, stt_gradient_100);
    }
}

static void stt_setCustomGradient(int i, HSV stt_gradient_0, HSV stt_gradient_100) {
    uint8_t min_x = 0;  // X coordinate of the left-most LED
    uint8_t max_x = 224; // X coordinate of the right-most LED

    HSV hsv_orig = STT_CUSTOM_GRADIENT_math(
      g_led_config.point[i].x,
      min_x,
      max_x,
      stt_gradient_0,
      stt_gradient_100,
      false
    );
    RGB rgb = hsv_to_rgb(hsv_orig);

    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}
