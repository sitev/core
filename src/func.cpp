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

	String generateSimpleUUID() {
#ifdef OS_WINDOWS
		char* str = new char[39];
		GUID guid;
		HRESULT h = CoCreateGuid(&guid);

		sprintf(str, "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		return str;
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
		gettimeofday(&tv, NULL);
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

}