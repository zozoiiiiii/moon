/************************************************************************/
/* 
@author:    junliang
@brief:     Skeleton
@time:      6/23/2016
*/
/************************************************************************/
#pragma once

#include "mn_render/inc/model/i_skeleton.h"
NS_MN_BEGIN

void InitBone(Bone* pBone);
void LoadSkeleton(Skeleton* pSkeleton, const std::string& file);

NS_MN_END