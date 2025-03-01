class RF_CL_RPCInstance: RF_RPCInstance {

    // MARK: - Internal

    void Send(string key, RF_Sound param1, PlayerIdentity playerIdentity = null) {
        Param3<string, string, RF_Sound> param = new Param3<string, string, RF_Sound>(GetModName(), key, param1);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    // MARK: - Internal

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
        switch (key) {
            case "getSound": {
                getSound(sender, ctx);
                break;
            }
        }
    }

    // MARK: - Private

    private void getSound(PlayerIdentity sender, ParamsReadContext ctx) {
        RF_Sound sound;
        RF_SoundModel soundModel;

        if (!ctx.Read(sound)) return;
        if (!ctx.Read(soundModel)) return;

        if (sound) sound.SetModel(soundModel);
    }
}
