#include "mn_object.h"
#include "mn_object_mgr.h"
#include "mn_memory.h"
#include "mn_reflection_mgr.h"
#include "mn_string.h"

NS_MN_BEGIN



BaseObject* BaseObject::parseFromFile(ObjectMgr* pObjMgr, const std::string& file, MN_OBJECTID id)
{
    FILE* pFile = fopen(file.c_str(), "r");
    if (NULL == pFile)
        return NULL;

    fseek(pFile, 0, SEEK_END);
    int nSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    AutoMem<char, 512> buf(nSize);
    fread(buf.GetBuf(), nSize, 1, pFile);
    fclose(pFile);

    return parseFrom(pObjMgr, buf.GetBuf(), id);
}

void BaseObject::parseFromObjectString(const std::string& data)
{
    Document doc;
    doc.Parse(data.c_str());
    if (!doc.IsObject())
        return;

    parseFromObject(&doc);
}

bool BaseObject::parseFromObject(const rapidjson::Value* pObject)
{
    ReflectionMgr* pReflectionMgr = GetReflectionMgr();
    return parseFromProperties(pObject, GetMetaClass(), this);
}

bool BaseObject::parseFromProperties(const rapidjson::Value* pObject, MetaClass* pMetaClass, void* pInstance)
{
    Value::ConstMemberIterator propertiesItr = pObject->FindMember("properties");
    if (propertiesItr == pObject->MemberEnd())
        return true;

    const Value* properties = &propertiesItr->value;

    bool bRet = true;
    ReflectionMgr* pReflectionMgr = GetReflectionMgr();
    Var var;
    for (Value::ConstMemberIterator itr = properties->MemberBegin(); itr != properties->MemberEnd(); ++itr)
    {
        std::string key = itr->name.GetString();
        MetaField* pMetaField = pReflectionMgr->findMetaFieldFromAll(pMetaClass->name, key.c_str());
        if (!pMetaField)
        {
            bRet = false;
            continue;
        }

        if (!itr->value.IsObject())
        {
            // base variant
            std::string strValue = itr->value.GetString();
            setFieldValueFromStr(pReflectionMgr, pMetaField, pInstance, strValue);
        }
        else
        {
            // object
            if (pMetaField->var_type != MNVT_CLASS)
            {
                bRet = false;
                continue;
            }

            MetaClass* pSubMetaClass = pReflectionMgr->findMetaClass(pMetaField->type_name);
            if (!pSubMetaClass)
            {
                bRet = false;
                continue;
            }

            // property object should not baseobject
            if (pReflectionMgr->isInstanceOf(pSubMetaClass, "BaseObject"))
            {
                bRet = false;
                continue;
            }

            void* pSubObject = pMetaField->Get(pInstance);
            parseFromProperties(&itr->value, pSubMetaClass, pSubObject);
        }
    }

    return bRet;
}

BaseObject* BaseObject::parseFrom(ObjectMgr* pObjMgr, const std::string& data, MN_OBJECTID id)
{
    ReflectionMgr* pReflectionMgr = pObjMgr->getReflectionMgr();
    Var var;
    Document doc;
    doc.Parse(data.c_str());
    if (!doc.IsObject())
        return NULL;

    // must 1 member: class name
    if (doc.MemberCount() != 1)
        return NULL;

    Value::ConstMemberIterator classItr = doc.MemberBegin();
    if (classItr == doc.MemberEnd())
        return NULL;

    std::string strClass = classItr->name.GetString();
    MetaClass* pMetaClass = pReflectionMgr->findMetaClass(strClass.c_str());
    if (!pMetaClass)
        return NULL;

    // create baseobject from meta name
    BaseObject* pObject = pObjMgr->create(strClass, id);
    if (!pObject)
        return NULL;

    if (!pObject->parseFromObject(&classItr->value))
        return NULL;

    return pObject;
}


bool BaseObject::serializeProperties(rapidjson::Document* doc, rapidjson::Value* pObject,MetaClass* pMetaClass, void* pInstance)
{
    rapidjson::Value properties;
    properties.SetObject();

    ReflectionMgr* pReflectionMgr = GetReflectionMgr();
    std::vector<MetaField*> fields;
    pReflectionMgr->getAllMetaField(pMetaClass->name, fields);
    for (int i = 0; i < fields.size(); i++)
    {
        MetaField* pMetaField = fields[i];
        std::string key = pMetaField->name;
        rapidjson::Value rjKey(key.c_str(), doc->GetAllocator());

        if (pMetaField->var_type == MNVT_CLASS)
        {
            std::string strChildClassName = pMetaField->type_name;
            void* pChildInstance = pMetaField->Get(pInstance);
            MetaClass* pChildMetaClass = pReflectionMgr->findMetaClass(strChildClassName);
            if(!pChildMetaClass)
                continue;

            // this object should not hierarchy of BaseObject(consider as child), like vec3f
            if (pReflectionMgr->isInstanceOf(pChildMetaClass, "BaseObject"))
                continue;

            rapidjson::Value rjVal;
            rjVal.SetObject();
            serializeProperties(doc, &rjVal, pChildMetaClass, pChildInstance);
            properties.AddMember(rjKey, rjVal, doc->GetAllocator());
        }
        else
        {
            // property is base type
            std::string strFieldVal;
            bool bRet = getFieldValueToStr(pReflectionMgr, pMetaField, pInstance, strFieldVal);
            if(!bRet)
                return false;

            rapidjson::Value rjVal(strFieldVal.c_str(), doc->GetAllocator());
            properties.AddMember(rjKey, rjVal, doc->GetAllocator());
        }
    }

    pObject->AddMember("properties", properties, doc->GetAllocator());
    return true;
}

bool BaseObject::serializeObjectTo(rapidjson::Document* doc, rapidjson::Value* pObject)
{
    bool bResult = true;
    ReflectionMgr* pReflectionMgr = GetReflectionMgr();

    // serialize properties data
    if (!serializeProperties(doc, pObject, GetMetaClass(), this))
        return false;

    return true;
}



std::string BaseObject::serializeTo()
{
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value objectVal;
    objectVal.SetObject();
    if (!serializeObjectTo(&doc, &objectVal))
        return false;

    rapidjson::Value key(GetMetaClass()->name.c_str(), doc.GetAllocator());
    doc.AddMember(key, objectVal, doc.GetAllocator());


    // convert rapidjson into string
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strBuf);
    doc.Accept(writer);
    return strBuf.GetString();
}

bool BaseObject::serializeToFile(const std::string& file)
{
    FILE* pFile = fopen(file.c_str(), "w");
    if (!pFile)
        return false;

    std::string str = serializeTo();
    fwrite(str.c_str(), str.length(), 1, pFile);
    fclose(pFile);
    return true;
}


/////////////////////////////////////////////////

ReflectionMgr* BaseObject::GetReflectionMgr()
{
    return m_pObjectMgr->getReflectionMgr();
}


EventMgr* BaseObject::GetEventMgr()
{
    return m_pObjectMgr->getEventMgr();
}

bool BaseObject::IsInstanceOf(const std::string& strClassName)
{
	ReflectionMgr* pReflectionMgr = GetObjectMgr()->getReflectionMgr();
	return pReflectionMgr->isInstanceOf(GetMetaClass(), strClassName);
}


bool BaseObject::SetFieldVal(const char* prop_name, const void* val)
{
	MetaField* pMetaField = GetMetaClass()->FindMetaField(prop_name);
	if (!pMetaField)
		return false;

	pMetaField->Set(this, val);
	return true;
}

bool BaseObject::GetFieldVal(const char* prop_name, void* val)
{
	MetaField* pMetaField = GetMetaClass()->FindMetaField(prop_name);
	if (!pMetaField)
		return false;

	val = pMetaField->Get(this);
	return true;
}

bool BaseObject::Invoke(void* result, const char* name, void* parameters[])
{
	if(NULL == m_pMetaClass)
        return false;

	std::map<std::string, MetaMethod*>::iterator itor = m_pMetaClass->methods.find(name);
	if(itor == m_pMetaClass->methods.end())
        return false;

	MetaMethod* pMethodCreator = m_pMetaClass->methods[name];
	pMethodCreator->Invoke(result, this, parameters);
    return true;
}


bool BaseObject::Invoke(void* result, const char* name)
{
	void* parameters[1];
	return Invoke(result, name, parameters);
}

bool BaseObject::Invoke(void* result, const char* name, void* p1)
{
	void* parameters[1];
	parameters[0] = p1;
	return Invoke(result, name, parameters);
}

bool BaseObject::Invoke(void* result, const char* name, void* p1, void* p2)
{
	void* parameters[2];
	parameters[0] = p1;
	parameters[1] = p2;
	return Invoke(result, name, parameters);
}

bool BaseObject::Invoke(void* result, const char* name, void* p1, void* p2, void* p3)
{
	void* parameters[3];
	parameters[0] = p1;
	parameters[1] = p2;
	parameters[2] = p3;
	return Invoke(result, name, parameters);
}


bool BaseObject::setFieldValueFromStr(ReflectionMgr* pReflectionMgr, MetaField* pMetaField, void* pClassInstance, const std::string& str)
{
    if(NULL==pReflectionMgr || NULL==pMetaField)
        return false;

    int nType = pMetaField->var_type;
    switch (nType)
    {
    case MNVT_BOOL:
        {
            bool bValue = true;
            if (str == "true" || str == "TRUE")
                bValue = true;
            else
                bValue = false;
            pMetaField->Set(pClassInstance, &bValue);
            break;
        }
        break;
    case MNVT_SINT32:
        {
            sint32 iValue = StrToInt32(str);
            pMetaField->Set(pClassInstance, &iValue);
            break;
        }
    case MNVT_SINT64:
        {
            sint64 val = StrToInt64(str);
            pMetaField->Set(pClassInstance, &val);
            break;
        }
    case MNVT_FLOAT:
        {
            float val = StrToFloat(str);
            pMetaField->Set(pClassInstance, &val);
            break;
        }
    case MNVT_DOUBLE:
        {
            double val = StrToFloat(str);
            pMetaField->Set(pClassInstance, &val);
            break;
        }
    case MNVT_STRING:
        {
            pMetaField->Set(pClassInstance, &str);
            break;
        }
    case MNVT_WSTRING:
        {
            std::wstring wstr = Utf8ToWStr(str);
            pMetaField->Set(pClassInstance, &wstr);
            break;
        }
    default:
        return false;
    }

    return true;
}

bool BaseObject::getFieldValueToStr(ReflectionMgr* pReflectionMgr, MetaField* pMetaField, void* pClassInstance, std::string& str)
{
    if(NULL==pReflectionMgr || NULL==pMetaField)
        return false;

    int nType = pMetaField->var_type;
    void* pPropVal = pMetaField->Get(pClassInstance);

    switch (nType)
    {
    case MNVT_BOOL:
        {
            bool bVal = *(bool*)pPropVal;
            if (bVal)
                str= "true";
            else
                str= "false;";
        }
        break;
    case MNVT_SINT32:
        {
            int nVal = *(int*)pPropVal;
            str = Int32ToStr(nVal);
        }
        break;

    case MNVT_SINT64:
        {
            sint64 val64 = *(sint64*)pPropVal;
            str= Int64ToStr(val64);
        }
        break;
    case MNVT_FLOAT:
        {
            float fVal = *(float*)pPropVal;
            str= FloatToStr(fVal);
        }
        break;
    case MNVT_DOUBLE:
        {
            double dVal = *(double*)pPropVal;
            str= DoubleToStr(dVal);
        }
        break;
    case MNVT_STRING:
        str= *(std::string*)pPropVal;
        break;
    case MNVT_WSTRING:
        {
            const std::wstring& wstrVal = *(std::wstring*)pPropVal;
            str= WStrToUtf8(wstrVal);
        }
        break;
    default:
        return false;
    }

    return true;

}

NS_MN_END


