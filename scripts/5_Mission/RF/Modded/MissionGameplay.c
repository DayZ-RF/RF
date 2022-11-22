modded class MissionGameplay { 
	
	// MARK: - Override methods  ----------------------------------
	autoptr RFNotificationHud rfNotificationHud;

	override void OnInit() { 
		super.OnInit(); 
		rfNotificationHud = new RFNotificationHud(); 
	}
}