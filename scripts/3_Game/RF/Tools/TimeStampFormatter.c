class RF_TimeStampFormatter: Managed {
	
	// MARK: - Private Properties
	
	private autoptr array<string> weekdays = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
	
	private autoptr array<string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
	// MARK: - Internal

	string Formatted(RF_TimeStamp timeStamp) {
		string weekday = weekdays[timeStamp.GetWeekday() - 1];
		string month = months[timeStamp.GetMonth() - 1];
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