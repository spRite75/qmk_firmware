bool csgoLighting(int i) {
    if (_CSGO != biton32(default_layer_state)) {
        return false;
    }

    // Don't handle edge, left alt, or fn
    if (i > 66 || i == 60 || i == 63) {
        return false;
    }

    switch (i) {
        // Inventory
        case 1 ... 3:
        case 5:
            setYellow(i);
            return true;
        // Movement
        case 17: // W
        case 31 ... 33: // A - D
        case 44: // Left shift
        case 58: // Left ctrl
        case 61: // Space
            setBlue(i);
            return true;
        // Abilities
        case 16: // Q
        case 18: // E
        case 19: // R
        case 34: // F
        case 35: // G
        case 49: // B
            setOrange(i);
            return true;
        // Grenades
        case 47:
        case 48:
            setGreen(i);
            return true;
        // Communication
        case 21: // Y
        case 22: // U
        case 30: // Capslock
        case 45: // Z
            setMagenta(i);
            return true;
        default:
            turnOff(i);
            return true;
    }
}
