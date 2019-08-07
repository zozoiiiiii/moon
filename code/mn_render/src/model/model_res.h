/************************************************************************/
/* 
@author:  junliang
@brief:   
@time:    2017/7/14
*/
/************************************************************************/
#pragma once

#include "mn_render/inc/model/i_model_res.h"
#include "mn_render/inc/i_render.h"
class ModelRes : public IModelRes
{
public:
    static ModelRes* Instance();
    void SetRender(IRender* pRender){m_pRender = pRender;}
    virtual MN::IMesh* CreateMesh();
	virtual MN::IMesh* LoadMeshFile(const std::string& path, const std::string& file);
	virtual MN::Skeleton* LoadSkelFile(const std::string& file);
	virtual MN::IAnim* LoadAnimFile(MN::Skeleton* skel, const std::string& file);

    std::string GetResPath(){return m_pRender->GetResPath();}
private:
    IRender* m_pRender;
};