bool codingLighting(int i) {
    if (_CODING != biton32(default_layer_state)) {
        return false;
    }

    switch (i) {
        case 40: // ;
        case 41: // '
        case 44: // Left Shift
        case 55: // Right Shift
            setDullWhite(i);
            return true;
        default:
            return false;
    }
}
