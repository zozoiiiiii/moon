/************************************************************************/
/*
@author:  junliang
@brief:   
			1. hierarchy feature.
			2. render feature, position is in Item(2d), VisObj(3d)
			3. component manager

			base object   : create/destroy, meta
			    |
			  entity      : parent/children, component, serialize

			ui: entity+ item transform component + item render component
			3d: entity+ transform component + render component


			// xml file format





@time:    2018/08/14
*/
/************************************************************************/
#pragma once

#include "public/object/mn_object.h"
#include "public/object/mn_object_mgr.h"
#include "public/object/mn_event_mgr.h"


NS_MN_BEGIN


class Component;
class Entity : public BaseObject
{
	MN_BEGIN(Entity, BaseObject);
	MN_FIELD(&Entity::m_name, "name", "");
	MN_END
public:
	Entity() {}
	virtual void OnCreate();
	virtual void OnDestroyed();

	Entity* Duplicate();
	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() { return m_name; }

	// parent/children
	void SetParent(Entity* pEntity);
	Entity* FindParent();
	void ClearChildren();
	VarList GetChildren();
	int GetChildCount();
	MN_OBJECTID GetChildByIndex(int index);
	bool IsChildExist(Entity* pEntity);
	void AddChild(Entity* pEntity);
	Entity* FindChild(const std::string& name);
	void RemoveChild(Entity* pEntity);
	void InsertAfter(Entity* pEntity, Entity* after);
	void InsertBefore(Entity* pEntity, Entity* before);
	//virtual void OnAddBatch(IBatchGroup* pBatchGroup);
	//virtual void OnRender(RenderContext* pCxt) {}
	//virtual void OnRenderBefore(RenderContext* pCxt);
	//virtual void OnRenderAfter(RenderContext* pCxt);
	//IRender* GetRender();

	// component
	std::vector<Component*> GetAllComponents();
	Component* FindComponent(const std::string& strClassName);
	Component* AddComponent(const std::string& strClassName);
	void RemoveComponent(MN_OBJECTID id);
	virtual void OnComponentAdded(Component* pComponent) {}
	virtual void OnComponentRemoved(Component* pComponent) {}


	void InvokeEvent(const std::string& event, const VarList& args = VarList());
	virtual void OnEvent(const std::string& event, const VarList& args = VarList()) {}
private:
	// parse from
	virtual bool parseFromObject(const rapidjson::Value* value);
	bool parseFromComponents(const rapidjson::Value* value);
	bool parseFromChildren(const rapidjson::Value* value);

	// serialize to
	virtual bool serializeObjectTo(rapidjson::Document* doc, rapidjson::Value* value);
	bool serializeComponents(rapidjson::Document* doc, rapidjson::Value* value);
	bool serializeChildren(rapidjson::Document* doc, rapidjson::Value* value);
private:
	std::string m_name;
	MN_OBJECTID m_parent;
	std::vector<MN_OBJECTID> m_children;
	std::map<std::string, Component*> m_components;
};













class Component : public BaseObject
{
	MN_BEGIN(Component, BaseObject);
	MN_END
public:
	Entity * GetOwner() { return m_pOwner; }
	virtual void OnAdded() {}
	virtual void OnRemoved() {}
//	virtual void OnRenderBefore(RenderContext* pCxt) {}
//	virtual void OnRenderAfter(RenderContext* pCxt) {}
	virtual void OnEvent(const std::string& event, const VarList& args = VarList()) {};
private:
	void SetOwner(Entity* pOwner) { m_pOwner = pOwner; }
private:
	Entity * m_pOwner;
	friend class Entity;
};


class System : public BaseObject
{
public:
	virtual void onComponentAdded(MN_OBJECTID id) {}
	virtual void onComponentRemoved(MN_OBJECTID id) {}
	virtual void onComponentUpdated(MN_OBJECTID id) {}
};

NS_MN_END


