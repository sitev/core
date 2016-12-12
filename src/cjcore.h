#pragma once

#include <string>

class CjCore {
public:
    std::u32string utf8to32(std::string& utf8string);
    std::string utf32to8(std::u32string& utf32string);
};
