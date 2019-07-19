/************************************************************************/
/* 
@author:    junliang
@brief:     a class of a class.
@time:      2018-1-8
*/
/************************************************************************/
#pragma once

#include <map>
#include <string>
#include "mn_var_helper.h"



struct MetaField;
struct MetaMethod;



struct MetaClass
{
    typedef void* (*CB_Create)();
    typedef void(*CB_Destroy)(void* ptr);

    CB_Create create_func;
    CB_Destroy destroy_func;
    std::string name;
    std::string parent;
    std::map<std::string, MetaMethod*> methods;
    std::map<std::string, MetaField*> fields;

	MetaField* FindMetaField(const char* name)
	{
        std::map<std::string, MetaField*>::iterator itor = fields.find(name);
		if (itor == fields.end())
			return NULL;

		return itor->second;
	}

	MetaMethod* FindMetaMethod(const char* name)
	{
        std::map<std::string, MetaMethod*>::iterator itor = methods.find(name);
		if (itor == methods.end())
			return NULL;

		return itor->second;
	}
};

