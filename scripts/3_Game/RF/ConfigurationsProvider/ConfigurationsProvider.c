class RF_ConfigurationsProvider: Managed {

    // MARK: - Static Properties

    static ref RF_ConfigurationsProvider shared = new RF_ConfigurationsProvider();

    // MARK: - Private Properties

    private string settingsPath = "$profile:RF/settings.json";

    private autoptr RF_SettingsConfiguration settingsConfiguration;

    private autoptr Timer timer;

    // MARK: - Init

    void RF_ConfigurationsProvider() {
        updateSettingsConfiguration();
        auto settingsExample = settingsExample();
        settingsConfiguration._comment = settingsExample._comment;
        settingsConfiguration._logsLevelComment = settingsExample._logsLevelComment;
        settingsConfiguration._gmtComment = settingsExample._gmtComment;
        writeSettingsConfuguration(settingsConfiguration);
    }

    // MARK: - Internal

    void StartUpdateLoop() {
        timer = new Timer();
        timer.Run(10.0, this, "updateSettingsConfiguration", NULL, true);
    }

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
        object._comment = "New value applies in 10 seconds.";
        object._logsLevelComment = "0 - Nothing, 1 - Error, 2 - Error + Warning, 3 - Error + Warning + Info.";
        object.logsLevel = 2;
        object._gmtComment = "Format: HHMM. First two digits is hours, second two digits is minutes. For example: 300 - Moscow, -500 - New York, 0 - London.";
        object.gmt = 0;
        return object;
    }

    private void updateSettingsConfiguration() {
        settingsConfiguration = fetchSettingsConfiguration();
    }
}
