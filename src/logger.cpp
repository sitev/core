#include "cj.h"

namespace cj {

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

void Logger::out(String flag, String s) {
	application->mutexLogger.lock();
	if (fileName == "") return;
#ifdef OS_WINDOWS
	time_t t = std::time(nullptr);
	tm tm1 = *std::localtime(&t);
	char st[31];
	strftime(st, sizeof(st), "%d.%m.%y %H:%M:%S", localtime(&t));

	FILE *f = fopen(fileName.to_string().c_str(), "a");
	fprintf(f, "[%s] %s %s\n", st, flag.to_string().c_str(), s.to_string().c_str());
	fclose(f);
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

	FILE *f = fopen(fileName.toString8().c_str(), "a");
	fprintf(f, "%s %d %d %d %s: %s\n", dt.toString(dtfDatabase).toString8().c_str(), tv.tv_sec, tv.tv_usec, delta, flag.toString8().c_str(), s.toString8().c_str());
	fclose(f);
#endif
	application->mutexLogger.unlock();
}

void Logger::out(String s) {
	this->out("INFO", s);
}

}
