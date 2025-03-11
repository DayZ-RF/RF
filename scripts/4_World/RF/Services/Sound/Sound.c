class RF_Sound: ItemBase {

    // MARK: - Private Properties

    private autoptr EffectSound rfSound;

    private autoptr RF_SoundModel rfModel;

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
        return rfModel;
    }

    void SetModel(RF_SoundModel _model) {
        rfModel = _model;

        if (GetGame().IsClient()) {
            if (rfSound) StopSoundSet(rfSound);

            isRemovePending = false;

            rfSound = SEffectManager.PlaySound(rfModel.soundSet, GetPosition());
            rfSound.SetSoundLoop(rfModel.loop);
            rfSound.SetSoundAutodestroy(true);
        }
    }

    // MARK: - Override

    override void EEInit() {
        if (GetGame().IsClient()) setupClient();
    }

    override void EOnFrame(IEntity other, float timeSlice) {
        if (!isRemovePending && !rfSound && rfModel) {
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
        if (rfSound) StopSoundSet(rfSound);
    }
}