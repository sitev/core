#pragma once

namespace cj {

class Application : public Object {
public:
	List *lstCanvas;
	List lstTimer;

	Logger *logger;

	mutex g_mutex;
	mutex mutexLogger;

	bool isRunning;

	Application();
	~Application();
	virtual void run();
	virtual void step(){}
	virtual void stop();
	virtual void logger_out(String s);
	virtual void logger_out(String flag, String s);
	virtual void logger_out8(String flag, string s);
};
class DesktopApp : public Application {
public:
	DesktopApp() {}
};
class LinuxApp : public DesktopApp {
public:
};

class WebApp : public Application {
public:
	String documentRoot;
	WebApp();
};
/*
#ifdef cfg_WebApp
	extern WebApp *application;
#else if
*/

extern Application *application;




}
