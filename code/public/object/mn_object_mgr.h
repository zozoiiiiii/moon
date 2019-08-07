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

    BaseObject* create(const std::string& strClassName, MN_OBJECTID id = MN_INVALID_OBJECTID);
	void destroy(MN_OBJECTID id);
    BaseObject* find(MN_OBJECTID id);
    ReflectionMgr* getReflectionMgr(){return m_pReflectionMgr;}
    EventMgr* getEventMgr(){return m_pEventMgr;}
    virtual void setGlobal(const char* name, Var val);
    virtual Var findGlobal(const char* name);
    virtual BaseObject* findGlobalObject(const char* name);

    // on excute
    virtual void addExcute(BaseObject* pBaseObject);
    virtual void removeExcute(BaseObject* pBaseObject);
    virtual void onExcute(float sec);
private:
    std::map<MN_OBJECTID, BaseObject*> m_pObjects;
    std::map<std::string, Var> m_globalVars;
    std::vector<MN_OBJECTID> m_pExcute;
	ReflectionMgr* m_pReflectionMgr;
    EventMgr* m_pEventMgr;
    sint64 m_object_id_seed;
};

NS_MN_END