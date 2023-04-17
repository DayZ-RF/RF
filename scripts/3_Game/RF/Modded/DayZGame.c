modded class DayZGame {
	
	// MARK: - Private Properties

	private autoptr map<string, autoptr TManagedSet> subscribersMap = new map<string, autoptr TManagedSet>();
	
	private autoptr array<string> dayZGameEvents = {
		"OnUpdate",
		"OnKeyPress",
		"OnKeyRelease",
		"OnRPC",
	};
	
	// MARK: - Override Init
	
	void DayZGame() {
		foreach (string dayZGameEvent : dayZGameEvents)
			subscribersMap[dayZGameEvent] = new TManagedSet();
	}
	
	// MARK: - Override Events

	override void OnUpdate(bool doSim, float timeslice) {
        super.OnUpdate(doSim, timeslice);
		
		call("OnUpdate", new Param2<bool, float>(doSim, timeslice));
	}

    override void OnKeyPress(int key) {
        super.OnKeyPress(key);
		
		call("OnKeyPress", new Param1<int>(key));
    }

    override void OnKeyRelease(int key) {
        super.OnKeyRelease(key);
		call("OnKeyRelease", new Param1<int>(key));
    }

	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, target, rpc_type, ctx);
		
		call("OnRPC", new Param4<PlayerIdentity, Object, int, ParamsReadContext>(sender, target, rpc_type, ctx));
	}
	
	// MARK: - Internal

	bool Subscribe(Managed object, string dayZGameEvent) {
		if (!subscribersMap[dayZGameEvent]) return false;
		
		subscribersMap[dayZGameEvent].Insert(object);
		
		return true;
	}

	bool Unsubscribe(Managed object, string dayZGameEvent) {
		if (!subscribersMap[dayZGameEvent]) return false;

		int eventIndex = dayZGameEvents.Find(dayZGameEvent);
		if (eventIndex == -1) return false;
		
		int objectIndex = subscribersMap[dayZGameEvent].Find(object);
		if (objectIndex == -1) return false;
		
		subscribersMap[dayZGameEvent].Remove(objectIndex);
		
		return true;
	}
	
	// MARK: - Private

	private void call(string dayZGameEvent, Param params) {
		autoptr TManagedSet subscribers = subscribersMap[dayZGameEvent];
		if (!subscribers) return;

        for (int i = subscribers.Count() - 1; i >= 0; i--) {
            auto subscriber = subscribers[i];
            if (!subscriber) {
                subscribers.Remove(i); 
                continue;
            }
			GetGame().GameScript.CallFunctionParams(subscriber, dayZGameEvent, NULL, params);
		}
	}
}