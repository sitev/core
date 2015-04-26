#pragma once

//char
//short
//long
#ifdef OS_WINDOWS
#define big __int64
#endif

#ifdef OS_LINUX
#define big long long
#endif

#define byte unsigned char

#define uchar unsigned char
#define ushort unsigned short
#define ulong unsigned long
#define ubig unsigned big

//int
#define uint unsigned int

//float
//double
#define real double

//bool

#ifdef OS_LINUX
#define SOCKET int
#define DWORD ulong
#define ULONG ulong
#endif

