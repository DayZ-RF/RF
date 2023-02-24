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
	
	RF_TimeStamp Add(int Day, int Hour, int Minute, int Second) {
		auto timeStamp = new RF_TimeStamp();
		bool isConfigured = timeStamp.configure(time + Day * secondsInDay + Hour * secondsInHour + Minute * secondsInMinute + Second * secondsInSecond);
		if (!isConfigured) return null;
		return timeStamp;
	}
	
	bool SetGMT(int GMT) {
		this.gmt[0] = (GMT / 1000) % 10;
		this.gmt[1] = (GMT / 100) % 10;
		this.gmt[2] = (GMT / 10) % 10;
		this.gmt[3] = (GMT / 1) % 10;
		int gmtSeconds = (GMT / 100) * secondsInHour + (GMT % 100) * secondsInMinute;
		return configure(time + gmtSeconds);
	}

	int GetWeekday() { 
		int days = RF_Time.DaysFromHigh(year, month, day);
		return RF_Time.WeekdayFromDays(days);
	}
	
	// MARK: - Private

	private bool configure(int Time) {
		if (Time < 0) return false;

		this.time = Time;

		int mat[3];
		RF_Time.HighFromDays(Time / secondsInDay, mat);

		year = mat[0];
		month = mat[1];
		day = mat[2];

		RF_Time.LowFromSeconds(Time % secondsInDay, mat);

		hour = mat[0];
		minute = mat[1];
		second = mat[2];

		return true;
	}

	private bool configure(int Year, int Month, int Day, int Hour, int Minute, int Second) {
		if (Year < 1970 || Month < 1 || Day < 1 || Hour < 0 || Minute < 0 || Second < 0) return false;

		this.year = Year;
		this.month = Month;
		this.day = Day;
		this.hour = Hour;
		this.minute = Minute;
		this.second = Second;

		this.time = RF_Time.DaysFromHigh(Year, Month, Day) * secondsInDay + RF_Time.SecondsFromLow(Hour, Minute, Second);

		return true;
	}
}