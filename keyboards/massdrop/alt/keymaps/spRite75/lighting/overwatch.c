bool overwatchLighting(int i) {
    if (_OVERWATCH != biton32(default_layer_state)) {
        return false;
    }

    // Don't handle edge, left alt, or fn
    if (i > 66 || i == 60 || i == 63) {
        return false;
    }

    switch (i) {
        // Movement
        case 17: // W
        case 31 ... 33: // A - D
        case 58: // Left ctrl
        case 61: // Space
            setBlue(i);
            return true;
        // Ultimate
        case 16: // Q
            setYellow(i);
            return true;
        // Abilities
        case 18: // E
        case 34: // F
        case 44: // Left shift
            setOrange(i);
            return true;
        // Communication
        case 30: // Capslock
        case 42: // Enter
        case 45 ... 47: // Z - C
            setMagenta(i);
            return true;
        default:
            turnOff(i);
            return true;
    }
}
