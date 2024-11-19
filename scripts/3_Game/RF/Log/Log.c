class RF_Log: Managed {

    // MARK: - Static Properties

    static ref RF_ConfigurationsProvider configurationsProvider = new RF_ConfigurationsProvider();

    // MARK: - Internal Properties

    string GetModName() {
        return "RF";
    }

    // MARK: - Internal

    void Info(string message) {
        if (configurationsProvider.GetSettingsConfiguration().logsLevel > 0) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Info", message));
        }
    }

    void Warning(string message) {
        if (configurationsProvider.GetSettingsConfiguration().logsLevel > 1) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Warning", message));
        }
    }

    void Error(string message) {
        if (configurationsProvider.GetSettingsConfiguration().logsLevel > 2) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Error", message));
        }
    }
}