class RFNotificationService: Managed {

	//MARK: - Public Methods 

	void ShowNotification(RFNotificationEntity config) {
		Param1<RFNotificationEntity> data = new Param1<RFNotificationEntity>(config);

		array<Man> players = new array<Man>;

		if (!config.players)
			GetGame().GetPlayers(players);
		else 
			players = config.players;
    	
    	foreach(auto player : players)
			GetGame().RPCSingleParam(player, RFEnum.RF_SEND_NOTIFICATION_FROM_SERVER, data, true, player.GetIdentity());		
	}
}