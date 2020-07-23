bool chatLighting(int i) {
    if (IS_LAYER_OFF(_CHAT)) {
        return false;
    }

    switch (i) {
        case 0: // Escape
            setRed(i);
            return true;
        case 42: // Enter
            setGreen(i);
            return true;
        default:
            setDefaultColour(i);
            return true;
    }
}
