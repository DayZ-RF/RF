
class RF_UUID: Managed {

    static string New() {
        autoptr array<string> chars = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
        autoptr array<int> dashes = {8, 13, 18, 23};
        string buf = "";

        for (int i = 0; i < 36; i++) {
            if (dashes.Find(i) == -1) {
                buf = buf + chars.GetRandomElement();
            } else {
                buf = buf + "-";
            }
        }

        return buf;
    }
}
