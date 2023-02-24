// Discord webhook service
class RFDiscordService: Managed {

	// MARK: - Private Properties

	private autoptr array<ref RFDispatchItem> items = {};

	private bool isRequestProcessing;

	private ref RFDiscordConfig config;

	private ref Timer runTimer = new Timer();

	private ref Timer pauseTimer = new Timer();

	// MARK: - Life Cycle

	void RFDiscordService() {
		loadConfig(config);
		runTimer.Run(0.25, this, "Tick", NULL, true);
	}

	// MARK: - Public

	// Send message to Discord channels
	//
	// - name: Webhook type
	// - message: Message Content
	void Send(string name, string message) {
		RFDiscordWebhook webhook = getOptionalWebhook(config, name);
		if (!webhook) return;
		foreach (string endpoint : webhook.endpoints) {
			RFDispatchItem item = new RFDispatchItem();
			item.endpoint = endpoint;
			item.message = message;
			items.Insert(item);
			if (items.Count() == 1) {
				ResumeTimer();
			}
		}
	}

	// Send message to Discord channels
	//
	// - endpoint: Webhook URL
	// - message: Message Content
	void SendToEndpoint(string endpoint, string message) {
		RFDispatchItem item = new RFDispatchItem();
		item.endpoint = endpoint;
		item.message = message;
		items.Insert(item);
		if (items.Count() == 1) {
			ResumeTimer();
		}
	}

	// MARK: - Timer Targets (Do not call it yourself)

	void StopTimerForAWhile() {
		PauseTimer();
		isRequestProcessing = false;
		pauseTimer.Run(10.0, this, "ResumeTimer", NULL, true);
	}

	void PauseTimer() {
		runTimer.Pause();
	}

	void ResumeTimer() {
		pauseTimer.Stop();
		runTimer.Continue();
	}

	void Tick() {
		if (items.Count() == 0) {
			PauseTimer();
			return;
		}
		if (isRequestProcessing) return;
		isRequestProcessing = true;
		RFDiscordCallback callback = new RFDiscordCallback();
		callback.delegate = this;
		RFDispatchItem item = items[0];
		RFDiscordData object = new RFDiscordData();
		object.content = item.message;
		string data = JSONService<RFDiscordData>.WriteString(object);
		RestContext ctx = GetRestApi().GetRestContext(item.endpoint);
		ctx.SetHeader("application/json");
		ctx.POST(callback, "", data);
	}

	// MARK: - Callback Delegate Protocol (Do not call it yourself)

	void LimitExceeded(RFDiscordCallback callback) {
		StopTimerForAWhile();
	}

	void OnSuccess(RFDiscordCallback callback) {
		items.RemoveOrdered(0);
		isRequestProcessing = false;
	}

	// MARK: - Private

	private void loadConfig(out RFDiscordConfig Config) {
		string rfFolder = "$profile:RF/";
		string discordFolder = rfFolder + "DISCORD/";
		string path = discordFolder + "config.json";
		if (!FileExist(rfFolder)) MakeDirectory(rfFolder);
		if (!FileExist(discordFolder)) MakeDirectory(discordFolder);
		JSONService<RFDiscordConfig>.ReadFile(path, Config);
		if (!Config) {
			Config = new RFDiscordConfig();
			RFDiscordWebhook newWebhook = new RFDiscordWebhook();
			newWebhook.name = "type [edit me]";
			newWebhook.endpoints = {"https://discord.com/api/webhooks/[edit me]/[edit me]", "https://discord.com/api/webhooks/[edit me]/[edit me]"};
			Config.webhooks.Insert(newWebhook);
		}
		JSONService<RFDiscordConfig>.WriteFile(path, Config);
	}

	private RFDiscordWebhook getOptionalWebhook(out RFDiscordConfig Config, string name) {
		foreach (RFDiscordWebhook webhook : Config.webhooks) {
			if (webhook.name == name) return webhook;
		}
		return null;
	}
}
