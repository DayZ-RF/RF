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

    // MARK: - Internal

    void Send(string key, PlayerIdentity playerIdentity = null) {
        Param2<string, string> param = new Param2<string, string>(GetModName(), key);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    void Send(string key, int rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, int> param = new Param3<string, string, int>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    void Send(string key, float rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, float> param = new Param3<string, string, float>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    void Send(string key, vector rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, vector> param = new Param3<string, string, vector>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    void Send(string key, string rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, string> param = new Param3<string, string, string>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }

    void Send(string key, TStringArray rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, TStringArray> param = new Param3<string, string, TStringArray>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
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

        if (modName != GetModName()) return;
        if (!key) return;

        Handle(sender, key, ctx);
    }

    // MARK: - Internal

    void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {}
}