/************************************************************************/
/*
@author:  junliang
@brief:   

use freetype library: https://learnopengl-cn.github.io/06%20In%20Practice/02%20Text%20Rendering/

@time:    2018/09/28
*/
/************************************************************************/
#pragma once

#include "MN_render/inc/i_batch.h"
#include "MN_render/inc/i_render.h"
#include "font/font_manager.h"
#include "font/font.h"
#include "MN_render/inc/model/i_mesh.h"
#include "item.h"

//NS_MN_BEGIN
class TextComponent : public ItemComponent
{
    MN_BEGIN(TextComponent, ItemComponent);
    MN_END


public:
	TextComponent();
	virtual void OnEvent(const std::string& event, const MN::VarList& args = MN::VarList());
	virtual void OnAddBatch(IBatchGroup* pBatchGroup);
	virtual void OnRender(IRender* pRender, RenderContext* pCxt);

	void SetText(const std::string& str) { m_string = str; }
private:
	void genMesh();
	void initAtlas();

private:
	MN::Font* m_pFont;
	GlyphAtlas * m_atlas;
	std::string m_string;
	int m_nMaxY;	// freetype use cartesian coordinate, here use lcd coordinate. so total string's origin is in topleft

	struct Vertex
	{
		MN::Vec3f pos;
		MN::Vec2f tex_coords;
	};

	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
	unsigned int m_VBO, m_EBO;
};

//NS_MN_END
