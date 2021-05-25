RGB iceBlue(void) { RGB col = {               .r = 24,    .g = 215,     .b = 204    }; return col; };
RGB lemonadePink(void) { RGB col = {          .r = 255,   .g = 114,     .b = 118    }; return col; };
RGB sexOnTheBeach_start(void) { RGB col = {   .r = 255,   .g = 144,     .b = 0      }; return col; };
RGB sexOnTheBeach_end(void) { RGB col = {     .r = 255,   .g = 0,       .b = 155    }; return col; };
RGB red(void) { RGB col = {                   .r = 255,   .g = 0,       .b = 0      }; return col; };
RGB green(void) { RGB col = {                 .r = 0,     .g = 255,     .b = 0      }; return col; };
RGB yellow(void) { RGB col = {                .r = 255,   .g = 255,     .b = 0      }; return col; };
RGB cyan(void) { RGB col = {                  .r = 0,     .g = 255,     .b = 255    }; return col; };
RGB blue(void) { RGB col = {                  .r = 0,     .g = 0,       .b = 255    }; return col; };
RGB magenta(void) { RGB col = {               .r = 255,   .g = 0,       .b = 255    }; return col; };
RGB white(void) { RGB col = {                 .r = 180,   .g = 200,     .b = 200    }; return col; };

s75_gradient_point full_white[] = {
    { .s_p = 0.00, .e_p = 1.00, .s_rgb = white, .e_rgb = white },
    { .end = true }
};

s75_gradient_point pink_lemonade[] = {
    { .s_p = 0.00, .e_p = 0.33, .s_rgb = iceBlue, .e_rgb = iceBlue },
    { .s_p = 0.33, .e_p = 0.66, .s_rgb = iceBlue, .e_rgb = lemonadePink },
    { .s_p = 0.66, .e_p = 1.00, .s_rgb = lemonadePink, .e_rgb = lemonadePink },
    { .end = true }
};

s75_gradient_point sex_on_the_beach[] = {
    { .s_p = 0.00, .e_p = 1.00, .s_rgb = sexOnTheBeach_start, .e_rgb = sexOnTheBeach_end },
    { .end = true }
};

s75_gradient_point capsicum[] = {
    { .s_p = 0.00, .e_p = 0.33, .s_rgb = red, .e_rgb = red },
    { .s_p = 0.33, .e_p = 0.66, .s_rgb = green, .e_rgb = green },
    { .s_p = 0.66, .e_p = 1.00, .s_rgb = yellow, .e_rgb = yellow },
    { .end = true }
};

// This mimics the default rainbow pattern that comes on the Drop Alt
s75_gradient_point massdrop_rainbow[] = {
    { .s_p = 0.000, .e_p = 0.167, .s_rgb = red, .e_rgb = yellow },
    { .s_p = 0.167, .e_p = 0.333, .s_rgb = yellow, .e_rgb = green },
    { .s_p = 0.333, .e_p = 0.500, .s_rgb = green, .e_rgb = cyan },
    { .s_p = 0.500, .e_p = 0.667, .s_rgb = cyan, .e_rgb = blue },
    { .s_p = 0.667, .e_p = 0.833, .s_rgb = blue, .e_rgb = magenta },
    { .s_p = 0.833, .e_p = 1.000, .s_rgb = magenta, .e_rgb = red },
    { .end = true }
};

void *gradient_setups[] = {
    sex_on_the_beach,
    pink_lemonade,
    full_white,
    capsicum,
    massdrop_rainbow
};

const uint8_t gradient_setups_count = sizeof(gradient_setups) / sizeof(gradient_setups[0]);
