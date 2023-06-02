# RFDiscordService

Discord service allows to send message from DayZ SA to Discord text channels

## Initialization

Initialize service. After **config.json** file will be generated in **$profiles/rf/discord/** if it doesn't exist

```csharp

RFDiscordService service = new RFDiscordService();

```

## Config

You can specify as many webhooks as you want. Also it is possible to specify more than one webhook endpoint to send message

```json

{
	"webhooks": [
		{
			"name": "All",
			"endpoints": [
				"https://discord.com/api/webhooks/[edit me]/[edit me]"
			]
		},
		{
			"name": "Kills",
			"endpoints": [
				"https://discord.com/api/webhooks/[edit me]/[edit me]"
				"https://discord.com/api/webhooks/[edit me]/[edit me]"
			]
		}
	]
}

```

## Sending messages

Send messages using type of webhook

```csharp

service.Send("All", "Server Launched");
service.Send("Kills", "Animal killed Zombie");
service.Send("Kills", "Zombie killed Animal");

```
