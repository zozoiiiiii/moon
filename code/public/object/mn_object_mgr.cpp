#include "mn_object_mgr.h"
NS_MN_BEGIN


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

void ObjectMgr::setGlobal(const char* name, Var val)
{
    m_globalVars[name] = val;
}

Var ObjectMgr::findGlobal(const char* name)
{
    std::map<std::string, Var>::iterator itor = m_globalVars.find(name);
    if(itor!=m_globalVars.end())
        return itor->second;

    return Var();
}


BaseObject* ObjectMgr::findGlobalObject(const char* name)
{
    const Var& value = findGlobal(name);
    if (value.type() != MNVT_SINT64)
        return NULL;

    MN_OBJECTID id;
    value.queryInt64(id);
    return find(id);
}


void ObjectMgr::addExcute(BaseObject* pBaseObject)
{
    if(NULL==pBaseObject)
        return;

    m_pExcute.push_back(pBaseObject->GetID());
}

void ObjectMgr::removeExcute(BaseObject* pBaseObject)
{
    if(NULL==pBaseObject)
        return;

    int nSize = (int)m_pExcute.size();
    for(int i=0; i<nSize; i++)
    {
        MN_OBJECTID id = m_pExcute[i];
        if(id==pBaseObject->GetID())
        {
            m_pExcute.erase(m_pExcute.begin()+i);
            return;
        }
    }}


void ObjectMgr::onExcute(float sec)
{
    int nSize = (int)m_pExcute.size();
    for(int i=0; i<nSize; i++)
    {
        MN_OBJECTID id = m_pExcute[i];
        BaseObject* pEnt = find(id);
        if(NULL==pEnt)
        {
            // have erase issure, then end this loop, begin next time.
            m_pExcute.erase(m_pExcute.begin()+i);
            break;
        }

        pEnt->OnExcute(sec);
    }
}

NS_MN_END