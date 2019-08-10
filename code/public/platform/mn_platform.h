/************************************************************************/
/*
@author:  junliang
@time:    20190810
@brief:   platform
*/
/************************************************************************/
#pragma once


#ifdef _WIN32
#define _MN_PLATFORM_WIN32_
#elif __ANDROID__
#define _MN_PLATFORM_ANDROID_
#elif __APPLE__
#define _MN_PLATFORM_UTIL_APPLE_
#endif


// base type
#ifdef _MN_PLATFORM_WIN32_
typedef signed __int8                   sint8;
typedef unsigned __int8                 uint8;
typedef signed __int16                  sint16;
typedef unsigned __int16                uint16;
typedef signed __int32                  sint32;
typedef unsigned __int32                uint32;
typedef signed __int64                  sint64;
typedef unsigned __int64                uint64;

#elif _MN_PLATFORM_ANDROID_
#include <stdint.h>
typedef int8_t                          sint8;
typedef uint8_t                         uint8;
typedef int16_t                         sint16;
typedef uint16_t                        uint16;
typedef int32_t                         sint32;
typedef uint32_t                        uint32;
typedef int64_t                         sint64;
typedef uint64_t                        uint64;

#elif _MN_PLATFORM_UTIL_APPLE_
#endif


// variant type
// enum MNVarType
// {
// 	MNVT_UNKNOWN,
// 	MNVT_BOOL,
// 	MNVT_SINT32,
// 	MNVT_SINT64,
// 	MNVT_FLOAT,
// 	MNVT_DOUBLE,
// 	MNVT_STRING,
// 	MNVT_WSTRING,
// 	MNVT_CLASS,
// 	MNVT_CLASS_POINTER,
// 	MNVT_MAX,
// };
