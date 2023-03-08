class RF_RPCInstanceServer: RF_RPCInstance {
	
	  // MARK: - Override
	
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (GetGame().IsClient()) return;
        super.OnRPC(sender, target, rpc_type, ctx);
    }
}