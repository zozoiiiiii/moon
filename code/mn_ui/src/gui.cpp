#include "gui.h"
#include "font/font_manager.h"
#include <algorithm>

void GUI::open()
{
    FontManager::Instance()->Init(GetObjectMgr());

    m_pRender = IRender::Instance(GetObjectMgr());
    m_pUIBatchGroup = m_pRender->GetUIBatchGroup();
    m_pRenderContext = m_pUIBatchGroup->GetRenderContext();
    m_pDeskTop = (Item*)GetObjectMgr()->create("Item");
    if (NULL == m_pDeskTop)
        return;

    m_pDeskTop->SetName("DeskTopForm");

    GetEventMgr()->ConnectGlobals("AddBatch_Items", fastdelegate::MakeDelegate(this, &GUI::onEvent_AddBatch));


    m_pRenderContext->nRenderType = RT_Normal;
}

void GUI::close()
{

}

void GUI::ReSize(float w, float h)
{
	if (NULL == m_pRender)
		return;

	m_pRender->SetWinWidth(w);
	m_pRender->SetWinHeight(h);
	m_pRender->SetDeviceWidth(w);
	m_pRender->SetDeviceHeight(h);
	m_pRender->ResetDevice();
}

MN_OBJECTID GUI::GetDesktopForm() const
{
	if (!m_pDeskTop)
		return MN_INVALID_OBJECTID;

	return m_pDeskTop->GetID();
}

void GUI::AddModalForm(MN_OBJECTID control)
{
	m_modalForms.push_back(control);
}

void GUI::RemoveModalForm(MN_OBJECTID control)
{
	std::vector<MN_OBJECTID>::iterator itor = std::find(m_modalForms.begin(), m_modalForms.end(), control);
	if (itor == m_modalForms.end())
		return;

	m_modalForms.erase(itor);
}



// desktop form, modal from
// child1, child2, c3,c4 from form1
// child1, c2, c3 from child1
//scene tree.
void GUI::onEvent_AddBatch(const char* name, const MN::VarList& args)
{
	if (!m_pDeskTop)
		return;

	visitEntities(m_pDeskTop);

	// add all render object to painter batch group.
	int nModalFormsNum = m_modalForms.size();
	for (int i = 0; i < nModalFormsNum; i++)
	{
		MN_OBJECTID formID = m_modalForms[i];
		BaseObject* pObject = GetObjectMgr()->find(formID);
		if(NULL == pObject)
			continue;

		if(!pObject->IsInstanceOf("Item"))
			continue;

		Item* pForm = (Item*)pObject;
		visitEntities(pForm);
	}
}


void GUI::visitEntities(Item* pEntity)
{
	// components
	std::vector<Component*> components = pEntity->GetAllComponents();
	int nCnt = components.size();
	for (int i = 0; i < nCnt; i++)
	{
		Component* pComponent = components[i];
		if(!pComponent->IsInstanceOf("RenderComponent"))
			continue;

		RenderComponent* pRenderComponent = (RenderComponent*)pComponent;
		pRenderComponent->OnAddBatch(m_pUIBatchGroup);
	}
		 
	// children
	int nChildNum = pEntity->GetChildCount();
	for (int i = 0; i < nChildNum; i++)
	{
		MN_OBJECTID id = pEntity->GetChildByIndex(i);
		BaseObject* pObject = GetObjectMgr()->find(id);
		if (NULL == pObject)
		 	continue;
		 
		if (!pObject->IsInstanceOf("Entity"))
		 	continue;
		 
		Item* pChildEntity = (Item*)pObject;
		visitEntities(pChildEntity);
	}
}