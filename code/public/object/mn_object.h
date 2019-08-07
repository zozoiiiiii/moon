/************************************************************************/
/*
@author:    junliang
@brief:     base object
	1. create/destroy
	2. meta class

	{
	"class": "Object1"
	"properties":{
		"x":"0",
		"y":"0",
		object1:{"properties":{x:10}},
		object2:{"properties":{y:10}}
		}
	}
@time:      20160120
*/
/************************************************************************/
#pragma once

#include <string>
#include <map>
#include <vector>

#include "mn_type.h"
#include "mn_reflection.h"
#include "mn_var.h"
#include "mn_varlist.h"

#include "external/rapidjson/document.h"
#include "external/rapidjson/writer.h"
#include "external/rapidjson/prettywriter.h"
#include "external/rapidjson/stringbuffer.h"
using namespace rapidjson;

// guid
#ifndef MN_OBJECTID
#define  MN_OBJECTID sint64
#define MN_INVALID_OBJECTID 0
#endif


NS_MN_BEGIN
class ObjectMgr;
class ReflectionMgr;
class EventMgr;
class BaseObject
{
	MN_BEGIN(BaseObject, "");
	MN_END
public:
    static BaseObject* parseFrom(ObjectMgr* pObjMgr, const std::string& data, MN_OBJECTID id = MN_INVALID_OBJECTID);
    static BaseObject* parseFromFile(ObjectMgr* pObjMgr, const std::string& file, MN_OBJECTID id = MN_INVALID_OBJECTID);
    std::string serializeTo();
    bool serializeToFile(const std::string& file = "");

	virtual void OnCreate() {}
    virtual void OnDestroy(){}
    virtual void OnExcute(float sec) {}
    virtual BaseObject* duplicate() { return NULL; }
    virtual void parseFromObjectString(const std::string& data);

    ObjectMgr* GetObjectMgr(){return m_pObjectMgr;}
    EventMgr* GetEventMgr();
	ReflectionMgr* GetReflectionMgr();
    MN_OBJECTID GetID(){return m_id;}
	MetaClass* GetMetaClass() { return m_pMetaClass; };
	bool IsInstanceOf(const std::string& strClassName);

	bool SetFieldVal(const char* prop_name, const void* val);
	bool GetFieldVal(const char* prop_name, void* val);

    bool Invoke(void* result, const char* name);
    bool Invoke(void* result, const char* name, void* p1);
    bool Invoke(void* result, const char* name, void* p1, void* p2);
    bool Invoke(void* result, const char* name, void* p1, void* p2, void* p3);

protected:
    virtual bool parseFromObject(const rapidjson::Value* value);	
    virtual bool serializeObjectTo(rapidjson::Document* doc, rapidjson::Value* value);

    // property object should not contain baseobject(can used as child), like vec3f
    virtual bool serializeProperties(rapidjson::Document* doc, rapidjson::Value* value, MetaClass* pMetaClass, void* pInstance);
    virtual bool parseFromProperties(const rapidjson::Value* value, MetaClass* pMetaClass, void* pInstance);
private:
    void SetEntMgr(ObjectMgr* pMgr){m_pObjectMgr=pMgr;}
    void SetID(MN_OBJECTID id){m_id = id;}
    void SetCreator(MetaClass* creator){ m_pMetaClass = creator;}
    bool Invoke(void* result, const char* name, void* parameters[]);

    static bool setFieldValueFromStr(ReflectionMgr* pReflectionMgr, MetaField* pMetaField, void* pClassInstance, const std::string& str);
    static bool getFieldValueToStr(ReflectionMgr* pReflectionMgr, MetaField* pMetaField, void* pClassInstance, std::string& str);
private:
    MN_OBJECTID m_id;
    MetaClass* m_pMetaClass;
    ObjectMgr* m_pObjectMgr;
    friend class ObjectMgr;
};
NS_MN_END


