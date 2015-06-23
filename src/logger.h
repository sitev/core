#pragma once

namespace cj {

#define LOGGER_TRACE_FLAG 1
#define LOGGER_DEBUG_FLAG 1
#define LOGGER_INFO_FLAG 1
#define LOGGER_ERROR_FLAG 1
#define LOGGER_OUT_FLAG 1


#ifdef LOGGER_TRACE_FLAG
#define LOGGER_TRACE(s) application->logger_out("TRACE", s)
#else
#define LOGGER_TRACE(s)
#endif

#ifdef LOGGER_DEBUG_FLAG
#define LOGGER_DEBUG(s) application->logger_out("DEBUG", s)
#else
#define LOGGER_DEBUG(s)
#endif

#ifdef LOGGER_INFO_FLAG
#define LOGGER_INFO(s) application->logger_out("INFO", s)
#else
#define LOGGER_INFO(s)
#endif

#ifdef LOGGER_ERROR_FLAG
#define LOGGER_ERROR(s) application->logger_out("ERROR", s)
#else
#define LOGGER_ERROR(s)
#endif

#ifdef LOGGER_OUT_FLAG
#define LOGGER_OUT(s) application->logger_out(s)
#define LOGGER_OUT(flag, s) application->logger_out(flag, s)
#else
//#define LOGGER_OUT(s)
#define LOGGER_OUT(flag, s)
#endif

class Logger {
private:
	String fileName;

	struct timeval tv2;
	//struct timezone tz2;

public:
	Logger();
	Logger(String fileName);
	Logger(String path, String file);

	virtual ~Logger();

	virtual void set(String fileName);
	virtual void set(String path, String file);

	virtual void out(String s);
	virtual void out(String flag, String s);
};

}
