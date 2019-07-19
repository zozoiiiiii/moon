/************************************************************************/
/*
@author:   [junliang]
@time:     [7/19/2019]
@desc:     
*/
/************************************************************************/
#pragma once
#include "mn_input/inc/i_input_module.h"
#include "public/object/mn_event_mgr.h"

class WinInputModule : public IInputModule
{
    MN_BEGIN(WinInputModule, IInputModule);
    MN_END
public:
    virtual void OnCreate();
    virtual void OnDestroy();
    bool MsgProc(unsigned int msg, size_t param1, size_t param2, int& result);
private:
    IInputModule* m_pInputModule;
    MN::EventMgr* m_pEventMgr;
};