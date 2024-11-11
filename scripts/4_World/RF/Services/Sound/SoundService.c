class RF_SoundService: Managed {

	// MARK: - Internal

	RF_Sound Play(vector position, string soundSet, bool loop = false, Managed delegate = null) {
		auto object = GetGame().CreateObject("RF_Sound", position, GetGame().IsClient());
		if (!object) {
			RF_Log().Error(string.Format("Can not create sound %1 at %2", soundSet, position));
			return null;
		}

		auto sound = RF_Sound.Cast(object);
		if (!sound) {
			RF_Log().Error(string.Format("Sound %1 at %2 is not inherited from RF_Sound", soundSet, position));
			return null;
		}

		auto model = new RF_SoundModel();
		model.soundSet = soundSet;
		model.loop = loop;
		sound.delegate = delegate;
		sound.SetModel(model);

		return sound;
	}

	void Stop(RF_Sound sound) {
		if (sound) sound.Delete();
	}
}