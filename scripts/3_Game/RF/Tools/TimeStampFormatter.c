class RF_TimeStampFormatter: Managed {

    // MARK: - Private Properties

    protected autoptr array<string> weekdays = {"#RF_Mon", "#RF_Tue", "#RF_Wed", "#RF_Thu", "#RF_Fri", "#RF_Sat", "#RF_Sun", };

    protected autoptr array<string> months = {"#RF_Jan", "#RF_Feb", "#RF_Mar", "#RF_Apr", "#RF_May", "#RF_Jun", "#RF_Jul", "#RF_Aug", "#RF_Sep", "#RF_Oct", "#RF_Nov", "#RF_Dec", };

    // MARK: - Internal

    string Formatted(RF_TimeStamp _timeStamp) {
        auto time = _timeStamp.GetTime() + GetGmtInSeconds();
        auto timeStamp = RF_TimeStamp.Date(time);
        string weekday = Widget.TranslateString(weekdays[timeStamp.GetWeekday() - 1]);
        string month = Widget.TranslateString(months[timeStamp.GetMonth() - 1]);
        string day = ToString(timeStamp.GetDay());
        string year = ToString(timeStamp.GetYear());
        string hour = ToString(timeStamp.GetHour());
        string minute = ToString(timeStamp.GetMinute());
        string second = ToString(timeStamp.GetSecond());
        return string.Format("%1 %2 %3 %4 %5:%6:%7", weekday, month, day, year, hour, minute, second);
    }

    protected string ToString(int value) {
        if (value < 10) return string.Format("0%1", value);
        return string.Format("%1", value);
    }

    protected int GetGmtInSeconds() {
        auto gmt = RF_ConfigurationsProvider.shared.GetSettingsConfiguration().gmt;
        return (gmt / 100) * 3600 + (gmt % 100) * 60;
    }
}
