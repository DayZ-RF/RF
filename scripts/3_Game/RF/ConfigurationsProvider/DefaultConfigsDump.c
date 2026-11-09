class RF_DefaultConfigsDump: Managed {

    // MARK: - Static Properties

    static const string ROOT_FOLDER = "$profile:RF/00_DEFAULT_CONFIGS/";

    // MARK: - Internal Static

    static bool IsEnabled() {
        return RF_ConfigurationsProvider.shared.IsCreateDefaultDumpEnabled();
    }

    static string PrepareModFolder(string modName) {
        string folder = ROOT_FOLDER + modName + "/";
        RF_File.DeleteDirectory(folder);
        RF_File.MakeDirectories(folder);
        return folder;
    }
}
