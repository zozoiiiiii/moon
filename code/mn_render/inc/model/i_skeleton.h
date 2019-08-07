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

// �����ڵ�
struct Bone
{
    std::string name;
    int parent;
    std::vector<int> children;

    Vec3f pos;
    float angle,ax,ay,az;
    Vec3f scale;

    Mat4f inverseBindPose;            // ����ƫ�ƾ���, �ö���λ�ô�ģ�Ϳռ�ת���������ռ�
    Mat4f matrix;                    // ��ʱʹ��
};

struct Skeleton
{
    std::vector<Bone> bones;    // ���ڿ�����һ��vector�������rootbone���Ż�
};

NS_MN_END