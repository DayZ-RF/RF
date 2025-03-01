modded class MissionServer {

    // MARK: - Override

    override void OnInit() {
        super.OnInit();

        RF_Global.InitializeServerUnits();
    }
}
