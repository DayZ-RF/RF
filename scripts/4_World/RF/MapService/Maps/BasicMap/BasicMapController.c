#ifdef BASICMAP
modded class BasicMapController {

    BasicMapMarker RF_CreateSessionMarker(string name, vector pos, string icon = "", array<int> colour = NULL, int alpha = 235, bool onHUD = false, float radius = 0, bool showCenterMarker = true, bool hideIntersects = false) {
        BasicMapMarker marker;
        if (radius == 0) {
            marker = new BasicMapMarker(name, pos, icon, colour, alpha, onHUD);
        } else {
            auto circleMarker = new BasicMapCircleMarker(name, pos, icon, colour, alpha, onHUD);
            circleMarker.SetRadius(radius);
            circleMarker.SetHideIntersects(hideIntersects);
            circleMarker.SetShowCenterMarker(showCenterMarker);
            marker = circleMarker;
        }
        if (marker) AddMarker(SERVER_KEY, marker);
        RF_Log().Info(string.Format("BasicMapController - RF_CreateSessionMarker: %1, %2, %3, %4, %5, %6, %7", marker, name, pos, icon, colour, alpha, onHUD));

        return marker;
    }

    void RF_UpdateSessionMarkerPosition(BasicMapMarker marker, vector position) {
        if (marker) marker.SetPosition(position);
        RF_Log().Info(string.Format("BasicMapController - RF_UpdateSessionMarkerPosition: %1, %2", marker, position));
    }

    void RF_RemoveSessionMarker(BasicMapMarker marker) {
        if (marker) RemoveMarker(SERVER_KEY, marker);
        RF_Log().Info(string.Format("BasicMapController - RF_RemoveSessionMarker: %1", marker));
    }

    void RF_UpdateMarkers() {
        RF_Log().Info(string.Format("BasicMapController - RF_UpdateMarkers"));

        auto serverMarkers = new array<autoptr BasicMapMarker>;
        auto serverCircleMarkers = new array<autoptr BasicMapCircleMarker>;

        if (Markers.Get(SERVER_KEY)) {
            BasicMapCircleMarker cMarker;
            for (int i = 0; i < Markers.Get(SERVER_KEY).Count(); i++) {
                if (Markers.Get(SERVER_KEY).Get(i).IsInherited(BasicMapCircleMarker) && Class.CastTo(cMarker, Markers.Get(SERVER_KEY).Get(i)) && cMarker.GetRadius() > 0) {
                    serverCircleMarkers.Insert(cMarker);
                } else {
                    serverMarkers.Insert(Markers.Get(SERVER_KEY).Get(i));
                }
            }
        }

        GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param3<array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker>, ref BasicMapConfig>(serverMarkers, serverCircleMarkers, GetBasicMapConfig()), true, null);
    }
}
#endif
