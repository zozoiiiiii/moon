/************************************************************************/
/*
@author:    junliang
@brief:     math utility func
@time:      20160323
*/
/************************************************************************/
#ifndef _yy_math_func_h_
#define _yy_math_func_h_

//#include "reflection/mn_type.h"
#include "mn_math.h"
#include <iostream>
#include "mn_Vec2f.h"
#include "mn_Mat4f.h"
#include "mn_vec3f.h"
NS_MN_BEGIN



void Swap(float &a,float &b) ;

// ���ߺ��������Ƿ��ཻ, ����true��ʾ�ཻ��dist��ʾ���ߵ������εľ���
int Intersecttri(
                 const Vec3f& v1,const Vec3f& v2,const Vec3f& v3,
                 const Vec3f& raypos,const Vec3f& raydir,
                 float& u,float& v,float& dist);


float Distance(float x1, float y1, float x2, float y2);
float Distance(float x1, float y1, float z1, float x2, float y2, float z2);

// ��-pi~pi�Ļ���ֵת��Ϊ0~2*pi�Ļ���ֵ
float NormalizeAngle(float angle);

// ������������ʸ���Ļ���ֵ(����0~2*pi��ֵ����z��������Ϊ0��)
float GetAngle(float x1, float z1, float x2, float z2);

// �Ƚ������������Ƿ����Ϊ���
bool FloatEqual(float f1, float f2);
bool FloatEqualZero(float f);

//���Ƿ��ڶ������
bool PointInRegion(Vec2f pt, Vec2f* plist, int num);
NS_MN_END
#endif