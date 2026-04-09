class RF_Sound: Managed {

    // MARK: - Internal Properties

    int id;
    string soundSet;
    vector position;
    bool loop;

    // MARK: - Private Properties

    private EffectSound m_effectSound;

    // MARK: - Internal

    void PlayOnClient() {
        m_effectSound = SEffectManager.PlaySound(soundSet, position, 0, 0, loop);
        if (m_effectSound) {
            m_effectSound.SetSoundAutodestroy(!loop);
        }
    }

    void StopOnClient() {
        if (m_effectSound) {
            m_effectSound.SoundStop();
            m_effectSound = null;
        }
    }
}
