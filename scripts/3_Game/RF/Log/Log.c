class RF_Log: Managed {

    // MARK: - Internal Properties

    string GetModName() {
        return "RF";
    }

    // MARK: - Internal

    void Info(string message) {
        auto settingsConfiguration = RF_ConfigurationsProvider.shared.GetSettingsConfiguration();
        if (settingsConfiguration && settingsConfiguration.logsLevel > 2) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Info", message));
        }
    }

    void Warning(string message) {
        auto settingsConfiguration = RF_ConfigurationsProvider.shared.GetSettingsConfiguration();
        if (settingsConfiguration && settingsConfiguration.logsLevel > 1) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Warning", message));
        }
    }

    void Error(string message) {
        auto settingsConfiguration = RF_ConfigurationsProvider.shared.GetSettingsConfiguration();
        if (settingsConfiguration && settingsConfiguration.logsLevel > 0) {
            Print(string.Format("[%1][%2][%3]: %4", RF_TimeStamp.Now().Formatted(), GetModName(), "Error", message));
        }
    }
}
