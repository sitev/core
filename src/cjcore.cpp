#include "cjcore.h"

std::u32string CjCore::utf8to32(std::string& utf8string) {
    std::u32string utf32string = U"";

    for(unsigned int i = 0; i < utf8string.length(); ++i) {
        if (static_cast<unsigned char>(utf8string[i]) <= 0x7f)
            utf32string.push_back(utf8string[i]);
        else if (static_cast<unsigned char>(utf8string[i]) < 0xe0) {
            unsigned char a = utf8string[i++];
            utf32string.push_back(((a & 0x1f) << 6) + (utf8string[i] & 0x3f));
        }
        else if (static_cast<unsigned char>(utf8string[i]) < 0xf0) {
            unsigned char a = utf8string[i++], b = utf8string[i++];
            utf32string.push_back(((a & 0x0f) << 12) + ((b & 0x3f) << 6) + (utf8string[i] & 0x3f));
        }
        else if (static_cast<unsigned char>(utf8string[i]) < 0xf8) {
            unsigned char a = utf8string[i++], b = utf8string[i++], c = utf8string[i++];
            utf32string.push_back(((a & 0x07) << 18) + ((b & 0x3f) << 12) + ((c & 0x3f) << 6) + (utf8string[i] & 0x3f));
        }
        else if (static_cast<unsigned char>(utf8string[i]) < 0xfc) {
            unsigned char a = utf8string[i++], b = utf8string[i++], c = utf8string[i++], d = utf8string[i++];
            utf32string.push_back(((a & 0x03) << 24) + ((b & 0x3f) << 18) + ((c & 0x3f) << 12) + ((d & 0x3f) << 6) + (utf8string[i] & 0x3f));
        }
        else if (static_cast<unsigned char>(utf8string[i]) < 0xfe) {
            unsigned char a = utf8string[i++], b = utf8string[i++], c = utf8string[i++], d = utf8string[i++], e = utf8string[i++];
            utf32string.push_back(((a & 0x01) << 30) + ((b & 0x3f) << 24) + ((c & 0x3f) << 18) + ((d & 0x3f) << 12) + ((e & 0x3f) << 6) + (utf8string[i] & 0x3f));
        }
    }

    return utf32string;
}

std::string CjCore::utf32to8(std::u32string& utf32string) {
    std::string utf8string = "";

    for (unsigned int i = 0; i < utf32string.length(); ++i) {
        if (utf32string[i] <= 0x7f)
            utf8string.push_back(utf32string[i] & 0x7f);
        else if (utf32string[i] <= 0x7ff) {
            utf8string.push_back(0xc0 + ((utf32string[i] & 0x7c0) >> 6));
            utf8string.push_back(0x80 + (utf32string[i] & 0x3f));
        }
        else if (utf32string[i] <= 0xffff) {
            utf8string.push_back(0xe0 + ((utf32string[i] & 0xf000) >> 12));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x0fc0) >> 6));
            utf8string.push_back(0x80 + (utf32string[i] & 0x3f));
        }
        else if (utf32string[i] <= 0x1fffff) {
            utf8string.push_back(0xf0 + ((utf32string[i] & 0x1c0000) >> 18));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x3f000) >> 12));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x0fc0) >> 6));
            utf8string.push_back(0x80 + (utf32string[i] & 0x3f));
        }
        else if (utf32string[i] <= 0x03ffffff) {
            utf8string.push_back(0xf8 + (utf32string[i] >> 24));
            utf8string.push_back(0x80 + ((utf32string[i] & 0xfc0000) >> 18));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x3f000) >> 12));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x0fc0) >> 6));
            utf8string.push_back(0x80 + (utf32string[i] & 0x3f));
        }
        else {
            utf8string.push_back(0xfc + (utf32string[i] >> 30));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x3f000000) >> 24));
            utf8string.push_back(0x80 + ((utf32string[i] & 0xfc0000) >> 18));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x3f000) >> 12));
            utf8string.push_back(0x80 + ((utf32string[i] & 0x0fc0) >> 6));
            utf8string.push_back(0x80 + (utf32string[i] & 0x3f));
        }
    }

    return utf8string;
}
