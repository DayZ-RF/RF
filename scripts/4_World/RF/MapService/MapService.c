class RF_MapService: Managed {

    autoptr RF_BasicMapService basicMapService = new RF_BasicMapService();
    autoptr RF_RFMapService rfMapService = new RF_RFMapService();

    autoptr RF_VPPMapService vppMapService = new RF_VPPMapService();

    autoptr RF_VPPMapClientService vppMapClientService = new RF_VPPMapClientService();

    autoptr RF_LBMasterMapService lbMasterMapService = new RF_LBMasterMapService();
}
