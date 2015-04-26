#pragma once

namespace cj {

//Trace — вывод всего подряд. На тот случай, если Debug не позволяет локализовать ошибку.
//Debug — журналирование моментов вызова «крупных» операций. Старт/остановка потока, запрос пользователя и т.п.
//Info — разовые операции, которые повторяются крайне редко, но не регулярно. (загрузка конфига, плагина, запуск бэкапа)

#define LOGGER_TRACE_FLAG 1
#define LOGGER_DEBUG_FLAG 1
#define LOGGER_INFO_FLAG 1
#define LOGGER_ERROR_FLAG 1

#ifdef LOGGER_TRACE_FLAG
#define LOGGER_TRACE(s) application->logger_out("TRACE", s)
#endif

#ifdef LOGGER_DEBUG_FLAG
#define LOGGER_DEBUG(s) application->logger_out("DEBUG", s)
#endif

#ifdef LOGGER_INFO_FLAG
#define LOGGER_INFO(s) application->logger_out("INFO", s)
#endif

#ifdef LOGGER_ERROR_FLAG
#define LOGGER_ERROR(s) application->logger_out("ERROR", s)
#endif

#define LOGGER_OUT(s) application->logger_out(s)
#define LOGGER_OUT(flag, s) application->logger_out(flag, s)


class Logger {
private:
	String fileName;

	struct timeval tv2;
	//struct timezone tz2;

public:
	Logger();
	Logger(String fileName);
	Logger(String path, String file);

	~Logger();

	virtual void set(String fileName);
	virtual void set(String path, String file);

	virtual void out(String s);
	virtual void out(String flag, String s);
};

}
