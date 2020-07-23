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

    // Don't handle edge, left alt, or fn
    if (i > 66) {
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
            turnOff(i);
            return true;
    }
}
