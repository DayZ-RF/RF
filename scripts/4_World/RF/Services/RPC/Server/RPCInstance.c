class RF_SE_RPCInstance: RF_RPCInstance {

    // MARK: - Internal

    void Send(string key, RF_Sound param1, RF_SoundModel param2, PlayerIdentity playerIdentity = null) {
        Param4<string, string, RF_Sound, RF_SoundModel> param = new Param4<string, string, RF_Sound, RF_SoundModel>(GetModName(), key, param1, param2);
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
			case "removeSound": {
				removeSound(sender, ctx);
				break;
			}
		}
	}

	// MARK: - Private

	private void getSound(PlayerIdentity sender, ParamsReadContext ctx) {
		RF_Sound sound;

		if (!ctx.Read(sound)) return;

		if (sound) Send("getSound", sound, sound.GetModel(), sender);
	}

	private void removeSound(PlayerIdentity sender, ParamsReadContext ctx) {
		RF_Sound sound;

		if (!ctx.Read(sound)) return;

		if (sound) sound.Delete();
	}
}