class RF_RFMapService: Managed {

    #ifdef SERVER
    #ifdef RF_MAP
    private autoptr RF_MAP_SE_MarkerViewModelsMap markersMap = new RF_MAP_SE_MarkerViewModelsMap();
    #endif
    #endif

    void CreateMapMarker(string uuid, string title, vector pos, string iconPath = "", RF_Color color = NULL, bool isVisible = true, float radius = 0,  bool hideIntersects = false) {
        #ifdef SERVER
        #ifdef RF_MAP
        auto markerEntity = new RF_MAP_MarkerEntity();
        markerEntity.uuid = uuid;
        markerEntity.position = pos;
        markerEntity.title = title;
        markerEntity.textColor = color;
        markerEntity.iconPath = iconPath;

        if (!hideIntersects) {
            markerEntity.circle = new RF_MAP_CircleEntity();
            markerEntity.circle.radius = radius;
            markerEntity.circle.strike = new RF_MAP_StrikeEntity();
            markerEntity.circle.strike.width = 3.0;
            markerEntity.circle.strike.color = color;
            markerEntity.circle.border = new RF_MAP_BorderEntity();
            markerEntity.circle.border.width = 3.0;
            markerEntity.circle.border.color = color;
        }
        auto newMarker = RF_MAP_SE_Global.mapManager.AddEventMarker(markerEntity);

        if (!newMarker) {
            RF_Log().Error("[RF_RFMapService] - Cannot create event marker");
            return;
        }

        markersMap.Insert(uuid, newMarker);
        RF_Log().Info(string.Format("[RF_RFMapService] - CreateRFMapMarker: %1", uuid));

        #endif
        #endif
    }

    void RemoveMapMarker(string uuid) {
        #ifdef SERVER
        #ifdef RF_MAP
        if (!GetGame().IsServer()) return;

        RF_Log().Info(string.Format("RF_RFMapService - RemoveRFMapMarker: %1", uuid));

        auto marker = markersMap.Get(uuid);
        RF_MAP_SE_Global.mapManager.RemoveEventMarker(marker);

        #endif
        #endif
    }
}
