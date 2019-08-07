/************************************************************************/
/*
@author:    junliang
@brief:     reflection manager
@time:      20160120
*/
/************************************************************************/
#pragma once

#include "mn_type.h"
#include "mn_reflection.h"
#include "mn_var.h"


#define MN_REG(reflectionMgr, cls) reflectionMgr->regCreator(cls::MetaClassInstance());

NS_MN_BEGIN

class ReflectionMgr
{
public:
    virtual ~ReflectionMgr(){}
    inline MetaClass* findMetaClass(const std::string& strClassName);
    inline void regCreator(MetaClass* pCreator);

    inline MetaField* findMetaField(const std::string& strClassName, const std::string& strFieldName);
    inline MetaField* findMetaFieldFromAll(const std::string& strClassName, const std::string& strFieldName);
    inline void getAllMetaField(const std::string& strClassName, std::vector<MetaField*>& fields);

    inline bool isInstanceOf(MetaClass* pCreator, const std::string& strClassName);

private:
    std::map<std::string, MetaClass*> m_creatorClasses;
};


////////////////////////

MetaClass* ReflectionMgr::findMetaClass(const std::string& strClassName)
{
    std::map<std::string, MetaClass*>::iterator itor = m_creatorClasses.find(strClassName);
    if (itor == m_creatorClasses.end())
        return NULL;

    MetaClass* pec = itor->second;
    return pec;
}


void ReflectionMgr::regCreator(MetaClass* pCreator)
{
    std::map<std::string, MetaClass*>::iterator itor = m_creatorClasses.find(pCreator->name);
    if (itor != m_creatorClasses.end())
        return;

    m_creatorClasses[pCreator->name] = pCreator;
}


MetaField* ReflectionMgr::findMetaField(const std::string& strClassName, const std::string& strFieldName)
{
    MetaClass* pMetaClass = findMetaClass(strClassName);
    if(NULL == pMetaClass)
        return NULL;

    std::map<std::string, MetaField*>::iterator itor = pMetaClass->fields.find(strFieldName);
    if(itor == pMetaClass->fields.end())
        return NULL;

    return itor->second;
}

MetaField* ReflectionMgr::findMetaFieldFromAll(const std::string& strClassName, const std::string& strFieldName)
{
    MetaClass* pMetaClass = findMetaClass(strClassName);
    if (NULL == pMetaClass)
        return NULL;


    std::map<std::string, MetaField*>::iterator itor = pMetaClass->fields.find(strFieldName);
    if (itor == pMetaClass->fields.end())
    {
        return findMetaFieldFromAll(pMetaClass->parent, strFieldName);
    }

    return itor->second;
}

void ReflectionMgr::getAllMetaField(const std::string& strClassName, std::vector<MetaField*>& fields)
{
    MetaClass* pMetaClass = findMetaClass(strClassName);
    if (NULL == pMetaClass)
        return;

    getAllMetaField(pMetaClass->parent, fields);

    std::map<std::string, MetaField*>::iterator itor = pMetaClass->fields.begin();
    for (; itor != pMetaClass->fields.end(); itor++)
    {
        fields.push_back(itor->second);
    }
}

bool ReflectionMgr::isInstanceOf(MetaClass* pCreator, const std::string& strClassName)
{
    if(NULL==pCreator)
        return false;

    if(strClassName==pCreator->name)
        return true;

    // end of loop
    const std::string& strParent = pCreator->parent;
    if(strParent=="BaseObject" && strParent != strClassName)
        return false;

    MetaClass* pCreator_Parent = findMetaClass(strParent);
    if(NULL==pCreator_Parent)
    {
        return false;
    }

    return isInstanceOf(pCreator_Parent, strClassName);
}

NS_MN_END