#include "cj.h"

namespace cj {


	int round(real value) {
		return (int)(value + 0.5);
	}
	void swap(int &A, int &B)
	{
		int S = A;
		A = B;
		B = S;
	}
	void swap(real &A, real &B)
	{
		real S = A;
		A = B;
		B = S;
	}

	String generateUUID() {
#ifdef OS_WINDOWS
		char* str = new char[39];
		GUID pguid;
		HRESULT h = CoCreateGuid(&pguid);
		LPOLESTR szGUID = new WCHAR[39];
		StringFromGUID2(pguid, szGUID, 39);
		for (int i = 0; i < 39; i++)
			str[i] = (char)szGUID[i];
		return str;
#endif
#ifdef OS_LINUX
		uuid_t t;
		uuid_generate(t);

		char ch[36];
		memset(ch, 0, 36);
		uuid_unparse(t, ch);

		return ch;
#endif
	}

#ifdef OS_WINDOWS
	static int usleep_cnt = 0;
	void usleep(big usec) {
		Sleep(usec / 1000);
		//if (usleep_cnt % 10 == 0) Sleep(usec / 1000);
		usleep_cnt++;
		/*
			HANDLE timer;
			LARGE_INTEGER ft;

			ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

			timer = CreateWaitableTimer(NULL, TRUE, NULL);
			SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
			WaitForSingleObject(timer, INFINITE);
			CloseHandle(timer);
			*/
	}
#endif
#ifdef OS_LINUX
	ulong GetTickCount() {
		struct timeval tv; 
		gettimeofday(&tv,NULL); 
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	}
#endif


	ulong getUsageMemory()
	{
		/*
		long pages = sysconf(_SC_PHYS_PAGES);
		long page_size = sysconf(_SC_PAGE_SIZE);
		return pages * page_size;
		*/

#ifdef OS_LINUX
		int who = RUSAGE_SELF;
		struct rusage usage;
		getrusage(who, &usage);
		return usage.ru_maxrss;
#endif
#ifdef OS_WINDOWS
		return 0;
#endif
	}

	void sendMail(String toEMail, String fromEMail, String subject, String message) {
		if (toEMail == "") return;
#ifdef OS_LINUX
		String s = (String)"echo \"Content-Type: text/plain; charset=utf-8\nX-Mailer: Super Mailer\nTo: " + toEMail + "\nSubject: " + subject + "\n" + message + "\"|/usr/sbin/sendmail -f" + fromEMail + " " + toEMail;
		//page->out("debug", (String)"sendMail: " + s);
		//	FILE *f = popen("echo \"Subject: qqq002\nMessage here 002\"|sendmail -fvps_test@mail.ru vps_test@mail.ru", "w");
		try {
			FILE *f = popen(s.to_string().c_str(), "w");
			if (f != NULL) pclose(f);
		}
		catch (...) {
		}
#endif
	}

	void sendMail_s(string toEMail, string fromEMail, string subject, string message) {
		if (toEMail == "") return;
#ifdef OS_LINUX
		string s = "echo \"Content-Type: text/plain; charset=utf-8\nX-Mailer: Super Mailer\nTo: " + toEMail + "\nSubject: " + subject + "\n" + message + "\"|/usr/sbin/sendmail -f" + fromEMail + " " + toEMail;
		try {
			FILE *f = popen(s.c_str(), "w");
			if (f != NULL) pclose(f);
		}
		catch (...) {
		}
#endif
	}

	String dtRus(String dtUsa, int format) {
		String y = dtUsa.subString(0, 4);
		String m = dtUsa.subString(5, 2);
		String d = dtUsa.subString(8, 2);

		String t = "";
		if (format == 2) t = dtUsa.subString(11, dtUsa.getLength());
		else if (format == 1) t = dtUsa.subString(11, 5);
		//else if (format == 1) t = dtUsa.subString(11, 5);

		if (t == "") return d + "." + m + "." + y;
		return d + "." + m + "." + y + " " + t;
	}

#ifdef OS_WINDOWS
	void showMessage(String msg)
	{
///		::MessageBox(NULL, msg.to_string().c_str(), "Message", MB_OK);
	}
#endif
	real random() {
		return (real)rand() / RAND_MAX;
	}
	int random(int count) {
		return ((int)((real)rand() / RAND_MAX) * count);
	}
	/*
	bool FileExists(const char *fname)
	{
		return access(fname, 0) != -1;
	}
	*/
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

	Char::Char() {
	}

	Char::Char(char32_t ch) {
		this->ch = ch;
	}

	bool Char::operator==(Char value) {
		return ch == value.ch;
	}
	bool Char::operator!=(const Char value) {
		return ch != value.ch;
	}
	bool Char::operator>(const Char value) {
		return ch > value.ch;
	}
	bool Char::operator>=(const Char value) {
		return ch >= value.ch;
	}
	bool Char::operator<(const Char value) {
		return ch < value.ch;
	}
	bool Char::operator<=(const Char value) {
		return ch <= value.ch;
	}


	String::String() {
//		s8 = this->to_string();
	}
	String::String(const String& value) {
		String v(value);
//		s8 = this->to_string();
	}
	String::String(String& value) {
		s = value.s;
//		s8 = this->to_string();
	}
	String::String(string value) {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		s = convert32.from_bytes(value);
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
		s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif

//		s8 = this->to_string();
	}
	String::String(u32string value) {
		s = value;
//		s8 = this->to_string();
	}
	String::String(char32_t value) {
		s = value;
//		s8 = this->to_string();
	}
	String::String(const char *value) {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		string s8 = value;
		s = convert32.from_bytes(s8);
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
	    s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif

//		s8 = this->to_string();
	}
	string String::to_string() {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		string s8 = convert32.to_bytes(s);
		return s8;
#endif

#ifdef OS_LINUX
		
		string s8 = boost::locale::conv::utf_to_utf<char>(s);
		return s8;
#endif
	}
	String::String(char *value) {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		s = convert32.from_bytes(value);
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
	s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif
//		s8 = this->to_string();
	}
	String::String(char value) {
		char mys[2];
		mys[0] = value;
		mys[1] = 0;
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		s = convert32.from_bytes(mys);
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
	s = boost::locale::conv::utf_to_utf<char32_t>(mys);
#endif
//		s8 = this->to_string();
	}
	String::String(int value) {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		s = convert32.from_bytes(::to_string(value));
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
		char values8[20];
		sprintf(values8, "%d", value);
		s = boost::locale::conv::utf_to_utf<char32_t>(values8);
#endif
//		s8 = this->to_string();
	}
	String::String(real value) {
		fromFloat(value, 10);
//		s8 = this->to_string();
	}
	String::String(bool value) {
		
#ifdef OS_WINDOWS && _MSC_VER == 1800
		Convert32 convert32;
		if (value) s = convert32.from_bytes("1");
		else s = convert32.from_bytes("0");
#endif

#ifdef OS_LINUX || OS_WINDOWS && _MSC_VER == 1900
		
		if (value) s = boost::locale::conv::utf_to_utf<char32_t>("1");
		else s = boost::locale::conv::utf_to_utf<char32_t>("0");
#endif
//		s8 = this->to_string();
	}
	String::~String() {
	}

	Char String::getChar(int index) {
		Char ch(s[index]);
		return ch;
	}
	String String::getCharString(int index) {
		String mys = s[index];
		return mys;
	}
	void String::setChar(int index, Char ch) {
		s[index] = ch.ch;
	}
	void String::setChar(int index, String ch) {
		s[index] = ch.s.c_str()[0];
	}
	int String::getCharCode(int index) {
		return 0;
	}
	void String::setCharCode(int index, int code) {
	}
	String& String::operator=(const String& value) {
		s = value.s;
//		s8 = this->to_string();
		return *this;
	}
	String String::operator+(String value) {
		u32string u32 = this->s + value.s;
		String str(u32);
		return str;
	}
	String operator+(const char* value, String stvalue) {
		String retString(value);
		retString += stvalue;
		return retString;
	}
	String String::operator+=(String value) {
		u32string u32 = s += value.s;
		String str(u32);
//		s8 = str.to_string();
		return str;
	}
	bool String::operator==(String value) {
		return s == value.s;
	}
	bool String::operator!=(String value) {
		return s != value.s;
	}
	bool String::operator>(String value) {
		return s > value.s;
	}
	bool String::operator>=(String value) {
		return s >= value.s;
	}
	bool String::operator<(String value) {
		return s < value.s;
	}
	bool String::operator<=(String value) {
		return s <= value.s;
	}
	int String::getLength() {
		return s.length();
	}
	void String::setLength(int value) {
	}
	String String::subString(int pos, int count) {
		if (pos < 0)
			return "";
		String s32;
		try {
			u32string u = s.substr(pos, count);
			s32 = u;
			string s8 = s32.to_string();
		}
		catch (...) {
			u32string u = s.substr(pos, count);
			s32 = u;
			string s8 = s32.to_string();
		}
		return s32;
	}
	String String::subString(int pos) {
		if (pos < 0)
			return "";
		String s32;
		u32string u = s.substr(pos);
		s32 = u;
		string s8 = s32.to_string();
		return s32;
	}
	int String::getPos(String str) {
		int len = str.getLength();
		if (len <= 0) return -1;
		for (int i = 0; i <= getLength() - len; i++)
		{
			String s = subString(i, len);
			if (s == str) return i;
		}
		return -1;
	}
	int String::getPosBack(String str) {
		int len = str.getLength();
		if (len <= 0) return -1;
		for (int i = getLength() - len; i >= 0; i--)
		{
			String s = subString(i, len);
			if (s == str) return i;
		}
		return -1;
	}
	int String::toInt() {
		//s8 = "123";
		//int a = stoi(s8);
		String t = s;
		int a = strtol(t.to_string().c_str(), NULL, 0);
		return a;
	}
	real String::toFloat() {
		return 0;
	}
	String String::upperCase() {
		s[0] = towupper(s[0]);
		return *this;
	}
	String String::lowerCase() {
		int count = getLength();
		String s = *this;
		for (int i = 0; i < count; i++)
		{
			int Code = getCharCode(i);
			if (Code >= 65 && Code <= 90)
			{
				s.setCharCode(i, Code + 32);
			}
		}
		return s;
	}
	String String::firstUpperCase() {
		int count = getLength();
		if (count == 0) return "";

		String s = *this;
		int Code = getCharCode(0);
		if (Code >= 97 && Code <= 122)
		{
			s.setCharCode(0, Code - 32);
		}
		return s;
	}
	String String::firstLowerCase() {
		int count = getLength();
		if (count == 0) return "";

		String s = *this;
		int Code = getCharCode(0);
		if (Code >= 65 && Code <= 90)
		{
			s.setCharCode(0, Code + 32);
		}
		return s;
	}
	void String::fromFloat(real value, int digit) {
	}

	//--------------------------------------------------------------------------------------------------
	//----------          ����� List          ----------------------------------------------------------
	//--------------------------------------------------------------------------------------------------

	List::List() {
		memory = NULL;//iMemory = NULL;
		count = capacity = 0;
	}
	List::~List() {
		memory = NULL;//iMemory = NULL;
	}
	void List::assign(List *list) {
		this->clear();
		if (list == NULL) return;
		int count = list->getCount();
		for (int i = 0; i < count; i++) {
			this->add(list->getItem(i));
		}
	}
	int List::getCapacity() {
		return capacity;
	}
	void List::setCapacity(int value) {
		capacity = value;
		//	if (memory == NULL) memory = (Object**)malloc(value * sizeof(Object*));
		//	else 
		try {
			memory = (Object**)realloc(memory, value * sizeof(Object*));
		}
		catch(...) {
			printf("List: error realloc\n");
			memory = NULL;
			capacity = 0;
		}
		//iMemory = memory;
	}
	int List::getCount() {
		return count;
	}
	Object* List::add(Object* item) {
		if (count >= capacity || memory == NULL) {
			setCapacity(capacity + LIST_CAPACITY_STEP);
		}
		memory[count] = (Object*)item;
		count++;

		return item;
	}
	void List::insert(int index, Object* item) {
		if (count >= capacity || memory == NULL) {
			setCapacity(capacity + LIST_CAPACITY_STEP);
		}
		for (int i = count - 1; i >= index; i--) {
			memory[i + 1] = memory[i];
		}
		memory[index] = (Object*)item;
		count++;
	}
	Object* List::getItem(int index) {
		if (memory == NULL) return NULL;
		Object *res = memory[index];
		return res;
	}
	Object* List::getFirst() {
		if (memory == NULL) return NULL;
		if (count == 0) return NULL;
		return getItem(0);
	}
	Object* List::getLast() {
		if (memory == NULL) return NULL;
		if (count == 0) return NULL;
		return getItem(count - 1);
	}
	void List::setItem(int index, Object* item) {
		if (memory == NULL) return;
		memory[index] = (Object*)item;
	}
	void List::change(int index1, int index2) {
		Object *data1 = getItem(index1);
		Object *data2 = getItem(index2);
		setItem(index1, data2);
		setItem(index2, data1);
	}
	void List::moveTo(int index1, int index2) {
		if (memory == NULL) return;
		if (index1 == index2) return;
		if (index1 <= count || index2 <= count) return;
		if (index1 > index2) {
			Object *data = memory[index1];
			for (int i = index1 - 1; i >= index2; i--) {
				memory[i + 1] = memory[i];
			}
			memory[index2] = data;
		}
	}
	int List::indexOf(Object* item) {
		if (memory == NULL) return -1;
		for (int i = 0; i < count; i++)
		{
			Object *cur = getItem(i);
			if (cur == item) return i;
		}
		return -1;
	}
	void List::del(int index) {
		if (memory == NULL) return;
		if (index < 0) return;
		if (count == 0) return;
		if (index >= count) return;

		for (int i = index; i < count - 1; i++) {
			memory[i] = memory[i + 1];
		}
		count--;
	}
	int List::del(Object* item) {
		int index = indexOf(item);
		del(index);
		return index;
	}
	void List::remove(int index) {
		if (memory == NULL) return;
		if (index < 0) return;
		if (count == 0) return;
		delete memory[index];

		for (int i = index; i < count - 1; i++) {
			memory[i] = memory[i + 1];
		}
		count--;
	}
	int List::remove(Object* item) {
		int index = indexOf(item);
		remove(index);
		return index;
	}
	void List::clear() {
		if (memory == NULL) return;
		int count;
		while ((count = getCount()) != 0)
		{
			del(count - 1);
		}
	}
	void List::kill() {
		if (memory == NULL) return;
		int count;
		while ((count = getCount()) != 0)
		{
			remove(count - 1);
		}
	}

	//---------------------------------------------------------------------------
	//----------  StringList   ----------------------------------------------------
	//---------------------------------------------------------------------------
	StringList::StringList()
	{
	}
	String StringList::getClassName()
	{
		return "StringList";
	}
	void StringList::add(String* str)
	{
		String *S = new String(*str);
		List::add(S);
	}
	void StringList::add(String str)
	{
		String *S = new String(str);
		List::add(S);
	}
	void StringList::insert(int index, String str)
	{
		String *S = new String(str);
		List::insert(index, S);
	}
	String* StringList::getItem(int index)
	{
		return (String*)List::getItem(index);
	}
	String StringList::getString(int index)
	{
		return *((String*)List::getItem(index));
	}
	void StringList::setItem(String* str, int index)
	{
		List::setItem(index, str);
	}
	void StringList::setString(String str, int index)
	{
		String *S = new String(str);
		List::setItem(index, S);
	}
	int StringList::indexOf(String* Item)
	{
		return List::indexOf(Item);
	}
	int StringList::remove(String* Item)
	{
		return List::remove(Item);
	}
	int StringList::remove(String str)
	{
		int count = getCount();
		for (int i = 0; i < count; i++)
		{
			if (str == getString(i))
			{
				remove(i);
				return i;
			}
		}
		return -1;
	}
	bool StringList::find(String str)
	{
		int count = getCount();
		for (int i = 0; i < count; i++)
		{
			if (str == getString(i)) return true;
		}
		return false;
	}


	//--------------------------------------------------------------------------------------------------
	//----------          ParameterList          -------------------------------------------------------
	//--------------------------------------------------------------------------------------------------

	ParamList::ParamList() {
	}

	ParamList::~ParamList() {
	}

	void ParamList::add(String name, String value) {
		pars.insert(std::pair<string, string>(name.to_string(), value.to_string()));
	}

	void ParamList::insert(String name, String value) {
		pars.insert(std::pair<string, string>(name.to_string(), value.to_string()));
	}

	void ParamList::clear() {
		pars.clear();
	}
	int ParamList::getCount() {
		return pars.size();
	}
	bool ParamList::parse(String s) {
		return true;
	}

	String ParamList::getValue(String name) {
		string v = pars[name.to_string()];
		printf("getValue: %s = %s\n", name.to_string().c_str(), v.c_str());
		return pars[name.to_string()];
	}

	String ParamList::getName(int index) {
		auto iter = pars.begin();
		for (int i = 0; i < index; i++) iter++;
		return iter->first;
	}

	String ParamList::getValue(int index) {
		auto iter = pars.begin();
		for (int i = 0; i < index; i++) iter++;
		return iter->second;
	}

	void ParamList::add(string name, string value) {
		pars.insert(std::pair<string, string>(name, value));
	}
	void ParamList::insert(string name, string value) {
		pars.insert(std::pair<string, string>(name, value));
	}
	string ParamList::getValue_s(string name) {
		return pars[name];
	}
	string ParamList::getName_s(int index) {
		auto iter = pars.begin();
		for (int i = 0; i < index; i++) iter++;
		return iter->first;
	}
	string ParamList::getValue_s(int index) {
		auto iter = pars.begin();
		for (int i = 0; i < index; i++) iter++;
		return iter->second;
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
