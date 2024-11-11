class RFNotificationHudItem: Managed {

	// MARK: - Private properties  ----------------------------------

	private autoptr RFNotificationHud parent;
	private Widget rootWidget;
	private TextWidget title;
	private TextWidget mainText;
	private GridSpacerWidget wraper;
	private ImageWidget notificationIcon;

	private float margin = 20;
	private const string NOTIFICATION_SOUNDSET = "RF_Notification_SoundSet";

	// MARK: - Init ----------------------------------

	void RFNotificationHudItem(RFNotificationHud Parent, RFNotificationEntity data) {
		this.parent = Parent;

		rootWidget = GetGame().GetWorkspace().CreateWidgets("RF/GUI/Layouts/RFNotificationHud.layout");

		title = TextWidget.Cast(rootWidget.FindAnyWidget("NotificationTitle"));
		mainText = TextWidget.Cast(rootWidget.FindAnyWidget("NotificationText"));
		wraper = GridSpacerWidget.Cast(rootWidget.FindAnyWidget("Wraper"));
		notificationIcon = ImageWidget.Cast(rootWidget.FindAnyWidget("NotificationIcon"));

		configureWith(data);

		EffectSound sound = SEffectManager.PlaySound(NOTIFICATION_SOUNDSET, GetGame().GetPlayer().GetPosition());
        sound.SetSoundAutodestroy(true);
	}

	void ~RFNotificationHudItem() {
		this.destroy();
	}

	void configureWith(RFNotificationEntity data) {
		title.SetText(data.title);
		mainText.SetText(data.message);

		setBordersColor(data.viewConfiguration.borderColor);
		setTitleColor(data.viewConfiguration.titleColor);
		setTextColor(data.viewConfiguration.textColor);
		setBackgroundColor(data.viewConfiguration.backgroundColor);
		setImage(data.viewConfiguration.iconPath);
		this.margin = data.viewConfiguration.margin;

		refresh();

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.destroy, data.lifetime * 1000, false);
	}

	// MARK: - Public methods ----------------------------------

	void DownItSelf() { 
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;
		rootWidget.GetPos(x, y);
		wraper.GetScreenSize(width, height);
		rootWidget.SetPos(x, y + height + margin);
	} 

	// MARK: - Private Methods --------------------------------------------------------------------------

	void refresh() {
		wraper.Update();
		rootWidget.Update();
		mainText.Update();
	}

	void destroy() {
		if (rootWidget)
			rootWidget.Unlink();
		parent.RemoveItem(this);
	}

	void setBackgroundColor(int color) {
		wraper.SetColor(color);
	} 

	void setTextColor(int color) {
		mainText.SetColor(color);
	}

	void setTitleColor(int color) {
		title.SetColor(color);
	}

	void setBordersColor(int color) {
		Widget borderTop = rootWidget.FindAnyWidget("borderTop");
		Widget borderLeft = rootWidget.FindAnyWidget("borderLeft");
		Widget borderBottom = rootWidget.FindAnyWidget("borderBottom");
		Widget borderRight = rootWidget.FindAnyWidget("borderRight");
		borderTop.SetColor(color);
		borderLeft.SetColor(color);
		borderBottom.SetColor(color);
		borderRight.SetColor(color);
	}

	void setImage(string path) {
		notificationIcon.LoadImageFile(0, path);
	}
}