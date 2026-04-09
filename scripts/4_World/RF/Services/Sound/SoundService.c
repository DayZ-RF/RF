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
            TStringArray data = {sound.id.ToString(), soundSet, position[0].ToString(), position[1].ToString(), position[2].ToString(), loop.ToString()};
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

    // MARK: - Client RPC Handlers

    void HandlePlaySound(TStringArray data) {
        if (!data || data.Count() < 6) return;

        auto sound = new RF_Sound();
        sound.id = data[0].ToInt();
        sound.soundSet = data[1];
        sound.position = Vector(data[2].ToFloat(), data[3].ToFloat(), data[4].ToFloat());
        sound.loop = data[5].ToInt() != 0;
        sound.PlayOnClient();

        if (sound.loop) {
            m_sounds.Set(sound.id, sound);
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
