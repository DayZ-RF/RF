class RF_Log: Managed {

    // MARK: - Internal Properties

    string GetModName() {
        return "RF";
    }

    // MARK: - Internal

    void Warning(string message) {
        Print(string.Format("[%1][%2]: %3", GetModName(), "Warning", message));
    }

    void Info(string message) {
        Print(string.Format("[%1][%2]: %3", GetModName(), "Info", message));
    }

    void Error(string message) {
        Print(string.Format("[%1][%2]: %3", GetModName(), "Error", message));
    }
}