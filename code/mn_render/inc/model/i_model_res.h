/************************************************************************/
/* 
@author:  junliang
@brief:   
@time:    2017/7/14
*/
/************************************************************************/
#pragma once

#include "i_mesh.h"
#include "i_anim.h"
#include "i_skeleton.h"

class IModelRes
{
public:
    virtual MN::IMesh* CreateMesh() = 0;
	virtual MN::IMesh* LoadMeshFile(const std::string& path, const std::string& file) = 0;
	virtual MN::Skeleton* LoadSkelFile(const std::string& file) = 0;
	virtual MN::IAnim* LoadAnimFile(MN::Skeleton* skel, const std::string& file) = 0;
};