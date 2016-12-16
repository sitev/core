#include "cj.h"

namespace cj {

    u32string Utf::toUtf32(string utf8) {
        u32string utf32;

        for (unsigned int i = 0; i < utf8.length(); ++i) {
            if (static_cast<unsigned char>(utf8[i]) <= 0x7f)
                utf32.push_back(utf8[i]);
            else if (static_cast<unsigned char>(utf8[i]) < 0xe0) {
                unsigned char a = utf8[i++];
                utf32.push_back(((a & 0x1f) << 6) + (utf8[i] & 0x3f));
            }
            else if (static_cast<unsigned char>(utf8[i]) < 0xf0) {
                unsigned char a = utf8[i++], b = utf8[i++];
                utf32.push_back(((a & 0x0f) << 12) + ((b & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (static_cast<unsigned char>(utf8[i]) < 0xf8) {
                unsigned char a = utf8[i++], b = utf8[i++], c = utf8[i++];
                utf32.push_back(((a & 0x07) << 18) + ((b & 0x3f) << 12) + ((c & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (static_cast<unsigned char>(utf8[i]) < 0xfc) {
                unsigned char a = utf8[i++], b = utf8[i++], c = utf8[i++], d = utf8[i++];
                utf32.push_back(((a & 0x03) << 24) + ((b & 0x3f) << 18) + ((c & 0x3f) << 12) + ((d & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
            else if (static_cast<unsigned char>(utf8[i]) < 0xfe) {
                unsigned char a = utf8[i++], b = utf8[i++], c = utf8[i++], d = utf8[i++], e = utf8[i++];
                utf32.push_back(((a & 0x01) << 30) + ((b & 0x3f) << 24) + ((c & 0x3f) << 18) + ((d & 0x3f) << 12) + ((e & 0x3f) << 6) + (utf8[i] & 0x3f));
            }
        }

        return utf32;
    }

    string Utf::toUtf8(u32string utf32) {
        string utf8 = "";

        for (unsigned int i = 0; i < utf32.length(); ++i) {
            if (utf32[i] <= 0x7f)
                utf8.push_back(utf32[i] & 0x7f);
            else if (utf32[i] <= 0x7ff) {
                utf8.push_back(0xc0 + ((utf32[i] & 0x7c0) >> 6));
                utf8.push_back(0x80 + (utf32[i] & 0x3f));
            }
            else if (utf32[i] <= 0xffff) {
                utf8.push_back(0xe0 + ((utf32[i] & 0xf000) >> 12));
                utf8.push_back(0x80 + ((utf32[i] & 0x0fc0) >> 6));
                utf8.push_back(0x80 + (utf32[i] & 0x3f));
            }
            else if (utf32[i] <= 0x1fffff) {
                utf8.push_back(0xf0 + ((utf32[i] & 0x1c0000) >> 18));
                utf8.push_back(0x80 + ((utf32[i] & 0x3f000) >> 12));
                utf8.push_back(0x80 + ((utf32[i] & 0x0fc0) >> 6));
                utf8.push_back(0x80 + (utf32[i] & 0x3f));
            }
            else if (utf32[i] <= 0x03ffffff) {
                utf8.push_back(0xf8 + (utf32[i] >> 24));
                utf8.push_back(0x80 + ((utf32[i] & 0xfc0000) >> 18));
                utf8.push_back(0x80 + ((utf32[i] & 0x3f000) >> 12));
                utf8.push_back(0x80 + ((utf32[i] & 0x0fc0) >> 6));
                utf8.push_back(0x80 + (utf32[i] & 0x3f));
            }
            else {
                utf8.push_back(0xfc + (utf32[i] >> 30));
                utf8.push_back(0x80 + ((utf32[i] & 0x3f000000) >> 24));
                utf8.push_back(0x80 + ((utf32[i] & 0xfc0000) >> 18));
                utf8.push_back(0x80 + ((utf32[i] & 0x3f000) >> 12));
                utf8.push_back(0x80 + ((utf32[i] & 0x0fc0) >> 6));
                utf8.push_back(0x80 + (utf32[i] & 0x3f));
            }
        }

        return utf8;
    }
}
