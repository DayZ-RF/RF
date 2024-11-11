class RF_Log: Managed {

    // MARK: - Internal Properties

    string GetModName() {
        return "RF";
    }

    // MARK: - Internal

    void Warning(string message) {
        Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Warning", message));
    }

    void Info(string message) {
        Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Info", message));
    }

    void Error(string message) {
        Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Error", message));
    }
}