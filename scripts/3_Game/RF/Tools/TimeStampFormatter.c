class RF_TimeStampFormatter: Managed {
	
	// MARK: - Private Properties
	
	private autoptr array<string> weekdays = {"#RF_Mon", "#RF_Tue", "#RF_Wed", "#RF_Thu", "#RF_Fri", "#RF_Sat", "#RF_Sun", };
	
	private autoptr array<string> months = {"#RF_Jan", "#RF_Feb", "#RF_Mar", "#RF_Apr", "#RF_May", "#RF_Jun", "#RF_Jul", "#RF_Aug", "#RF_Sep", "#RF_Oct", "#RF_Nov", "#RF_Dec", };
	
	// MARK: - Internal

	string Formatted(RF_TimeStamp timeStamp) {
		string weekday = Widget.TranslateString(weekdays[timeStamp.GetWeekday() - 1]);
		string month = Widget.TranslateString(months[timeStamp.GetMonth() - 1]);
		string day = ToString(timeStamp.GetDay());
		string year = ToString(timeStamp.GetYear());
		string hour = ToString(timeStamp.GetHour());
		string minute = ToString(timeStamp.GetMinute());
		string second = ToString(timeStamp.GetSecond());
		array<int> gmt = timeStamp.GetGMT();
		string gmtString = gmt[0].ToString() + gmt[1].ToString() + gmt[2].ToString() + gmt[3].ToString();
		string sign = "+";
		if (gmt[0] < 0) {
			sign = "-";
		}
		return string.Format("%1 %2 %3 %4 %5:%6:%7 GMT%8%9", weekday, month, day, year, hour, minute, second, sign, gmtString);
	}

	static string ToString(int value) {
		if (value < 10) return string.Format("0%1", value);
		return string.Format("%1", value);
	}
}