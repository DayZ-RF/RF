modded class DayZGame {
	
	// MARK: - Private Properties

	private autoptr map<string, autoptr TManagedSet> subscribersMap = new map<string, autoptr TManagedSet>();
	
	private autoptr array<string> dayZGameEvents = {
		"OnUpdate",
		"OnKeyPress",
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