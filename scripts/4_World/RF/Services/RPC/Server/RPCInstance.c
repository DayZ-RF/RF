class RF_SE_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_Constant.RPC_TYPE; }

    override string GetModName() { return RF_Constant.MOD_NAME; }

    // MARK: - Internal

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
    }
}
