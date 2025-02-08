class RF_Global: Managed {

	// MARK: - Static Properties

	static ref RF_CL_RPCInstance clientRPC;

	static ref RF_SE_RPCInstance serverRPC;

	static ref RF_SoundService soundService;

	static ref RFNotificationHud rfNotificationHud;

	// MARK: - Static

	static void InitializeClientUnits() {
		clientRPC = new RF_CL_RPCInstance();
		soundService = new RF_SoundService();
		rfNotificationHud = new RFNotificationHud();
        RF_ConfigurationsProvider.shared.StartUpdateLoop();
	}

	static void InitializeServerUnits() {
		serverRPC = new RF_SE_RPCInstance();
		soundService = new RF_SoundService();
        RF_ConfigurationsProvider.shared.StartUpdateLoop();

		printWelcomeMessage();
	}

	// MARK: - Private

	private static void printWelcomeMessage() {
		Print("\n\n");
		Print("'########::'########:");
		Print(" ##.... ##: ##.....::");
		Print(" ##:::: ##: ##:::::::");
		Print(" ########:: ######:::");
		Print(" ##.. ##::: ##...::::");
		Print(" ##::. ##:: ##:::::::");
		Print(" ##:::. ##: ##:::::::");
		Print("..:::::..::..::::::::");
		Print("'########:'########:::::'###::::'##::::'##:'########:'##:::::'##::'#######::'########::'##:::'##:");
		Print(" ##.....:: ##.... ##:::'## ##::: ###::'###: ##.....:: ##:'##: ##:'##.... ##: ##.... ##: ##::'##::");
		Print(" ##::::::: ##:::: ##::'##:. ##:: ####'####: ##::::::: ##: ##: ##: ##:::: ##: ##:::: ##: ##:'##:::");
		Print(" ######::: ########::'##:::. ##: ## ### ##: ######::: ##: ##: ##: ##:::: ##: ########:: #####::::");
		Print(" ##...:::: ##.. ##::: #########: ##. #: ##: ##...:::: ##: ##: ##: ##:::: ##: ##.. ##::: ##. ##:::");
		Print(" ##::::::: ##::. ##:: ##.... ##: ##:.:: ##: ##::::::: ##: ##: ##: ##:::: ##: ##::. ##:: ##:. ##::");
		Print(" ##::::::: ##:::. ##: ##:::: ##: ##:::: ##: ########:. ###. ###::. #######:: ##:::. ##: ##::. ##:");
		Print("..::::::::..:::::..::..:::::..::..:::::..::........:::...::...::::.......:::..:::::..::..::::..::");
		Print("V 																	V");
		Print("----------------------------------------------------------------------");
		Print("-> This is a free open source framework, created by Roman and Fedor <-");
		Print("-> 				You are able to use it on your server			   <-");
		Print("-> 		You are able to monetize your server, using this mod 	   <-");
		Print("->		You are NOT able to repack this mod to your's modpack 	   <-");
		Print("----------------------------------------------------------------------");
		Print("\n\n");
	}
}