// Клиентская половина моста к VanillaPlusPlusMap.
// Принимает снимок маркеров с сервера и держит в актуальном виде только свои маркеры,
// не трогая те, что VanillaPlusPlusMap завёл сам.
class RF_VPPMapClientService: Managed {

    #ifdef RF_VanillaPlusPlusMap_CL
    #ifndef SERVER
    private autoptr map<string, ref MarkerInfo> ownedMarkers = new map<string, ref MarkerInfo>();
    #endif
    #endif

    // MARK: - Internal

    void HandleMarkersDidUpdate(RF_VPPMapData data) {
        #ifdef RF_VanillaPlusPlusMap_CL
        #ifndef SERVER
        if (!data) return;

        auto serverMarkers = GetDayZGame().GetServerMarkers();
        if (!serverMarkers) return;

        removeVanishedMarkers(data, serverMarkers);

        foreach (string uuid, RF_VPPMapMarkerData markerData : data.markersMap) {
            auto marker = ownedMarkers.Get(uuid);

            if (!marker || serverMarkers.Find(marker) == -1) {
                marker = new MarkerInfo(markerData.title, markerData.iconPath, markerData.color, markerData.position, markerData.isActive.isEnabled, markerData.is3DActive.isEnabled);
                serverMarkers.Insert(marker);
                ownedMarkers.Set(uuid, marker);
                continue;
            }

            marker.SetName(markerData.title);
            marker.SetIconPath(markerData.iconPath);
            marker.SetColor(markerData.color);
            marker.SetPosition(markerData.position);

            if (markerData.isActive.isForced) marker.SetActive(markerData.isActive.isEnabled);
            if (markerData.is3DActive.isForced) marker.Set3DActive(markerData.is3DActive.isEnabled);
        }
        #endif
        #endif
    }

    // MARK: - Private

    #ifdef RF_VanillaPlusPlusMap_CL
    #ifndef SERVER

    private void removeVanishedMarkers(RF_VPPMapData data, array<ref MarkerInfo> serverMarkers) {
        auto vanishedUUIDs = new TStringArray();

        foreach (string uuid, MarkerInfo marker : ownedMarkers) {
            if (data.markersMap.Contains(uuid)) continue;

            int index = serverMarkers.Find(marker);
            if (index != -1) serverMarkers.RemoveOrdered(index);

            vanishedUUIDs.Insert(uuid);
        }

        foreach (string vanishedUUID : vanishedUUIDs) {
            ownedMarkers.Remove(vanishedUUID);
        }
    }
    #endif
    #endif
}
