/************************************************************************/
/* 
@author:    junliang
@brief:     type
@crossplatform help:
http://www.cnblogs.com/foohack/p/5013272.html
http://www.cnblogs.com/UnGeek/archive/2013/03/25/2981439.html

#ifdef _WIN32

#elif __ANDROID__

#elif __APPLE__
#endif

@time:      2018-1-19
*/
/************************************************************************/
#pragma once


// base type
#ifdef _WIN32
typedef signed __int8                   sint8;
typedef unsigned __int8                 uint8;
typedef signed __int16                  sint16;
typedef unsigned __int16                uint16;
typedef signed __int32                  sint32;
typedef unsigned __int32                uint32;
typedef signed __int64                  sint64;
typedef unsigned __int64                uint64;

#elif __ANDROID__
#include <stdint.h>
typedef int8_t                          sint8;
typedef uint8_t                         uint8;
typedef int16_t                         sint16;
typedef uint16_t                        uint16;
typedef int32_t                         sint32;
typedef uint32_t                        uint32;
typedef int64_t                         sint64;
typedef uint64_t                        uint64;

#elif __APPLE__
#endif

// variant type
enum MNVarType
{
    MNVT_UNKNOWN,
    MNVT_BOOL,
    MNVT_SINT32,
    MNVT_SINT64,
    MNVT_FLOAT,
    MNVT_DOUBLE,
    MNVT_STRING,
    MNVT_WSTRING,
    MNVT_CLASS,  // simple class like vec3f vv, transform aa, varlist()<<vv<<aa;
    //MNVT_POINTER, use BaseObject id instead, more safe, more simple.  IScene* pScene;varlist()<<pScene->getid()
    MNVT_MAX,
};


// namespace
#ifndef NS_MN_BEGIN
#define NS_MN_BEGIN                     namespace MN{
#define NS_MN_END                       }
#define USING_NS_MN                     using namespace MN;
#endif