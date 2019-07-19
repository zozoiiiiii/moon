/************************************************************************/
/* 
@author:    junliang
@brief:     event manager
@time:      2017-5-18
*/
/************************************************************************/
#pragma once


#include "mn_object.h"
#include "FastDelegate.h"

typedef fastdelegate::FastDelegate2<const char*, const MN::VarList&, void> EventDelegate;

NS_MN_BEGIN
typedef std::map<std::string, std::vector<EventDelegate> > MAP_EVENT;
typedef std::map<MN_OBJECTID, MAP_EVENT> MAP_SENDER;

class EventMgr
{
    MN_BEGIN(EventMgr, BaseObject);
    MN_END
public:
    typedef std::map<std::string, std::vector<EventDelegate> > MAP_EVENT;
    typedef std::map<MN_OBJECTID, MAP_EVENT> MAP_SENDER;

    virtual int Invoke(MN_OBJECTID sender, const char* eventname, const VarList& arg=VarList());

    virtual void Connect(MN_OBJECTID sender, const char* eventname, EventDelegate cb_fun);
	virtual void Disconnect(MN_OBJECTID sender, const char* eventname, EventDelegate cb_fun);
	virtual void Disconnect(MN_OBJECTID sender);

    virtual void ConnectGlobals(EventDelegate recv_callback);
    virtual void DisconnectGlobals(EventDelegate recv_callback);

    virtual void ConnectGlobals(const char* eventname, EventDelegate recv_callback);
    virtual void DisconnectGlobals(const char* eventname, EventDelegate recv_callback);

private:
    inline void Invoke(std::vector<EventDelegate>& delegates,  const char* name, const VarList& arg)
    {
        size_t cnt = delegates.size();
        for(size_t i = 0; i < cnt; i++)
        {
            delegates[i](name, arg);
        }
    }

private:
    MAP_EVENT m_globals;
    MAP_SENDER m_senders;
};

NS_MN_END