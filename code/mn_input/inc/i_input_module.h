/************************************************************************/
/*
@author:   [junliang]
@time:     [7/19/2019]
@desc:     input module
*/
/************************************************************************/
#pragma once

#include "public/object/mn_object.h"

enum InputEventType
{
    IET_UNKNOWN = -1,

    IET_Mouse_RDown,
    IET_Mouse_RUp,
    IET_Mouse_LDown,
    IET_Mouse_LUp,
    IET_Mouse_Move,

    IET_KeyBoard_Down,
    IET_KeyBoard_Up,
};

#ifdef WIN32
class IInputModule : public MN::BaseObject
{
    MN_BEGIN(IInputModule, BaseObject);
    MN_END
public:
    virtual bool MsgProc(unsigned int msg, size_t param1, size_t param2, int& result){};
};
#endif