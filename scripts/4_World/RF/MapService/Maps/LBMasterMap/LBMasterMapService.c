// Мост к LBmaster Groups. Целиком серверный: LBmaster сам синхронизирует маркеры с клиентами.
class RF_LBMasterMapService: Managed {

    #ifdef RF_LBMASTER
    #ifdef SERVER
    private autoptr TStringIntMap markers = new TStringIntMap();
    #endif
    #endif

    // MARK: - Init

    void RF_LBMasterMapService() {
        #ifdef RF_LBMASTER
        #ifdef SERVER
        RF_Log().Info("[RF_LBMasterMapService] - Enabled");
        #endif
        #else
        RF_Log().Info("[RF_LBMasterMapService] - Disabled: LBmaster is not loaded");
        #endif
    }

    // MARK: - Internal

    bool IsAvailable() {
        #ifdef RF_LBMASTER
        #ifdef SERVER
        return true;
        #endif
        #endif

        return false;
    }

    void CreateMarker(string uuid, string title, vector position, string iconPath, int color, bool circleIsEnabled, int circleRadius, int circleColor, bool circleIsStriked) {
        #ifdef RF_LBMASTER
        #ifdef SERVER
        if (!uuid) return;

        int alpha, red, green, blue;
        LBConverter.ARGBToComponents(circleColor, alpha, red, green, blue);

        LBServerMarker lbMarker;

        if (circleIsEnabled) {
            lbMarker = LBStaticMarkerManager.Get.AddTempServerMarker(title, position, iconPath, color, true, false, true, true);
            if (!lbMarker) return;

            markers.Set(uuid, lbMarker.uid);
            lbMarker.SetRadius(circleRadius, alpha, red, green, blue, circleIsStriked);

            RF_Log().Info(string.Format("[RF_LBMasterMapService] - CreateMarker: %1", uuid));
            return;
        }

        lbMarker = LBStaticMarkerManager.Get.AddTempServerMarker(title, position, iconPath, color, true, true, true, true);
        if (!lbMarker) return;

        markers.Set(uuid, lbMarker.uid);

        RF_Log().Info(string.Format("[RF_LBMasterMapService] - CreateMarker: %1", uuid));
        #endif
        #endif
    }

    void RemoveMarker(string uuid) {
        #ifdef RF_LBMASTER
        #ifdef SERVER
        if (!uuid) return;
        // Без этой проверки Get вернул бы 0 и снёс чужой маркер LBmaster.
        if (!markers.Contains(uuid)) return;

        LBStaticMarkerManager.Get.RemoveServerMarker(markers.Get(uuid));
        markers.Remove(uuid);

        RF_Log().Info(string.Format("[RF_LBMasterMapService] - RemoveMarker: %1", uuid));
        #endif
        #endif
    }
}
