/************************************************************************/
/* 
@author:    junliang
@brief:     ray
@time:      2017-8-23
*/
/************************************************************************/
#pragma once

#include "mn_plane.h"
#include "mn_aabb.h"

enum RayAABBSide{
    up =0,
    down,
    left,
    right,
    front,
    back,
};

NS_MN_BEGIN

class Ray
{
public:
    Ray();
    Ray(Vec3f origin,Vec3f direction);
    ~Ray();
    Vec3f origin() const;
    void setOrigin(const Vec3f &origin);
    Vec3f direction() const;
    void setDirection(const Vec3f &direction);
    Vec3f intersectPlane(Plane p);
    bool intersectAABB(AABB  aabb, RayAABBSide * side,Vec3f &hitPoint) const;
    bool intersectTriangle(const Vec3f & v1, const Vec3f & v2, const Vec3f & v3, float * out = NULL) const;
private:
    Vec3f m_origin;
    Vec3f m_direction;
};

NS_MN_END

