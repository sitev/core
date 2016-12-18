#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "cfg.h"

#ifdef __linux__
#define OS_LINUX
#define cfg_WebApp
#else
#define OS_WINDOWS
#define cfg_WebApp
#endif

#ifdef OS_LINUX
#include <sys/resource.h>
#include "uuid/uuid.h"
#endif

#ifdef OS_WINDOWS
#include <io.h>
#include <registry.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include <wctype.h>
#include <string.h>
#include <map>
#include <mutex>
#include <thread>

using namespace std;

#ifdef USING_UTF

#ifdef OS_LINUX
#include <uchar.h>
typedef basic_string<char32_t> u32string;
#endif

#elif USING_STL

#include <codecvt>

typedef std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> Convert16;
typedef std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> Convert32;

#include <iomanip>
#include <ctime>

#elif USING_BOOST
#include <uchar.h>
typedef basic_string<char32_t> u32string;
#include <boost/locale.hpp>
#endif

#include "types.h"
#include "func.h"
#include "object.h"
#include "utf.h"
#include "strings.h"
#include "list.h"
#include "stream.h"
#include "logger.h"
#include "config.h"
#include "xmlParser.h"

#include "application.h"
