class RF_RPCInstance: Managed {

    // MARK: - Internal Properties

    int GetRPCType() { return 0; }

    string GetModName() { return "RF"; }

    // MARK: - Life Cycle

    void RF_RPCInstance() {
        auto game = GetDayZGame();
        if (game) game.Subscribe(this, "OnRPC");
    }

    void ~RF_RPCInstance() {
        auto game = GetDayZGame();
        if (game) game.Unsubscribe(this, "OnRPC");
    }

    // MARK: - Subscribe
    
    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type != GetRPCType()) return;

        int countOfParams;
        string modName;
        string key;
        ctx.Read(countOfParams);
        ctx.Read(modName);
        ctx.Read(key);

        if (countOfParams != 3) return;
        if (modName != GetModName()) return;
        if (!key) return;

        Handle(sender, key, ctx);
    }

    // MARK: - Internal

    void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {}
}