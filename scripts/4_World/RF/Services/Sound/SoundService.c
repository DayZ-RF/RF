class RF_SoundService: Managed {

    // MARK: - Private Properties

    private static int s_nextId = 1;
    private ref map<int, ref RF_Sound> m_sounds = new map<int, ref RF_Sound>();

    // MARK: - Internal

    RF_Sound Play(vector position, string soundSet, bool loop = false) {
        auto sound = new RF_Sound();
        sound.id = s_nextId++;
        sound.soundSet = soundSet;
        sound.position = position;
        sound.loop = loop;

        if (GetGame().IsServer()) {
            auto data = new RF_SoundData();
            data.id = sound.id;
            data.soundSet = soundSet;
            data.position = position;
            data.loop = loop;
            RF_Global.serverRPC.Send("playSound", data);
        } else {
            sound.PlayOnClient();
        }

        if (loop) {
            m_sounds.Set(sound.id, sound);
        }

        return sound;
    }

    void Stop(RF_Sound sound) {
        if (!sound) return;

        if (GetGame().IsServer()) {
            RF_Global.serverRPC.Send("stopSound", sound.id);
        } else {
            sound.StopOnClient();
        }

        m_sounds.Remove(sound.id);
    }

    // MARK: - Sync

    void SyncLoopSounds(PlayerIdentity player) {
        foreach (int id, RF_Sound sound : m_sounds) {
            auto data = new RF_SoundData();
            data.id = sound.id;
            data.soundSet = sound.soundSet;
            data.position = sound.position;
            data.loop = true;
            RF_Global.serverRPC.Send("playSound", data, player);
        }
    }

    // MARK: - Client RPC Handlers

    void HandlePlaySound(RF_SoundData data) {
        if (!data) return;

        if (data.loop) {
            auto sound = new RF_Sound();
            sound.id = data.id;
            sound.soundSet = data.soundSet;
            sound.position = data.position;
            sound.loop = true;
            sound.PlayOnClient();
            m_sounds.Set(sound.id, sound);
        } else {
            SEffectManager.PlaySound(data.soundSet, data.position);
        }
    }

    void HandleStopSound(int soundId) {
        auto sound = m_sounds.Get(soundId);
        if (sound) {
            sound.StopOnClient();
            m_sounds.Remove(soundId);
        }
    }
}
