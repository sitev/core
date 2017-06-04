#include <iostream>

#include "core.h"


namespace core {

//--------------------------------------------------------------------------------------------------
//----------          class Application          ---------------------------------------------------
//--------------------------------------------------------------------------------------------------

Application *application;

Application::Application() {
	application = this;
	logger = NULL;
	isRunning = false;
}
Application::~Application() {
}

void Application::run() {
	isRunning = true;
}

void Application::stop() {
	isRunning = false;
}

void Application::logger_out(String s) {
	if (logger != NULL) logger->out(s);
}

void Application::logger_out(String flag, String s) {
	if (logger != NULL) logger->out(flag, s);
}

void Application::logger_out8(String flag, string s) {
	if (logger != NULL) logger->out(flag, s);
}


//--------------------------------------------------------------------------------------------------
//----------          class WebApp          --------------------------------------------------------
//--------------------------------------------------------------------------------------------------

WebApp::WebApp() {

}


}
