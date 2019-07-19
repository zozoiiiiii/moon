/************************************************************************/
/* 
@author:  junliang
@brief:   deep copy, not c struct
@time:    2017/11/6
*/
/************************************************************************/
#pragma once

#include "mn_type.h"
#include <string.h>
#include <string>
#include <wchar.h>
#include <math.h>

NS_MN_BEGIN
class Var
{
public:
    Var() :m_nType(MNVT_UNKNOWN){}
    Var(bool val) :m_nType(MNVT_BOOL){ m_bool = val;}
    Var(int val) :m_nType(MNVT_SINT32), m_int(val){}
    Var(sint64 val) : m_nType(MNVT_SINT64), m_int64(val){}
    Var(float val) : m_nType(MNVT_FLOAT), m_float(val){}
    Var(double val) : m_nType(MNVT_DOUBLE), m_double(val){}
    Var(const char* val) : m_nType(MNVT_STRING),m_str(val){}    // VarList::AddVar(const Var& v) will change to bool if no this function.
    Var(const wchar_t* val) :m_nType(MNVT_WSTRING),m_wstr(val){}
    Var(const std::string& val) : m_nType(MNVT_STRING),m_str(val){}
    Var(const std::wstring& val) :m_nType(MNVT_WSTRING), m_wstr(val){}

    int type() const{return m_nType;}
    bool setType(int nType){ if(nType > MNVT_UNKNOWN && nType <= MNVT_MAX)   return false; m_nType = nType; return true;}

    bool queryBool(bool& val) const{if(m_nType != MNVT_BOOL) return false; val=m_bool;;return true;}
    bool queryInt(int& val) const{if(m_nType != MNVT_SINT32) return false; val=m_int;;return true;}
    bool queryInt64(sint64& val) const{if(m_nType != MNVT_SINT64) return false; val=m_int64;;return true;}
    bool queryFloat(float& val) const{if(m_nType != MNVT_FLOAT) return false; val=m_float;;return true;}
    bool queryDouble(double& val) const{if(m_nType != MNVT_DOUBLE) return false; val=m_double;;return true;}
    bool queryStr(std::string& val) const{if(m_nType != MNVT_STRING) return false; val=m_str;;return true;}
    bool queryWstr(std::wstring& val) const{if(m_nType != MNVT_WSTRING) return false; val=m_wstr;;return true;}

    bool setBool(bool val){if (m_nType != MNVT_BOOL) return false;m_bool = val;return true;}
    bool setInt(int val){if (m_nType != MNVT_SINT32) return false;m_int = val;return true;}
    bool setInt64(sint64 val){if (m_nType != MNVT_SINT64) return false;m_int64 = val;return true;}
    bool setFloat(float val){if (m_nType != MNVT_FLOAT) return false;m_float = val;return true;}
    bool setDouble(double val){if (m_nType != MNVT_DOUBLE) return false;m_double = val;return true;}
    bool setStr(const std::string& val){if (m_nType != MNVT_STRING) return false;m_str = val;return true;}
    bool setWstr(const std::wstring& val){if (m_nType != MNVT_WSTRING) return false;m_wstr = val;return true;}

    bool operator==(const Var& copy) const
    {
        if (type() != copy.type())
            return false;

        switch (type())
        {
        case MNVT_BOOL:
            return m_bool == copy.m_bool;
        case MNVT_SINT32:
            return m_int == copy.m_int;
        case MNVT_SINT64:
            return m_int64 == copy.m_int64;
        case MNVT_FLOAT:
            return fabs( m_float - copy.m_float ) <= 0.0001;
        case MNVT_DOUBLE:
            return fabs( m_double - copy.m_double ) <= 0.0001;
        case MNVT_STRING:
            return m_str == copy.m_str;
        case MNVT_WSTRING:
            return m_wstr == copy.m_wstr;
        default:
            return false;
        }

        return false;
    }
private:
    int m_nType;

    union
    {
        bool m_bool;
        int m_int;
        sint64 m_int64;
        float m_float;
        double m_double;
    };
    std::string m_str;
    std::wstring m_wstr;
};


NS_MN_END