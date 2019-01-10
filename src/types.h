#pragma once

//bool  - 8 bit
//short - 16 bit
//int   - 32 bit
//long  - 32 / 64 bit (depricated)

#define byte char
#define ubyte unsigned char
#define ushort unsigned short
#define uint unsigned int

//size_t - 32 / 64 bit
//ilong - 64 bit
//ulong - 64 bit

#ifdef OS_WINDOWS
#define ilong __int64
#define ulong unsigned __int64
#endif

#ifdef OS_LINUX
#define ilong long long
#define ulong long long
#endif

#define big __int128
#define ubig unsigned __int128


//float
//double
#define real long double


//char     - 8 bit
//char16_t - 16 bit
//char32_t - 32 bit
