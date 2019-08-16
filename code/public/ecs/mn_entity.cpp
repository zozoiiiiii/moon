#include "mn_entity.h"
#include <algorithm>
#include "public/object/mn_memory.h"
#include "public/object/mn_reflection_mgr.h"
#include "platform/mn_string.h"

NS_MN_BEGIN

bool Entity::parseFromObject(const rapidjson::Value* pObject)
{
	if (!BaseObject::parseFromObject(pObject))
		return false;


	if (!parseFromComponents(pObject))
		return false;

	if (!parseFromChildren(pObject))
		return false;

	return true;
}


bool Entity::parseFromComponents(const rapidjson::Value* pObject)
{
	return true;
}

bool Entity::parseFromChildren(const rapidjson::Value* pObject)
{
	Value::ConstMemberIterator childrenItr = pObject->FindMember("children");
	if (childrenItr == pObject->MemberEnd())
		return true;


	bool bRet = true;
    ReflectionMgr* pReflectionMgr = GetReflectionMgr();
	const Value* children = &childrenItr->value;
	for (Value::ConstMemberIterator itr = children->MemberBegin(); itr != children->MemberEnd(); ++itr)
	{
		std::string key = itr->name.GetString();
		const rapidjson::Value* pChildValue = &itr->value;

		// new entity
		BaseObject* pChildObject = GetObjectMgr()->create(key);
		if (!pChildObject)
		{
			bRet = false;
			continue;
		}

		if (!pChildObject->IsInstanceOf("Entity"))
		{
			GetObjectMgr()->destroy(pChildObject->GetID());
			bRet = false;
			continue;
		}

		Entity* pChildEntity = (Entity*)pChildObject;
		if (!pChildEntity->parseFromObject(pChildValue))
		{
			bRet = false;
			continue;
		}

		AddChild(pChildEntity);
	}

	return bRet;
}



bool Entity::serializeObjectTo(rapidjson::Document* doc, rapidjson::Value* pObject)
{
	if (!BaseObject::serializeObjectTo(doc, pObject))
		return false;

	if (!serializeComponents(doc, pObject))
		return false;

	if (!serializeChildren(doc, pObject))
		return false;

	return true;
}


bool Entity::serializeComponents(rapidjson::Document* doc, rapidjson::Value* pObject)
{
	return true;
}

bool Entity::serializeChildren(rapidjson::Document* doc, rapidjson::Value* pObject)
{
	int nChildCnt = GetChildCount();
	if (nChildCnt <= 0)
		return true;

	bool bResult = true;
	rapidjson::Value children;
	children.SetObject();

	for (int i=0; i<m_children.size(); i++)
	{
		MN_OBJECTID id = m_children[i];
		BaseObject* pChildObject = GetObjectMgr()->find(id);
		if (!pChildObject)
		{
			bResult = false;
			continue;
		}


		if (!pChildObject->IsInstanceOf("Entity"))
		{
			bResult = false;
			continue;
		}

		Entity* pChildEntity = (Entity*)pChildObject;

		rapidjson::Value subValue;
		subValue.SetObject();
		if(!pChildEntity->serializeObjectTo(doc, &subValue))
		{
			bResult = false;
			continue;
		}

		rapidjson::Value subKey(pChildEntity->GetMetaClass()->name.c_str(), doc->GetAllocator());
		children.AddMember(subKey, subValue, doc->GetAllocator());
	}

	pObject->AddMember("children", children, doc->GetAllocator());
	return bResult;
}



void Entity::OnCreate()
{
	BaseObject::OnCreate();

// 	MN_OBJECTID parent = YY_INVALID_OBJECTID;
// 	MN_OBJECTID prev = YY_INVALID_OBJECTID;
// 	MN_OBJECTID next = YY_INVALID_OBJECTID;
// 	auto itor = args.find(PROP_ENTITY_PARENT);
// 	if (itor != args.end())
// 		parent = itor->second.GetInt64();
// 
// 	itor = args.find(PROP_ENTITY_PREV);
// 	if (itor != args.end())
// 		prev = itor->second.GetInt64();
// 
// 	itor = args.find(PROP_ENTITY_NEXT);
// 	if (itor != args.end())
// 		next = itor->second.GetInt64();
// 
// 	BaseObject* pParent = GetObjectMgr()->Find(parent);
// 	BaseObject* pPrev = GetObjectMgr()->Find(prev);
// 	BaseObject* pNext = GetObjectMgr()->Find(next);
// 	if (NULL != pParent)
// 	{
// 		if (!pParent->IsInstanceOf("Entity"))
// 			return;
// 
// 		Entity* pParentEntity = (Entity*)pParent;
// 		if (pPrev)
// 		{
// 			if (!pPrev->IsInstanceOf("Entity"))
// 				return;
// 
// 			pParentEntity->InsertAfter(this, (Entity*)pPrev);
// 		}
// 		else if (pNext)
// 		{
// 			if (!pNext->IsInstanceOf("Entity"))
// 				return;
// 
// 			pParentEntity->InsertBefore(this, (Entity*)pNext);
// 		}
// 		else
// 				pParentEntity->AddChild(this);
// 	}
}

void Entity::OnDestroyed()
{
	ClearChildren();
	GetObjectMgr()->destroy(GetID());
}


Entity* Entity::Duplicate()
{
	//std::string str = serializeTo();
	//return Entity::parseFrom(GetObjectMgr(), str);
	return NULL;
}


void Entity::InsertAfter(Entity* pEntity, Entity* after)
{
    std::vector<MN_OBJECTID>::iterator itor = std::find(m_children.begin(), m_children.end(), pEntity->GetID());
	if (itor == m_children.end())
		return;

	m_children.insert(itor, after->GetID());
}

void Entity::InsertBefore(Entity* pEntity, Entity* before)
{
	std::vector<MN_OBJECTID>::iterator itor = std::find(m_children.begin(), m_children.end(), pEntity->GetID());
	if (itor == m_children.end())
		return;

	//if(itor==m_children.begin())
		//m_children.insert()

	//m_children.insert(itor, before->GetID());
}

void Entity::SetParent(Entity* pEntity)
{
	if(pEntity)
		m_parent = pEntity->GetID();
}

Entity* Entity::FindParent()
{
	BaseObject* pObject = GetObjectMgr()->find(m_parent);
	if (NULL == pObject)
		return NULL;

	if (!pObject->IsInstanceOf("Entity"))
		return NULL;

	return (Entity*)pObject;
}


void Entity::ClearChildren()
{
	InvokeEvent("ClearChildren");

	int nCnt = GetChildCount();
	for (int i = 0; i < nCnt; i++)
	{
		MN_OBJECTID id = GetChildByIndex(i);
		BaseObject* pObject = GetObjectMgr()->find(id);
		if (NULL == pObject)
			continue;

		if (!pObject->IsInstanceOf("Entity"))
		{
			GetObjectMgr()->destroy(pObject->GetID());
			continue;
		}

		Entity* pChildEntity = (Entity*)pObject;
		pChildEntity->ClearChildren();
		GetObjectMgr()->destroy(pObject->GetID());
	}

	m_children.clear();
}

VarList Entity::GetChildren()
{
	VarList args;
	for (int i = 0; i < m_children.size(); i++)
	{
		args << m_children[i];
	}
	return args;
}


int Entity::GetChildCount()
{
	return m_children.size();
}

MN_OBJECTID Entity::GetChildByIndex(int index)
{
	if (index < 0 || index >= GetChildCount())
		return MN_INVALID_OBJECTID;

	return m_children[index];
}


Entity* Entity::FindChild(const std::string& name)
{
	int nCnt = GetChildCount();
	for (int i = 0; i < nCnt; i++)
	{
		MN_OBJECTID id = GetChildByIndex(i);
		BaseObject* pObject = GetObjectMgr()->find(id);
		if (NULL == pObject)
			continue;

		if (!pObject->IsInstanceOf("Entity"))
			continue;

		Entity* pEntity = (Entity*)pObject;
		if (pEntity->GetName() == name)
			return pEntity;
	}

	return NULL;
}

void Entity::AddChild(Entity* pEntity)
{
    std::vector<MN_OBJECTID>::iterator itor = std::find(m_children.begin(), m_children.end(), pEntity->GetID());
	if (itor != m_children.end())
		return;

	m_children.push_back(pEntity->GetID());
	pEntity->SetParent(this);
	int nIndex = m_children.size() - 1;

	InvokeEvent("AddChild", VarList()<<pEntity->GetID()<<nIndex);
}

void Entity::RemoveChild(Entity* pEntity)
{
	std::vector<MN_OBJECTID>::iterator itor = std::find(m_children.begin(), m_children.end(), pEntity->GetID());
	if (itor == m_children.end())
		return;

	int nIndex = itor - m_children.begin();
	InvokeEvent("RemoveChild", VarList() << pEntity->GetID()<<nIndex);

	pEntity->SetParent(NULL);
	m_children.erase(itor);
}

bool Entity::IsChildExist(Entity* pEntity)
{
	std::vector<MN_OBJECTID>::iterator itor = std::find(m_children.begin(), m_children.end(), pEntity->GetID());
	if (itor == m_children.end())
		return false;

	return true;

}
// 
// 
// void Entity::OnAddBatch(IBatchGroup* pBatchGroup)
// {
// 	pBatchGroup->AddNormalBatch(this);
// 
// 	int nChildNum = GetChildCount();
// 	for (int i = 0; i < nChildNum; i++)
// 	{
// 		MN_OBJECTID id = GetChildByIndex(i);
// 		BaseObject* pObject = GetObjectMgr()->Find(id);
// 		if (NULL == pObject)
// 			continue;
// 
// 		if (!pObject->IsInstanceOf("Entity"))
// 			continue;
// 
// 		Entity* pEntity = (Entity*)pObject;
// 		pEntity->OnAddBatch(pBatchGroup);
// 	}
// }
// 
// 
// IRender* Entity::GetRender()
// {
// 	if (NULL == m_pRender)
// 		m_pRender = IRender::Instance(GetObjectMgr());
// 
// 	return m_pRender;
// }


void Entity::InvokeEvent(const std::string& event, const VarList& args)
{
	// entity handle this event
	OnEvent(event, args);

	// component handle this event
	std::map<std::string, Component*>::iterator itor = m_components.begin();
	for (; itor != m_components.end(); itor++)
	{
		Component* pComponent = itor->second;
		pComponent->OnEvent(event, args);
	}
}
// 
// void Entity::OnRenderBefore(RenderContext* pCxt)
// {
// 	auto itor = m_components.begin();
// 	for (; itor != m_components.end(); itor++)
// 	{
// 		Component* pComponent = itor->second;
// 		pComponent->OnRenderBefore(pCxt);
// 	}
// }
// 
// void Entity::OnRenderAfter(RenderContext* pCxt)
// {
// 	auto itor = m_components.begin();
// 	for (; itor != m_components.end(); itor++)
// 	{
// 		Component* pComponent = itor->second;
// 		pComponent->OnRenderAfter(pCxt);
// 	}
// 
// 	m_bFirstRender = false;
// }

std::vector<Component*> Entity::GetAllComponents()
{
	std::vector<Component*> components;
    std::map<std::string, Component*>::iterator itor = m_components.begin();
	for (; itor != m_components.end(); itor++)
	{
		Component* pComponent = itor->second;
		components.push_back(pComponent);
	}
	return components;
}

Component* Entity::FindComponent(const std::string& strClassName)
{
	std::map<std::string, Component*>::iterator itor = m_components.find(strClassName);
	if (itor == m_components.end())
		return NULL;

	return itor->second;
}


Component* Entity::AddComponent(const std::string& strClassName)
{
	// same component already exist.
	if (NULL != FindComponent(strClassName))
		return NULL;

	BaseObject* pObject = GetObjectMgr()->create(strClassName);
	if (!pObject->IsInstanceOf("Component"))
		return NULL;

	Component* pComponent = (Component*)pObject;
	m_components[strClassName] = pComponent;
	pComponent->SetOwner(this);
	InvokeEvent("addComponent");
	return pComponent;
}

void Entity::RemoveComponent(MN_OBJECTID id)
{
	BaseObject* pComponent = GetObjectMgr()->find(id);
	if (NULL == pComponent)
		return;

	std::string strClassName = pComponent->GetMetaClass()->name;
	std::map<std::string, Component*>::iterator itor = m_components.find(strClassName);
	if (itor != m_components.end())
	{
		Component* pComponent = itor->second;
		InvokeEvent("removeComponent");
		m_components.erase(itor);
	}
}
NS_MN_END


