/************************************************************************/
/*
@author:  junliang
@brief:   
@time:    2018/09/28
*/
/************************************************************************/
#pragma once

#include "item.h"

NS_MN_BEGIN
class MouseArea: public Item
{
    MN_BEGIN(MouseArea, Item);
    MN_END
public:
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual bool OnMsg(uint32 msg_id, uint32 param1, uint32 param2);
private:
	void OnPressed(uint32 msg_id, uint32 param1, uint32 param2);
	void OnReleased(uint32 msg_id, uint32 param1, uint32 param2);
	bool isInside(int x, int y);
};

NS_MN_END