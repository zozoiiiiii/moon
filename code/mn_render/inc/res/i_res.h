/************************************************************************/
/* 
@author:  junliang
@brief:   resource file
@time:    2017/10/21
*/
/************************************************************************/
#pragma once


#include "public/object/mn_object.h"
#include "i_res_mgr.h"

class IRender;
class IRes : public MN::BaseObject
{
	MN_VIRTUAL_BEGIN(IRes, BaseObject);
	MN_END
public:
    IResMgr* GetResMgr(){return m_pResMgr;}
    IRender* GetRender(){return m_pResMgr->GetRender();}
private:
    void SetResMgr(IResMgr* pResMgr){m_pResMgr = pResMgr;}
private:
    friend class ResMgr;
    IResMgr* m_pResMgr;
};
