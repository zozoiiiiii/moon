/************************************************************************/
/* 
@author:    junliang
@brief:     variant helper
@time:      2017-12-19
*/
/************************************************************************/
#pragma once
#include <string>
#include <wchar.h>
#include "mn_type.h"


// variant flag
enum VarFlag
{
    YVF_UNKNOWN,
    YVF_NORMAL,             // variant
    YVF_POINTER,            // variant*
    YVF_CONST_POINTER,      // const variant*
    YVF_REF,                // variant&
    YVF_CONST_REF,          // const variant&
};

template<typename T>
struct VarHelper
{
    static int GetType(){return MNVT_UNKNOWN;}
    static std::string GetTypeName(){return "";}
    static VarFlag GetFlag(){return YVF_NORMAL;}

    // out parameter
    static bool IsOut(){return false;} 
    static T Get(void* data){return *(T*)data;}
};

template<typename T> 
struct VarHelper<T*>{ 
    static int GetType(){return MNVT_UNKNOWN;}
    static std::string GetTypeName(){return "";}
    static VarFlag GetFlag(){return YVF_POINTER;} 
    static bool IsOut(){return true;} 
    static T* Get(void* data){return *(T**)data;} 
};



template<typename T>
struct VarHelper<const T*>{ 
    static int GetType(){return MNVT_UNKNOWN;}
    static std::string GetTypeName(){return "";}
    static VarFlag GetFlag(){return YVF_CONST_POINTER;} 
    static bool IsOut(){return false;} 
    static const T* Get(void* data){return *(const T**)data;} 
}; 

template<typename T>
struct VarHelper<T&>{ 
    static int GetType(){return MNVT_UNKNOWN;}
    static std::string GetTypeName(){return "";}
    static VarFlag GetFlag(){return YVF_REF;} 
    static bool IsOut(){return true;} 
    static T& Get(void* data){return *(T*)data;} 
}; 

template<typename T>
struct VarHelper<const T&>{ 
    static int GetType(){return MNVT_UNKNOWN;}
    static std::string GetTypeName(){return "";}
    static VarFlag GetFlag(){return YVF_CONST_REF;} 
    static bool IsOut(){return false;} 
    static const T& Get(void* data){return *(T*)data;} 
}; 



#define MN_TYPEHELPER(T, type_) \
    template<> \
struct VarHelper<T>{ \
    static int GetType(){return type_;} \
    static std::string GetTypeName(){return #T;} \
        static VarFlag GetFlag(){return YVF_NORMAL;} \
        static bool IsOut(){return false;} \
        static T Get(void* data){return *(T*)data;} \
    }; \
     template<> \
struct VarHelper<T*>{ \
    static int GetType(){return type_;} \
    static std::string GetTypeName(){return #T;} \
        static VarFlag GetFlag(){return YVF_POINTER;} \
        static bool IsOut(){return true;} \
        static T* Get(void* data){return *(T**)data;} \
     }; \
     template<> \
struct VarHelper<const T*>{ \
    static int GetType(){return type_;} \
    static std::string GetTypeName(){return #T;} \
        static VarFlag GetFlag(){return YVF_CONST_POINTER;} \
        static bool IsOut(){return false;} \
        static const T* Get(void* data){return *(const T**)data;} \
     }; \
     template<> \
struct VarHelper<T&>{ \
    static int GetType(){return type_;} \
    static std::string GetTypeName(){return #T;} \
        static VarFlag GetFlag(){return YVF_REF;} \
        static bool IsOut(){return true;} \
        static T& Get(void* data){return *(T*)data;} \
     }; \
     template<> \
struct VarHelper<const T&>{ \
    static int GetType(){return type_;} \
    static std::string GetTypeName(){return #T;} \
        static VarFlag GetFlag(){return YVF_CONST_REF;} \
        static bool IsOut(){return false;} \
        static const T& Get(void* data){return *(T*)data;} \
     }; 



using namespace std;

//fundamental type, like Q_DECLARE_METATYPE
MN_TYPEHELPER(bool, MNVT_BOOL);
MN_TYPEHELPER(int, MNVT_SINT32);
MN_TYPEHELPER(sint64, MNVT_SINT64);
MN_TYPEHELPER(float, MNVT_FLOAT);
MN_TYPEHELPER(double, MNVT_DOUBLE);
MN_TYPEHELPER(string, MNVT_STRING);
MN_TYPEHELPER(wstring, MNVT_WSTRING);


