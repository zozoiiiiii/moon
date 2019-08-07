/************************************************************************/
/*
@author:  junliang
@brief:   
@time:    2018/09/28
*/
/************************************************************************/
#pragma once

#include "public/ecs/mn_entity.h"
#include "MN_render/inc/i_batch.h"


// texture offset
//#define SETTEXX(x) ((float(x) - 0.5f)) 
//#define SETTEXY(y) (-(float(y) -0.5f))

// point offset, normally, (0,0) is in the right,left, so need to change to top,left
//#define SETX(x)	((x-0.5f))
//#define SETY(y)	(-(y-0.5f))


//#define COLOR_ARGB(a, r, g, b) ((unsigned int)((((a) & 0xFF)<<24) \
//	| (((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF)))

//#define COLOR_RGBA(r, g, b, a) COLOR_ARGB(a, r, g, b)

// color: a r g b
#define COLOR_RED 0xFFFF0000
#define COLOR_GREE 0xFF00FF00
#define COLOR_BLUE 0xFF0000FF
#define COLOR_EDITOR 0xFF535353
#define COLOR_TREEITEM_HIGHLIGHT 0xFF3A3A3A

//NS_MN_BEGIN
class Item;
class ItemComponent : public RenderComponent
{
	MN_BEGIN(ItemComponent, RenderComponent);
    MN_FIELD(&ItemComponent::m_test, "test", "");
	MN_END
public:
	Item* FindItem();
private:
	int m_test;
};

class Item : public MN::Entity
{
	MN_BEGIN(Item, Entity);
	MN_FIELD(&Item::m_top, "top", "");
	MN_FIELD(&Item::m_left, "left", "");
	MN_FIELD(&Item::m_width, "width", "");
    MN_FIELD(&Item::m_height, "height", "");
    MN_FIELD(&Item::m_visible, "visible", "");
	MN_END
public:
	Item();
	virtual void OnCreate();
	virtual void OnDestroyed();


	void SetLeft(float left);
	void SetAbsLeft(float left);
	float GetLeft();
	float GetAbsLeft();

	void SetTop(float top);
	void SetAbsTop(float top);
	float GetTop();
	float GetAbsTop();
	Item* FindParentTransform();


	float GetWidth();
	void SetWidth(float w);

	float GetHeight();
	void SetHeight(float h);

	int GetOpacity();
	void SetOpacity(int opacity);
	bool GetVisible();
	void SetVisible(bool visible);

	void SetTransformChanged(bool bChanged=true);
	bool IsTransformChanged() { return m_bTransformChanged; }
private:
	void Show();
	void Close();
	void ShowModal();
	void CloseModal();
private:
	float m_top;
	float m_left;
	float m_width;
	float m_height;
	int m_opacity;
	bool m_visible;
	bool m_bTransformChanged;
	MN::Vec3f m_pos;
};

//NS_MN_END


using namespace MN;
MN_TYPEHELPER(ItemComponent, MNVT_CLASS);