class RFNotificationEntity: Managed {

    // Title message
    string title;

    // Main message
    string message;

    // Time before notification will be destroyed
    int lifetime = 5;

    // View configuration
    autoptr RFNotificationViewConfiguration viewConfiguration = new RFNotificationViewConfiguration();

    // List of players who should recieve notification
    autoptr array<Man> players;
}

class RFNotificationViewConfiguration: Managed {

    // Title color
    int titleColor = ARGB(255, 255, 255, 255);

    // Text Color
    int textColor = ARGB(255, 255, 255, 255);

    // Borders color
    int borderColor = ARGB(255, 8, 123, 37);

    // Background color
    int backgroundColor = ARGB(255, 48, 48, 48);

    // Margin between notifications
    int margin = 20;

    // Icon of the notifications
    string iconPath = "RF/GUI/icons/alarm.edds";
}
