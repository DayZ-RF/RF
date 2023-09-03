class RF_Color: Managed {

    // MARK: - Public Properties

    int a, r, g, b;

    // MARK: - Init

    void RF_Color(int A = 255, int R = 0, int G = 0, int B = 0) {
        this.a = A;
        this.r = R;
        this.g = G;
        this.b = B;
    }

    // MARK: - Public Methods

    void ConfigureWith(int A, int R, int G, int B) {
        this.a = A;
        this.r = R;
        this.g = G;
        this.b = B;
    }

    void ConfigureWith(int color) {
        this.a = (color >> 24) & 0xFF;
        this.r = (color >> 16) & 0xFF;
        this.g = (color >> 8) & 0xFF;
        this.b = color & 0xFF;
    }

    int GetColorInt() {
        return ARGB(this.a, this.r, this.g, this.b);
    }

    // MARK: - Static Methods

    static void ToARGB(int color, out int A, out int R, out int G, out int B) {
        A = (color >> 24) & 0xFF;
        R = (color >> 16) & 0xFF;
        G = (color >> 8) & 0xFF;
        B = color & 0xFF;
    }
}