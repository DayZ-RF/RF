class RF_Sound: ItemBase {

    // MARK: - Private Properties

    private autoptr EffectSound sound;

    private autoptr RF_SoundModel model;

    private bool isRemovePending;

    // MARK: - Internal Properties

    Managed delegate;

    // MARK: - Init

    void RF_Sound() {
        if (GetGame().IsClient()) SetEventMask(EntityEvent.FRAME);
    }

    void ~RF_Sound() {
        if (delegate) GetGame().GameScript.CallFunctionParams(delegate, "didRemoveSound", NULL, new Param1<RF_Sound>(this));
        if (GetGame().IsClient()) teardownClient();
    }

    // MARK: - Internal

    RF_SoundModel GetModel() {
        return model;
    }

    void SetModel(RF_SoundModel _model) {
        model = _model;

        if (GetGame().IsClient()) {
            if (sound) StopSoundSet(sound);

            isRemovePending = false;

            sound = SEffectManager.PlaySound(model.soundSet, GetPosition());
            sound.SetSoundLoop(model.loop);
            sound.SetSoundAutodestroy(true);
        }
    }

    // MARK: - Override

    override void EEInit() {
        if (GetGame().IsClient()) setupClient();
    }

    override void EOnFrame(IEntity other, float timeSlice) {
        if (!isRemovePending && !sound && model) {
            isRemovePending = true;
            RF_Global.clientRPC.Send("removeSound", this);
        }
    }

    override bool IsParticle() {
        return true;
    }

    override bool IsTakeable() {
        return false;
    }

    // MARK: - Private

    private void setupClient() {
        RF_Global.clientRPC.Send("getSound", this);
    }

    private void teardownClient() {
        if (sound) StopSoundSet(sound);
    }
}
