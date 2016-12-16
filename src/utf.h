#pragma once

#include "cj.h"

namespace cj {
    class Utf {
    public:
        static u32string toUtf32(string utf8);
        static string toUtf8(u32string utf32);
    };
}
