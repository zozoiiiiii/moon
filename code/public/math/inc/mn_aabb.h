/************************************************************************/
/* 
@author:    junliang
@brief:     aabb

@help: tangziwen CubeEngine AABB
@time:      2017-8-23
*/
/************************************************************************/
#pragma once

#include "mn_vec3f.h"
#include "mn_mat4f.h"
#include <vector>
#include "public/math/inc/mn_math.h"
NS_MN_BEGIN

class AABB
{
public:
    AABB();
    ~AABB();
    void update(Vec3f *vec, int num);
    void update(Vec3f vec);
    void transForm(Mat4f mat);
    void reset();
    void merge(AABB box);
    Vec3f Min() const;
    void setMin(const Vec3f &min);

    Vec3f Max() const;

    Vec3f centre();

    std::vector<AABB> split8();
    bool isInside(Vec3f p) const;
    void setMax(const Vec3f &max);

    // °üº¬
    bool isCanCotain(AABB aabb);

    // Ïà½»
    bool isIntersect(AABB aabb, Vec3f &overLap);
private:
    Vec3f m_min;
    Vec3f m_max;
};
NS_MN_END
