class RF_CL_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_Constant.RPC_TYPE; }

    override string GetModName() { return RF_Constant.MOD_NAME; }

    // MARK: - Internal

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
        switch (key) {
            case "playSound": {
                TStringArray data;
                if (ctx.Read(data)) RF_Global.soundService.HandlePlaySound(data);
                break;
            }
            case "stopSound": {
                int soundId;
                if (ctx.Read(soundId)) RF_Global.soundService.HandleStopSound(soundId);
                break;
            }
        }
    }
}
