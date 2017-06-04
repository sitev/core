#include "core.h"

namespace core {

Logger::Logger() {
}

Logger::Logger(String fileName) {
	set(fileName);
}

Logger::Logger(String path, String file) {
	set(path, file);
}


Logger::~Logger() {
}

void Logger::set(String fileName) {
	this->fileName = fileName;

	//f = new File(fileName, "a");
}

void Logger::set(String path, String file) {
	fileName = path + "/" + file;

	//f = new File(fileName, "a");
}

void Logger::setEnabled(bool value) {
	isEnabled = value;
}


void Logger::out(String flag, String s) {
	out(flag, s.to_string());
	/*
	application->mutexLogger.lock();
	if (isEnabled) {
		if (flag == "SCREEN") isScreen = true;
		if (!isScreen && fileName == "") return;

#ifdef OS_WINDOWS
		time_t t = std::time(nullptr);
		tm tm1 = *std::localtime(&t);
		char st[31];
		strftime(st, sizeof(st), "%d.%m.%y %H:%M:%S", localtime(&t));

		if (!isScreen) {
			FILE *f = fopen(fileName.to_string().c_str(), "a");
			fprintf(f, "[%s] %s %s\n", st, flag.to_string().c_str(), s.to_string().c_str());
			fclose(f);
		}
		else {
			fprintf(stdout, "[%s] %s %s\n", st, flag.to_string().c_str(), s.to_string().c_str());
		}
#endif

#ifdef OS_LINUX
		DateTime dt;
		dt.now();

		struct timeval tv, dtv;
		struct timezone tz;
		gettimeofday(&tv, &tz);

		dtv.tv_sec = tv.tv_sec - tv2.tv_sec;
		dtv.tv_usec = tv.tv_usec - tv2.tv_usec;
		if(dtv.tv_usec < 0) {
			dtv.tv_sec--;
			dtv.tv_usec += 1000000;
		}
		int delta = dtv.tv_sec * 1000 + dtv.tv_usec / 1000;
		tv2 = tv;

		if (!isScreen) {
			FILE *f = fopen(fileName.to_string().c_str(), "a");
			string s1 = dt.toString(dtfDatabase).to_string();
			fprintf(f, "%s %d %d %d %s: %s\n", s1.c_str(), tv.tv_sec, tv.tv_usec, delta, flag.to_string().c_str(), s.to_string().c_str());
			fclose(f);
		}
		else {
			string s1 = dt.toString(dtfDatabase).to_string();
			fprintf(stdout, "%s %d %d %d %s: %s\n", s1.c_str(), tv.tv_sec, tv.tv_usec, delta, flag.to_string().c_str(), s.to_string().c_str());
		}
#endif
	}
	application->mutexLogger.unlock();
	*/
}

void Logger::out(String flag, string s) {
	application->mutexLogger.lock();
	if (isEnabled) {
		if (flag == "SCREEN") isScreen = true;
		if (!isScreen && fileName == "") return;

#ifdef OS_WINDOWS
		time_t t = std::time(nullptr);
		tm tm1 = *std::localtime(&t);
		char st[31];
		strftime(st, sizeof(st), "%d.%m.%y %H:%M:%S", localtime(&t));

		if (!isScreen) {
			FILE *f = fopen(fileName.to_string().c_str(), "a");
			fprintf(f, "[%s] %s %s\n", st, flag.to_string().c_str(), s.c_str());
			fclose(f);
		}
		else {
			fprintf(stdout, "[%s] %s\n", st, s.c_str());
		}
#endif

#ifdef OS_LINUX
		DateTime dt;
		dt.now();

		struct timeval tv, dtv;
		struct timezone tz;
		gettimeofday(&tv, &tz);

		dtv.tv_sec = tv.tv_sec - tv2.tv_sec;
		dtv.tv_usec = tv.tv_usec - tv2.tv_usec;
		if (dtv.tv_usec < 0) {
			dtv.tv_sec--;
			dtv.tv_usec += 1000000;
		}
		int delta = dtv.tv_sec * 1000 + dtv.tv_usec / 1000;
		tv2 = tv;

		if (!isScreen) {
			FILE *f = fopen(fileName.to_string().c_str(), "a");
			string s1 = dt.toString(dtfDatabase).to_string();
			string s2 = flag.to_string();
			fprintf(f, "%s ", s1.c_str());
			fprintf(f, "%d %d %d ", (int)tv.tv_sec, (int)tv.tv_usec, delta);
			fprintf(f, "%s: ", s2.c_str());
			fprintf(f, "%s\n", s.c_str());
			fclose(f);
		}
		else {
			string s1 = dt.toString(dtfDatabase).to_string();
			fprintf(stdout, "%s ", s1.c_str());
			fprintf(stdout, "%d %d %d ", (int)tv.tv_sec, (int)tv.tv_usec, delta);
			fprintf(stdout, "%s\n", s.c_str());
		}
#endif
	}
	application->mutexLogger.unlock();
}

void Logger::out(String s) {
	this->out("INFO", s);
}

}
