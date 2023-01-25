class RF_Time: Managed {

	// MARK: - Helpers

	static int DaysFromHigh(int year, int month, int day) {
		int y = year;
		int m = month;
		int d = day;
	    y -= m <= 2;
		int era;
		if (y >= 0) {
			era = y / 400;
		} else {
			era = (y - 399) / 400;
		}
		int mmm;
		if (m > 2) {
			mmm = m - 3;
		} else {
			mmm = m + 9;
		}
	    int yoe = (y - era * 400);
	    int doy = (153 * mmm + 2) / 5 + d - 1;
	    int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	    return era * 146097 + doe - 719468;
	}
	
	static void HighFromDays(int days, out int mat[3]) {
		int z = days;
	    z += 719468;
	    int era;
		if (z >= 0) {
			era = z / 146097;
		} else {
			era = (z - 146096) / 146097;
		}
	    int doe = z - era * 146097;
	    int yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	    int y = yoe + era * 400;
	    int doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	    int mp = (5 * doy + 2) / 153;
	    int d = doy - (153 * mp + 2) / 5 + 1;  
		int m;
		if (mp < 10) {
			m = mp + 3;
		} else {
			m = mp - 9;
		}
		mat[0] = y + (m <= 2);
		mat[1] = m;
		mat[2] = d;
	}
	
	static void LowFromSeconds(int time, out int mat[3]) {
		mat[0] = (time / 3600) % 24;
		mat[1] = (time / 60) % 60;
		mat[2] = (time / 1) % 60;
	}

	static int SecondsFromLow(int hour, int minute, int time) {
		return time + minute * 60 + hour * 3600;
	}
	
	static bool IsLeap(int y) {
	    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
	}
	
	static int LastDayOfMonthCommonYear(int m) {
	    int a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	    return a[m - 1];
	}
	
	static int LastDayOfMonthLeapYear(int m) {
	    int a[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    	return a[m - 1];
	}
	
	static int LastDayOfMonth(int y, int m) {
		if (m != 2 || !IsLeap(y)) {
			return LastDayOfMonthCommonYear(m);
		} else {
			return LastDayOfMonthLeapYear(m);
		}
	}
	
	static int WeekdayFromDays(int z) {
	    if (z >= -4) {
			return (z + 4) % 7;
		} else {
			return (z + 5) % 7 + 6;
		}
	}
}