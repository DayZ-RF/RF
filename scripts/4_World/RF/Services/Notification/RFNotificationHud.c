class RFNotificationHud: Managed {

    // MARK: - Private properties ----------------------------------

    autoptr array <autoptr RFNotificationHudItem> items = {};

    // MARK: - Init ----------------------------------

    void RFNotificationHud() {
        GetDayZGame().Event_OnRPC.Insert(ClientRPCHandler);
    }

    void ~RFNotificationHud() {
        GetDayZGame().Event_OnRPC.Remove(ClientRPCHandler);
    }

    // MARK: - Public methods ----------------------------------

    // Удалить элемент с экрана
    // - item: Экземпляр объекта на удаление

    void RemoveItem(RFNotificationHudItem item) {
        int idx = items.Find(item);
        if (idx + 1)
            items.Remove(idx);
    }

    // MARK: - Private methods ----------------------------------

    // Добавить элемент с сообщением на экран
    // - data: Набор данных с информацией для отображения

    void addItem(RFNotificationEntity data) {
        downAllItems();
        items.Insert(new RFNotificationHudItem(this, data));
    }

    // Опустить элемент ниже

    void downAllItems() {
        for (int i = 0; i < this.items.Count(); i++)
            this.items.Get(i).DownItSelf();
    }

    // MARK: - RPC methods ----------------------------------

    private void ClientRPCHandler(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

        if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
            delete this;
            return;
        }

        switch (rpc_type) {
            case RFEnum.RF_SEND_NOTIFICATION_FROM_SERVER: {
                Param1<RFNotificationEntity> args;
                if (!ctx.Read(args)) return;

                RFNotificationEntity data = args.param1;
                addItem(data);

                break;
            }
        }
    }
}
