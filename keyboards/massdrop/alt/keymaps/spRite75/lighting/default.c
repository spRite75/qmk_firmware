void defaultLighting(int i) {
    switch (i) {
        case 29: // 2nd right hand button
        case 43: // 3rd right hand button
        case 57: // 4th right hand button
            turnOff(i);
            return;
        default:
            setDefaultColour(i);
            return;
    }
}
