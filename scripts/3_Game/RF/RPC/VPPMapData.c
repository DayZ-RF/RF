class RF_VPPMapMarkerFlag: Managed {

    bool isEnabled;

    bool isForced;
}

class RF_VPPMapMarkerData: Managed {

    string uuid;

    string title;

    string iconPath;

    vector color;

    vector position;

    autoptr RF_VPPMapMarkerFlag isActive = new RF_VPPMapMarkerFlag();

    autoptr RF_VPPMapMarkerFlag is3DActive = new RF_VPPMapMarkerFlag();
}

class RF_VPPMapData: Managed {

    autoptr map<string, autoptr RF_VPPMapMarkerData> markersMap = new map<string, autoptr RF_VPPMapMarkerData>();
}
