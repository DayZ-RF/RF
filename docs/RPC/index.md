# RPC Service

RPC wrapper under vanila DayZ RPCs.



## Simple example (Using primitives or sending only signal)

### Available primitives

* int
* string
* vector
* string
* TStringArray

### Template RPC Instance

Create RPC instances in your mod according to the example. You can create as much RPC cases as you need in your mod. To handle one RPC you need to create a new case in "switch" construction and create private method, which will handle the recieved information.

* RF_TEMPLATE_Constant.RPC_TYPE - random int value. Should be unique. (ex. 123456)
* RF_TEMPLATE_Constant.MOD_NAME - special random string. We usualy use mod name. (ex. "Template")

#### Client

```csharp

class RF_TEMPLATE_CL_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_TEMPLATE_Constant.RPC_TYPE; }

    override string GetModName() { return RF_TEMPLATE_Constant.MOD_NAME; }
	
	// MARK: - Override

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
        switch (key) {
            case "didReceiveTemplateActionEmpty": {
                handleDidReceiveTemplateActionEmpty(sender, ctx);
                break;
            }
            case "didReceiveTemplateActionIntValue": {
                handleDidReceiveTemplateActionIntValue(sender, ctx);
                break;
            }
        }
    }

    // MARK: - Handlers

    private void handleDidReceiveTemplateActionEmpty(PlayerIdentity sender, ParamsReadContext ctx) {
        // Work here...
    }

    private void handleDidReceiveTemplateActionIntValue(PlayerIdentity sender, ParamsReadContext ctx) {
        int intValue;
        ctx.Read(intValue);
        if (!intValue) return;
        // Work with int value..
    }
}

```

#### Server

```csharp
class RF_TEMPLATE_SE_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_TEMPLATE_Constant.RPC_TYPE; }

    override string GetModName() { return RF_TEMPLATE_Constant.MOD_NAME; }

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
        switch (key) {
            case "fetchTempleteData": {
                handleFetchTempleteData(sender, ctx);
                break;
            }
        }
    }

    // MARK: - Handlers

    private void handleFetchTempleteData(PlayerIdentity sender, ParamsReadContext ctx) {        
        // Work here...
    }
}
```

The best practise will be to use singleton and store such variables in one place. So, the example could be like:

```csharp
class RF_TEMPLATE_SE_Global: Managed {

	// MARK: - Static Properties

	static ref RF_TEMPLATE_SE_RPCInstance rpc = new RF_TEMPLATE_SE_RPCInstance();
}
```

### Send RPCs

##### Send object data to concrete player

```csharp
private void handleDataAndSendFromServerToClient(PlayerBase player) {
	auto playerIdentity = player.GetIdentity();
	int intValue = 123456;
	RF_TEMPLATE_SE_Global.rpc.Send("didReceiveTemplateAction", intValue, playerIdentity);
}
```

##### Send int data broadcasting (to all players)

```csharp
private void handleDataAndSendFromServerToClient() {
	int intValue = 123456;
	RF_TEMPLATE_SE_Global.rpc.Send("didReceiveTemplateAction", intValue);
}
```

##### Send signal from client to server

```csharp
private void sendSignalFromClientToServer() {
	RF_TEMPLATE_CL_Global.rpc.Send("fetchTempleteData");
}
```

</br><hr></br>




## Advanced example (Sending custom object)

### Template RPC Instance

Create RPC instances in your mod according to the example.

#### Client

```csharp

class RF_TEMPLATE_CL_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_TEMPLATE_Constant.RPC_TYPE; }

    override string GetModName() { return RF_TEMPLATE_Constant.MOD_NAME; }
	
	// MARK: - Override

    override void Handle(PlayerIdentity sender, string key, ParamsReadContext ctx) {
        super.Handle(sender, key, ctx);
        switch (key) {
            case "didReceiveTemplateAction": {
                handleDidReceiveTemplateAction(sender, ctx);
                break;
            }
        }
    }

    // MARK: - Handlers

    private void handleDidReceiveTemplateAction(PlayerIdentity sender, ParamsReadContext ctx) {
        autoptr RF_TEMPLATE_Object object;
        ctx.Read(object);
        if (!object) return;
        // Work with object..
    }
}

```

#### Server

```csharp
class RF_TEMPLATE_SE_RPCInstance: RF_RPCInstance {

    // MARK: - Override Properties

    override int GetRPCType() { return RF_TEMPLATE_Constant.RPC_TYPE; }

    override string GetModName() { return RF_TEMPLATE_Constant.MOD_NAME; }
	
    // MARK: - Handlers

    void Send(string key, RF_TEMPLATE_Object rpcObject, PlayerIdentity playerIdentity = null) {
        Param3<string, string, RF_TEMPLATE_Object> param = new Param3<string, string, RF_TEMPLATE_Object>(GetModName(), key, rpcObject);
        GetGame().RPCSingleParam(null, GetRPCType(), param, true, playerIdentity);
    }
}
```


### Send RPCs

##### Send object data to concrete player

```csharp
private void handleDataAndSendFromServerToClient(PlayerBase player) {
	auto playerIdentity = player.GetIdentity();
	RF_TEMPLATE_Object customObject = new RF_TEMPLATE_Object();
	RF_TEMPLATE_SE_Global.rpc.Send("didReceiveTemplateAction", customObject, playerIdentity);
}
```

##### Send object data broadcasting (to all players)

```csharp
private void handleDataAndSendFromServerToClient() {
	RF_TEMPLATE_Object customObject = new RF_TEMPLATE_Object();
	RF_TEMPLATE_SE_Global.rpc.Send("didReceiveTemplateAction", customObject);
}
```
