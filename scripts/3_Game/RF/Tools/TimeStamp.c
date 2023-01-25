class RF_TimeStamp: Managed {
	
	// MARK: - Internal Properties
	
	autoptr RF_TimeStampFormatter formatter = new RF_TimeStampFormatter();

	array<int> GetGMT() { return gmt; }
	
	int GetTime() { return time; }
	int GetYear() { return year; }
	int GetMonth() { return month; }
	int GetDay() { return day; }
	int GetHour() { return hour; }
	int GetMinute() { return minute; }
	int GetSecond() { return second; }
	
	// MARK: - Private Constants

    private int secondsInSecond = 1;
    private int secondsInMinute = 60;
    private int secondsInHour = 3600;
    private int secondsInDay = 86400;
    private int secondsInMonth = 2629743;
    private int secondsInYear = 31556926;

	// MARK: - Private Properties
	
	private autoptr array<int> gmt = {0, 0, 0, 0};

	private int time   = 0;

	private int year   = 1970;
	private int month  = 1;
	private int day    = 1;
	private int hour   = 0;
	private int minute = 0;
	private int second = 0;
	
	// MARK: - Static

	static RF_TimeStamp Date(int Year, int Month, int Day, int Hour, int Minute, int Second) {
		auto timeStamp = new RF_TimeStamp();
		bool isConfigured = timeStamp.configure(Year, Month, Day, Hour, Minute, Second);
		if (!isConfigured) return null;
		return timeStamp;
	}

	static RF_TimeStamp Date(int Seconds) {
		auto timeStamp = new RF_TimeStamp();
		bool isConfigured = timeStamp.configure(Seconds);
		if (!isConfigured) return null;
		return timeStamp;
	}

	static RF_TimeStamp Now() {
		auto timeStamp = new RF_TimeStamp();
		int Year, Month, Day, Hour, Minute, Second;
		GetHourMinuteSecondUTC(Hour, Minute, Second);
		GetYearMonthDayUTC(Year, Month, Day);
		bool isConfigured = timeStamp.configure(Year, Month, Day, Hour, Minute, Second);
		if (!isConfigured) return null;
		return timeStamp;
	}

	static RF_TimeStamp Zero() {
		return new RF_TimeStamp();
	}

	// MARK: - Internal
	
	string Formatted() { 
		return formatter.Formatted(this);
	}
	
	bool IsLowerThan(RF_TimeStamp a) {
		return time < a.GetTime();
	}
	
	bool IsBiggerThan(RF_TimeStamp a) {
		return time > a.GetTime();
	}
	
	bool IsEqual(RF_TimeStamp a) {
		return time == a.GetTime();
	}
	
	RF_TimeStamp Add(int day, int hour, int minute, int second) {
		auto timeStamp = new RF_TimeStamp();
		bool isConfigured = timeStamp.configure(time + day * secondsInDay + hour * secondsInHour + minute * secondsInMinute + second * secondsInSecond);
		if (!isConfigured) return null;
		return timeStamp;
	}
	
	bool SetGMT(int gmt) {
		this.gmt[0] = (gmt / 1000) % 10;
		this.gmt[1] = (gmt / 100) % 10;
		this.gmt[2] = (gmt / 10) % 10;
		this.gmt[3] = (gmt / 1) % 10;
		int gmtSeconds = (gmt / 100) * secondsInHour + (gmt % 100) * secondsInMinute;
		return configure(time + gmtSeconds);
	}

	int GetWeekday() { 
		int days = RF_Time.DaysFromHigh(year, month, day);
		return RF_Time.WeekdayFromDays(days);
	}
	
	// MARK: - Private

	private bool configure(int time) {
		if (time < 0) return false;

		this.time = time;

		int mat[3];
		RF_Time.HighFromDays(time / secondsInDay, mat);

		year = mat[0];
		month = mat[1];
		day = mat[2];

		RF_Time.LowFromSeconds(time % secondsInDay, mat);

		hour = mat[0];
		minute = mat[1];
		second = mat[2];

		return true;
	}

	private bool configure(int year, int month, int day, int hour, int minute, int second) {
		if (year < 1970 || month < 1 || day < 1 || hour < 0 || minute < 0 || second < 0) return false;

		this.year = year;
		this.month = month;
		this.day = day;
		this.hour = hour;
		this.minute = minute;
		this.second = second;

		this.time = RF_Time.DaysFromHigh(year, month, day) * secondsInDay + RF_Time.SecondsFromLow(hour, minute, second);

		return true;
	}
}