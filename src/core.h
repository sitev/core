﻿#pragma once

#define _CRT_SECURE_NO_WARNINGS


#include "cfg.h"

#ifdef __linux__
#define OS_LINUX
#define cfg_WebApp
#else
#define OS_WINDOWS
#define cfg_WebApp
#endif

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

//#define M_PI 3.14159


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <time.h>

#ifdef OS_LINUX
#include <sys/io.h>
#endif

#ifdef OS_WINDOWS
#include <io.h>
#endif

#include <iostream>
#include <fstream>
#include <map>
#include <mutex>
#include <functional>

#ifdef OS_LINUX
#include <sys/resource.h>
#endif

#ifdef OS_LINUX
#include <dirent.h>
#endif

#ifdef OS_WINDOWS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef OS_LINUX
#include <uuid/uuid.h>
//	#include <gd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

#include <string>
#include <thread>

using namespace std;

#ifdef OS_WINDOWS
#include <iomanip>
//#include <ctime>
#endif

#ifdef USING_UTF

#ifdef OS_LINUX
#include <uchar.h>
typedef basic_string<char32_t> u32string;
#endif

#elif defined(USING_STL)

#include <codecvt>

typedef std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> Convert16;
typedef std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> Convert32;

#elif defined(USING_BOOST)

#include <uchar.h>
typedef basic_string<char32_t> u32string;
#include <boost/locale.hpp>
#endif

#ifdef OS_WINDOWS
#pragma comment(lib, "ws2_32.lib")
#endif

#include "types.h"
#include "func.h"
#include "object.h"
#include "utf.h"
#include "strings.h"
#include "list.h"
#include "stream.h"
#include "buffer.h"



