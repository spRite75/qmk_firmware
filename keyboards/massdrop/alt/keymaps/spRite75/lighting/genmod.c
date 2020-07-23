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
