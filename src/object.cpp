#include "core.h"

namespace core {

	Object::Object() {
	}
	Object::~Object() {
	}
	String Object::getClassName() {
		return "Object";
	}
	String Object::getObjectName() {
		return "";
	}
	void Object::setObjectName(String value) {
	}
	bool Object::isParentClassExist(String className) {
		return false;
	}



	//---------------------------------------------------------------------------
	//----------  DateTime   ----------------------------------------------------
	//---------------------------------------------------------------------------
	DateTime::DateTime() {
		now();
	}
	DateTime::DateTime(int day, int month, int year) {
		setDate(day, month, year);
	}
	DateTime::DateTime(String s, DateTimeFormat dtf) {
		set(s, dtf);
	}
	void DateTime::now() {
		rawDateTime = time(NULL);
	}
	bool DateTime::isCorrect() {
		if (rawDateTime == -1) return false;
		return true;
	}
	void DateTime::setDate(int day, int month, int year) {
#ifdef OS_WINDOWS
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawDateTime);
		timeinfo.tm_year = year - 1900;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_mday = day;
		//	timeinfo->tm_sec = 5;
		rawDateTime = mktime(&timeinfo);
#endif

#ifdef OS_LINUX
		struct tm * timeinfo;
		timeinfo = localtime(&rawDateTime);
		timeinfo->tm_year = year - 1900;
		timeinfo->tm_mon = month - 1;
		timeinfo->tm_mday = day;
	//	timeinfo->tm_sec = 5;
		rawDateTime = mktime(timeinfo);
#endif
	}
	void DateTime::setTime(int hour, int minute, int second) {
#ifdef OS_WINDOWS
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawDateTime);
		timeinfo.tm_hour = hour;
		timeinfo.tm_min = minute;
		timeinfo.tm_sec = second;
		rawDateTime = mktime(&timeinfo);
#endif

#ifdef OS_LINUX
		struct tm * timeinfo;
		timeinfo = localtime(&rawDateTime);
		timeinfo->tm_hour = hour;
		timeinfo->tm_min = minute;
		timeinfo->tm_sec = second;
		rawDateTime = mktime(timeinfo);
#endif
	}
	void DateTime::set(String s, DateTimeFormat dtf) {
		String d, m, y;
		if (dtf == dtfRus) {
			d = s.subString(0, 2);
			m = s.subString(3, 2);
			y = s.subString(6, 4);
		}
		else if (dtf == dtfDatabase) {
			y = s.subString(0, 4);
			m = s.subString(5, 2);
			d = s.subString(8, 2);
		}
		setDate(d.toInt(), m.toInt(), y.toInt());
	}
	void DateTime::getDate(int &day, int &month, int &year) {
#ifdef OS_WINDOWS
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawDateTime);
		day = timeinfo.tm_mday;
		month = timeinfo.tm_mon + 1;
		year = timeinfo.tm_year + 1900;
#endif

#ifdef OS_LINUX
		struct tm * timeinfo;
		timeinfo = localtime(&rawDateTime);
		day = timeinfo->tm_mday;
		month = timeinfo->tm_mon + 1;
		year = timeinfo->tm_year + 1900;
#endif
	}
	void DateTime::getTime(int &hour, int &min, int &sec) {
#ifdef OS_WINDOWS
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawDateTime);
		hour = timeinfo.tm_hour;
		min = timeinfo.tm_min;
		sec = timeinfo.tm_sec;
#endif

#ifdef OS_LINUX
		struct tm * timeinfo;
		timeinfo = localtime(&rawDateTime);
		hour = timeinfo->tm_hour;
		min = timeinfo->tm_min;
		sec = timeinfo->tm_sec;
#endif
	}
	String DateTime::toString() {
		int d, m, y;
		getDate(d, m, y);
		String sd, sm, sy;
		sy = y;
		if (m < 10) sm = "0" + (String)m; else sm = m;
		if (d < 10) sd = "0" + (String)d; else sd = d;
		return sy + "-" + sm + "-" + sd;
	}
	String DateTime::toString(DateTimeFormat dtf) {
		int d, m, y, h, mm, s;
		getDate(d, m, y);
		getTime(h, mm, s);
		String sD = d, sM = m, sY = y;
		String sH = h, sMM = mm, sS = s;
		if (sD.getLength() == 1) sD = "0" + sD;
		if (sM.getLength() == 1) sM = "0" + sM;

		if (sD.getLength() == 1) sH = "0" + sH;
		if (sM.getLength() == 1) sMM = "0" + sMM;
		if (sS.getLength() == 1) sS = "0" + sS;
		if (dtf == dtfRus) return sD + "." + sM + "." + sY;
		if (dtf == dtfYMDhm) return sY + "-" + sM + "-" + sD + " " + sH + ":" + sMM;
		return sY + "-" + sM + "-" + sD + " " + sH + ":" + sMM + ":" + sS;
	}
	long DateTime::getRawDateTime() {
		return rawDateTime;
	}
	void DateTime::setRawDateTime(long rawDT) {
		rawDateTime = rawDT;
	}
	long DateTime::getDifference(DateTime dt) {
		return rawDateTime - dt.getRawDateTime();
	}
	int DateTime::getAge() {
		DateTime dtNow;
		dtNow.now();

		int d1, m1, y1, d2, m2, y2;
		this->getDate(d1, m1, y1);
		dtNow.getDate(d2, m2, y2);

		int y = y2 - y1;
		int m = m2 - m1;
		int d = d2 - d1;
		if (m < 0) y--;
		else if (m == 0 && d < 0) y--;
		if (y < 0) return 0;
		return y;
	}
	int DateTime::minusDay() {
		rawDateTime -= 86400;
		return rawDateTime;
	}
	bool DateTime::operator==(DateTime value) {
		return rawDateTime == value.getRawDateTime();
	}
	bool DateTime::operator!=(DateTime value) {
		return rawDateTime != value.getRawDateTime();
	}
	bool DateTime::operator>(DateTime value) {
		return rawDateTime > value.getRawDateTime();
	}
	bool DateTime::operator>=(DateTime value) {
		return rawDateTime >= value.getRawDateTime();
	}
	bool DateTime::operator<(DateTime value) {
		return rawDateTime < value.getRawDateTime();
	}
	bool DateTime::operator<=(DateTime value) {
		return rawDateTime <= value.getRawDateTime();
	}


}
