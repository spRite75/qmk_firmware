typedef struct {
  float s_p;
  RGB (*s_rgb)(void);
  float e_p;
  RGB (*e_rgb)(void);
  bool end;
} s75_gradient_point;

RGB s75_calculateColourForGradient(float pct, RGB s_rgb, RGB e_rgb) {
  // Here we'll calculate the desired gradient once I understand a bit more RGB colour space theory...
  RGB colour;
  colour.r = s_rgb.r * (1 - pct) + e_rgb.r * pct;
  colour.g = s_rgb.g * (1 - pct) + e_rgb.g * pct;
  colour.b = s_rgb.b * (1 - pct) + e_rgb.b * pct;
  return colour;
}

void s75_setCustomGradient(int led_index, s75_gradient_point *points) {
  float led_x_percent = (float)g_led_config.point[led_index].x / (MAX_X - MIN_X);
  for (int i = 0; i < S75_MAX_GRADIENT_POINTS; i++) {
    if (points[i].end) return;
    if (
      led_x_percent >= points[i].s_p &&
      led_x_percent <= points[i].e_p
    ) {
      float gradient_x_percent = (led_x_percent - points[i].s_p) / (points[i].e_p - points[i].s_p);
      RGB colour = s75_calculateColourForGradient(
        gradient_x_percent,
        points[i].s_rgb(),
        points[i].e_rgb()
      );
      rgb_matrix_set_color(
        led_index, 
        colour.r, 
        colour.g, 
        colour.b
      );
      return;
    }
  }
}
