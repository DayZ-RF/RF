// Серверная половина моста к VanillaPlusPlusMap.
// Копит маркеры событий и раз в mapUpdateInterval рассылает клиентам полный снимок.
class RF_VPPMapService: Managed {

    #ifdef RF_VanillaPlusPlusMap_CL
    #ifdef SERVER
    private autoptr map<string, autoptr RF_VPPMapMarkerData> markersMap = new map<string, autoptr RF_VPPMapMarkerData>();

    private autoptr Timer timer;

    private int lastSentCount;
    #endif
    #endif

    // MARK: - Init

    void RF_VPPMapService() {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifdef SERVER
        float interval = RF_ConfigurationsProvider.shared.GetMapUpdateInterval();
        timer = new Timer();
        timer.Run(interval, this, "tick", NULL, true);
        RF_Log().Info(string.Format("[RF_VPPMapService] - Enabled, sync interval: %1", interval));
        #endif
        #else
        RF_Log().Info("[RF_VPPMapService] - Disabled: RF_VanillaPlusPlusMap_CL is not loaded");
        #endif
    }

    // MARK: - Internal

    bool IsAvailable() {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifdef SERVER
        return true;
        #endif
        #endif

        return false;
    }

    void CreateMarker(string uuid, string title, vector position, string iconPath, vector color, bool isMarkerEnabled, bool isMarkerForced, bool is3DMarkerEnabled, bool is3DMarkerForced) {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifdef SERVER
        if (!uuid) return;

        position[1] = 0;

        auto markerData = new RF_VPPMapMarkerData();
        markerData.uuid = uuid;
        markerData.title = title;
        markerData.iconPath = iconPath;
        markerData.color = color;
        markerData.position = position;
        markerData.isActive.isEnabled = isMarkerEnabled;
        markerData.isActive.isForced = isMarkerForced;
        markerData.is3DActive.isEnabled = is3DMarkerEnabled;
        markerData.is3DActive.isForced = is3DMarkerForced;

        markersMap.Set(uuid, markerData);

        RF_Log().Info(string.Format("[RF_VPPMapService] - CreateMarker: %1", uuid));
        #endif
        #endif
    }

    void UpdateMarkerPosition(string uuid, vector position) {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifdef SERVER
        if (!uuid) return;
        if (!markersMap.Contains(uuid)) return;

        position[1] = 0;
        markersMap.Get(uuid).position = position;

        RF_Log().Info(string.Format("[RF_VPPMapService] - UpdateMarkerPosition: %1", uuid));
        #endif
        #endif
    }

    void RemoveMarker(string uuid) {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifdef SERVER
        if (!uuid) return;
        if (!markersMap.Contains(uuid)) return;

        markersMap.Remove(uuid);

        RF_Log().Info(string.Format("[RF_VPPMapService] - RemoveMarker: %1", uuid));
        #endif
        #endif
    }

    // MARK: - Private

    #ifdef RF_VanillaPlusPlusMap_CL
    #ifdef SERVER

    private void tick() {
        int count = markersMap.Count();
        // Пустой снимок шлём один раз - чтобы клиент убрал последний исчезнувший маркер.
        if (count == 0 && lastSentCount == 0) return;
        if (!RF_Global.serverRPC) return;

        auto rpcData = new RF_VPPMapData();
        rpcData.markersMap = markersMap;
        RF_Global.serverRPC.Send("vppMapMarkersDidUpdate", rpcData);

        lastSentCount = count;
    }
    #endif
    #endif
}
