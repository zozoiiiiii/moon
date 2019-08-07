/************************************************************************/
/* 
@author:    junliang
@brief:     Skeleton
@time:      6/23/2016
*/
/************************************************************************/
#pragma once

#include "i_mesh.h"
NS_MN_BEGIN

// 骨骼节点
struct Bone
{
    std::string name;
    int parent;
    std::vector<int> children;

    Vec3f pos;
    float angle,ax,ay,az;
    Vec3f scale;

    Mat4f inverseBindPose;            // 骨骼偏移矩阵, 让顶点位置从模型空间转换到骨骼空间
    Mat4f matrix;                    // 临时使用
};

struct Skeleton
{
    std::vector<Bone> bones;    // 后期可新增一个vector存放所有rootbone来优化
};

NS_MN_END