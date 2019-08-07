/************************************************************************/
/*
@author:  junliang
@brief:   
@time:    2018/10/25
*/
/************************************************************************/
#pragma once

#include "MN_render/inc/i_batch.h"
#include "MN_render/inc/i_render.h"
#include <vector>
#include "item.h"

//NS_MN_BEGIN
class RectangleComponent : public ItemComponent
{
	MN_BEGIN(RectangleComponent, ItemComponent);
    MN_METHOD(&RectangleComponent::SetColor, "SetColor", "");
	MN_END
public:
	RectangleComponent();
	virtual void OnEvent(const std::string& event, const MN::VarList& args = MN::VarList());
	virtual void OnAddBatch(IBatchGroup* pBatchGroup);
	virtual void OnRender(IRender* pRender, RenderContext* pCxt);
	void Setup();
	void SetColor(unsigned int color);
	unsigned int  GetColor();
private:
	sint32 m_color;	// unsigned int and signed int has same data, different rule. here use sint32 instead of unsigned int, as reflection module not support unsigned int.

	struct Vertex
	{
		MN::Vec3f pos;
		unsigned int color;	// 0xFF0000FF   : argb
	};

	Vertex m_vertices[4];
	unsigned int m_VBO, m_EBO;
};


//NS_MN_END