# Notification 


### RFNotificationEntity

| Variable name     | Type                            | default value |
|-------------------|---------------------------------|---------------|
| title             | string                          | ""            |
| message           | string                          | ""            |
| lifetime          | int                             | 5             |
| viewConfiguration | RFNotificationViewConfiguration | object        |
| players           | array<Man>                      | {}            |


### RFNotificationViewConfiguration

| Variable name   | Type   | default value             |
|-----------------|--------|---------------------------|
| titleColor      | int    | ARGB(255, 255, 255, 255)  |
| textColor       | int    | ARGB(255, 255, 255, 255)  |
| borderColor     | int    | ARGB(255, 8, 123, 37)     |
| backgroundColor | int    | ARGB(255, 48, 48, 48)     |
| margin          | int    | 20                        |
| iconPath        | string | "RF/GUI/icons/alarm.edds" |

### Example

##### Broadcast message

```csharp
private void sendBroadcastNotification(array<PlayerBase> players) {
	RFNotificationEntity entity = new RFNotificationEntity();
	entity.title = "Example title";
	entity.message = "Example message";
	entity.lifetime = 15 // in seconds
	RFNotificationService notificationSerivce = new RFNotificationService();
	notificationSerivce.ShowNotification(entity);
}
```

##### Broadcast message

```csharp
private void sendNotificationToConcretePlayers(array<PlayerBase> players) {
	RFNotificationEntity entity = new RFNotificationEntity();
	entity.title = "Example title";
	entity.message = "Example message";
	entity.lifetime = 15 // in seconds
	entiry.players = player;
	RFNotificationService notificationSerivce = new RFNotificationService();
	notificationSerivce.ShowNotification(entity);
}
```


##### Configuring colors and borders

```csharp
private void sendNotificationToConcretePlayers() {
	RFNotificationEntity entity = new RFNotificationEntity();
	entity.title = "Example title";
	entity.message = "Example message";
	entity.viewConfiguration.titleColor = ARGB(255, 255, 255, 255);
	entity.viewConfiguration.textColor = ARGB(255, 255, 255, 255);
	entity.viewConfiguration.borderColor = ARGB(255, 8, 123, 37);
	entity.viewConfiguration.backgroundColor = ARGB(255, 48, 48, 48);
	entity.viewConfiguration.margin = 20;
	entity.viewConfiguration.iconPath = "RF/GUI/icons/alarm.edds";

	RFNotificationService notificationSerivce = new RFNotificationService();
	notificationSerivce.ShowNotification(entity);
}
```