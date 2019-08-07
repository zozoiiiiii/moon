/************************************************************************/
/*
@author:  junliang
@brief:   just like sprite
@time:    2018/09/28
*/
/************************************************************************/
#pragma once

#include "MN_render/inc/i_batch.h"
#include "MN_render/inc/i_render.h"
#include "item.h"

//NS_MN_BEGIN
class ITexture;
class ImageComponent : public ItemComponent
{
    MN_BEGIN(ImageComponent, ItemComponent);
    MN_END


public:
	ImageComponent();
	virtual void OnEvent(const std::string& event, const MN::VarList& args = MN::VarList());
	virtual void OnAddBatch(IBatchGroup* pBatchGroup);
	virtual void OnRender(IRender* pRender, RenderContext* pCxt);

	void SetImageSource(const std::string& url);
private:
	void Setup();
private:
	struct Vertex
	{
		MN::Vec3f pos;
		MN::Vec2f tex_coords;
	};

	Vertex m_vertices[4];
	unsigned int m_VBO, m_EBO;
	ITexture* m_pTexture;
};
//NS_MN_END