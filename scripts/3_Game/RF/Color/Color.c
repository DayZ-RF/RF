class RF_Color: Managed {

    static void ToARGB(int color, out int A, out int R, out int G, out int B) {
        A = (color >> 24) & 0xFF;
        R = (color >> 16) & 0xFF;
        G = (color >> 8) & 0xFF;
        B = color & 0xFF;
    }
}