class RF_ConfigurationsProvider: Managed {

    // MARK: - Private Properties

    private string settingsPath = "$profile:RF/settings.json";

    private static ref RF_SettingsConfiguration settingsConfiguration;

    // MARK: - Init

    void RF_ConfigurationsProvider() {
        settingsConfiguration = fetchSettingsConfiguration();
    }

    // MARK: - Internal

    RF_SettingsConfiguration GetSettingsConfiguration() {
        return settingsConfiguration;
    }

    void SetSettingsConfiguration(RF_SettingsConfiguration configuration) {
        writeSettingsConfuguration(configuration);
    }

    // MARK: - Private

    private RF_SettingsConfiguration fetchSettingsConfiguration() {
        makeDirectory();
        RF_SettingsConfiguration configuration = loadSettingsConfiguration();
        if (!configuration) {
            configuration = settingsExample();
            if (FileExist(settingsPath)) {
                Print("Configuration file is damaged. I'm going to use default configuration. Repair configuration file or remove it and restart server");
            } else {
                Print("Configuration file doesn't exist. I'm going to write and use default configuration at: " + settingsPath);
                writeSettingsConfuguration(configuration);
            }
        }
        return configuration;
    }

    private void makeDirectory() {
        string rfFolder = "$profile:RF/";

        if (!FileExist(rfFolder)) MakeDirectory(rfFolder);
    }

    private RF_SettingsConfiguration loadSettingsConfiguration() {
        RF_SettingsConfiguration configuration;
        JSONService<RF_SettingsConfiguration>.ReadFile(settingsPath, configuration);
        return configuration;
    }

    private void writeSettingsConfuguration(RF_SettingsConfiguration configuration) {
        JSONService<RF_SettingsConfiguration>.WriteFile(settingsPath, configuration);
    }

    private RF_SettingsConfiguration settingsExample() {
        RF_SettingsConfiguration object = new RF_SettingsConfiguration();
        object._logsLevelComment = "New value applies on restart. 0 - Nothing, 1 - Info, 2 - Warning, 3 - Error";
        object.logsLevel = 0;
        return object;
    }
}