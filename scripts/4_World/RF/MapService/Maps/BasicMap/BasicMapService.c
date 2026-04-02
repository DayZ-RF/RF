class RF_BasicMapService: Managed {

    #ifdef BASICMAP
    private autoptr map<string, autoptr BasicMapMarker> basicMapMarkers = new map<string, autoptr BasicMapMarker>();
    #endif

    void CreateBasicMapSessionMarker(string uuid, string name, vector pos, string icon = "", array<int> colour = NULL, int alpha = 235, bool onHUD = false, float radius = 0, bool showCenterMarker = true, bool hideIntersects = false) {
        #ifdef BASICMAP
        if (!GetGame().IsServer()) return;

        RF_Log().Info(string.Format("RF_BasicMapService - CreateBasicMapSessionMarker: %1", uuid));

        auto basicMap = BasicMap();
        auto marker = basicMap.RF_CreateSessionMarker(name, pos, icon, colour, alpha, onHUD, radius, showCenterMarker, hideIntersects);
        if (basicMap && uuid) {
            basicMapMarkers[uuid] = marker;
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).RemoveByName(this, "updateMarkers");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "updateMarkers", 1000);
        }
        #endif
    }

    void UpdateBasicMapSessionMarkerPosition(string uuid, vector position) {
        #ifdef BASICMAP
        if (!GetGame().IsServer()) return;

        RF_Log().Info(string.Format("RF_BasicMapService - UpdateBasicMapSessionMarkerPosition: %1", uuid));

        auto basicMap = BasicMap();
        auto marker = basicMapMarkers[uuid];
        if (basicMap && uuid) {
            basicMap.RF_UpdateSessionMarkerPosition(marker, position);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).RemoveByName(this, "updateMarkers");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "updateMarkers", 1000);
        }
        #endif
    }

    void RemoveBasicMapSessionMarker(string uuid) {
        #ifdef BASICMAP
        if (!GetGame().IsServer()) return;

        RF_Log().Info(string.Format("RF_BasicMapService - RemoveBasicMapSessionMarker: %1", uuid));

        auto basicMap = BasicMap();
        auto marker = basicMapMarkers[uuid];
        if (basicMap && uuid) {
            basicMapMarkers[uuid] = null;
            basicMap.RF_RemoveSessionMarker(marker);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).RemoveByName(this, "updateMarkers");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "updateMarkers", 1000);
        }
        #endif
    }

    #ifdef BASICMAP

    private void updateMarkers() {
        auto basicMap = BasicMap();
        if (basicMap) basicMap.RF_UpdateMarkers();
    }
    #endif
}
