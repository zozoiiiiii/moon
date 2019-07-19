/************************************************************************/
/*
@author:    junliang
@brief:     BaseObject manager
@time:      20160120
*/
/************************************************************************/
#pragma once

#include <string>
#include <map>
#include <vector>
#include "mn_type.h"
#include "mn_object.h"
#include "mn_varlist.h"
#include "mn_reflection.h"
#include "mn_reflection_mgr.h"
#include "mn_event_mgr.h"
NS_MN_BEGIN
class ObjectMgr
{
public:
    ObjectMgr():m_object_id_seed(10000)
    {
        m_pReflectionMgr = new ReflectionMgr;
        m_pEventMgr = new EventMgr;
    }

    ~ObjectMgr()
    {
        delete m_pReflectionMgr;
        delete m_pEventMgr;
    }

    inline  BaseObject* create(const std::string& strClassName, MN_OBJECTID id = MN_INVALID_OBJECTID);
	inline  void destroy(MN_OBJECTID id);
    inline  BaseObject* find(MN_OBJECTID id);
    ReflectionMgr* getReflectionMgr(){return m_pReflectionMgr;}
    EventMgr* getEventMgr(){return m_pEventMgr;}
private:
    std::map<MN_OBJECTID, BaseObject*> m_pObjects;
	ReflectionMgr* m_pReflectionMgr;
    EventMgr* m_pEventMgr;
    sint64 m_object_id_seed;
};

//////////////////////////////////////////////////

BaseObject* ObjectMgr::create(const std::string& strClassName, MN_OBJECTID id)
{
    // get unique BaseObject id
    MN_OBJECTID newid = m_object_id_seed++;

    MetaClass* pec = m_pReflectionMgr->findMetaClass(strClassName);
    if(pec == NULL || NULL == pec->create_func)
        return NULL;

    BaseObject* pBaseObject = (BaseObject*)pec->create_func();
    if (!pBaseObject)
        return NULL;

    m_pObjects[newid] = pBaseObject;
    pBaseObject->SetEntMgr(this);
    pBaseObject->SetID(newid);
    pBaseObject->SetCreator(pec);
    pBaseObject->OnCreate();
    //m_pEventMgr->Invoke(pBaseObject->GetID(), "ObjectCreated", pBaseObject->GetID());
    return pBaseObject;
}


void ObjectMgr::destroy(MN_OBJECTID id)
{
    std::map<MN_OBJECTID, BaseObject*>::iterator itor = m_pObjects.find(id);
    if(itor==m_pObjects.end())
    {
        return;
    }

    BaseObject* pBaseObject = itor->second;
    pBaseObject->OnDestroy();
    //m_pEventMgr->Invoke(pBaseObject->GetID(), "ObjectDestroyed", pBaseObject->GetID());
    m_pObjects.erase(itor);

    // destroy
    MetaClass* pec = pBaseObject->GetMetaClass();
    pec->destroy_func(pBaseObject);
}

BaseObject* ObjectMgr::find(MN_OBJECTID id)
{
    std::map<MN_OBJECTID, BaseObject*>::iterator itor = m_pObjects.find(id);
    if(itor==m_pObjects.end())
        return NULL;

    return itor->second;
}

NS_MN_END