/************************************************************************/
/*
@author:  junliang
@brief:   
@time:    2018/09/28
*/
/************************************************************************/
#pragma once
#include "MN_ui/inc/i_gui.h"
#include "MN_render/inc/i_render.h"
#include "MN_render/inc/i_batch.h"
#include "MN_render/inc/i_render_context.h"
#include "item.h"

NS_MN_BEGIN
class GUI : public IGUI
{
    MN_BEGIN(GUI, IGUI);
    MN_END
public:
	virtual void open();
	virtual void close();
	virtual void ReSize(float w, float h);


	MN_OBJECTID GetDesktopForm() const;
	void AddModalForm(MN_OBJECTID control);
	void RemoveModalForm(MN_OBJECTID control);
	virtual IRender* GetRender() { return m_pRender; }

private:
	void onEvent_AddBatch(const char* name, const MN::VarList& args);
	void visitEntities(Item* pEntity);
private:
	IRender* m_pRender;
	IBatchGroup* m_pUIBatchGroup;
	RenderContext* m_pRenderContext;
	Item* m_pDeskTop;	// canvas node
	std::vector<MN_OBJECTID> m_modalForms; // pop up form
};
NS_MN_END