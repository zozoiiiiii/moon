/************************************************************************/
/*
@author:  junliang
@time:    20130308
@brief:   variant list.
*/
/************************************************************************/
#pragma once

#include "mn_var.h"
#include <vector>
#include <string.h>

NS_MN_BEGIN
class VarList
{
public:
    //VarList& operator<<(bool val){m_data.push_back(val);}
    //VarList& operator<<(int val){m_data.push_back(val);}
    //VarList& operator<<(sint64 val){m_data.push_back(val);}
    //VarList& operator<<(float val){m_data.push_back(val);}
    //VarList& operator<<(double val){m_data.push_back(val);}
    //VarList& operator<<(const char* val){m_data.push_back(val);}
    //VarList& operator<<(const wchar_t* val){m_data.push_back(val);}
    //VarList& operator<<(const std::string& val){m_data.push_back(val);}
    //VarList& operator<<(const std::wstring& val){m_data.push_back(val);}
    VarList& operator<<(const Var& val){m_data.push_back(val);return *this;}
    void queryData(std::vector<Var>& data){data=m_data;}
private:
	std::vector<Var> m_data;
};


//////////////////////////////////////////////////////////////////////////

NS_MN_END
