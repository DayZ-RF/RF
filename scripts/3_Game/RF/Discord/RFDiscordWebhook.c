// Webhook data
class RFDiscordWebhook: Managed {

	// Webhook type
	string name;

	// URL adresses of webhook type
	// You can enter many text channels URLs
	autoptr array<ref string> endpoints = {};
}
