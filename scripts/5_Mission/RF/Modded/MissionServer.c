modded class MissionServer {

    // MARK: - Override

    override void OnInit() {
        super.OnInit();

        RF_Global.InitializeServerUnits();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);

        if (RF_Global.soundService) RF_Global.soundService.SyncLoopSounds(identity);
    }
}
