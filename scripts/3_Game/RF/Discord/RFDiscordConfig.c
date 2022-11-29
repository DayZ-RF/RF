// Config with webhooks
class RFDiscordConfig: Managed {

	// List of available webhooks
	autoptr array<ref RFDiscordWebhook> webhooks = {};
}
