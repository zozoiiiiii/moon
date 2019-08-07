/************************************************************************/
/*
@author:  junliang
@brief:   ui framework

2d: form
3d: scene


entity------transform
	  ------sprite
      ------label
	  ------text

buttom control= entity(transform,sprint,button)
                    entity(transform,label)


@time:    2018/09/28
*/
/************************************************************************/

//#include "MN_core.h"
#include "gui.h"
#include "item.h"
#include "rectangle_component.h"
#include "text_component.h"
#include "image_component.h"
//#include "positioner/column_component.h"
//#include "positioner/row_component.h"


//#include "views/scroll_bar.h"
//#include "views/scroll_view.h"
//#include "views/scroll_view_delegate.h"
//#include "views/scroll_view_model.h"
//#include "views/tree_view_model.h"
//#include "views/tree_view.h"
//#include "button.h"
//#include "mouse_area.h"

//#include "item_generator_component.h"
//#include "anchor_fill_component.h"
//#include "text.h"


extern"C" __declspec(dllexport) void dll_main(MN::ObjectMgr* pEntMgr)
{
	ReflectionMgr* pReflectionMgr = pEntMgr->getReflectionMgr();
	MN_REG(pReflectionMgr, IGUI);
	MN_REG(pReflectionMgr, GUI);
	MN_REG(pReflectionMgr, Item);
	MN_REG(pReflectionMgr, ItemComponent);
	MN_REG(pReflectionMgr, RectangleComponent);

	//MN_REG(ColumnComponent);
	//MN_REG(RowComponent);

	MN_REG(pReflectionMgr, ImageComponent);
	MN_REG(pReflectionMgr, TextComponent);

//	MN_REG(ItemGeneratorComponent);
//	MN_REG(AnchorFillComponent);

	//MN_REG(Button);
	//MN_REG(MouseArea);
	//MN_REG(ScrollBar);
	//MN_REG(ScrollView);
	//MN_REG(ScrollViewDelegate);
	//MN_REG(ScrollViewModel);
	//MN_REG(TreeViewModel);
	//MN_REG(TreeView);

}
