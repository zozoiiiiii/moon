/************************************************************************/
/* 
@author:    junliang
@brief:     Mesh
@time:      6/23/2016
*/
/************************************************************************/
#pragma once

#include "mn_render/inc/model/i_mesh.h"

NS_MN_BEGIN

void InitVertex(Vertex* pVertex);
void InitVertex(Vertex* pVertex, float x_, float y_, float z_,float u_, float v_);

void SubMeshDraw(SubMesh* pSM, int nTexID, IShader* tri_Shader);
void SubMeshSetup(SubMesh* pSM);


// 当前模型的网格
class Mesh : public IMesh
{
public:
    Mesh();
    ~Mesh(){}
    void Load(const std::string& path, const std::string& file);
    void draw(IShader* tri_Shader);

    void AddSubMesh(const SubMesh& sm)
    {
        m_subMeshes.push_back(sm);
        subMesh_setup();
    }

    SubMesh* GetSubMesh(int nIndex)
    {
        if(nIndex<0||nIndex > m_subMeshes.size())
            return NULL;

        return &m_subMeshes[nIndex];
    }

    void CalNormalLines(SubMesh* pSM);


    virtual AABB GetAABB();
    void SetAABB(const AABB &aabb);
    void CalculateAABB();

private:
    bool LoadFromFile(const std::string& file);
    void subMesh_setup();
private:
    std::string m_path;
    std::vector<SubMesh> m_subMeshes;
    AABB m_aabb;


    //YY_PROP_GET_SET(bool, DiffuseMap);        // 漫反射贴图
    //YY_PROP_GET_SET(bool, NormalMap);        // 法线贴图
    //YY_PROP_GET_SET(bool, GlossMap);        // 光泽贴图
    //YY_PROP_GET_SET(bool, WireFrame);        // 不显示贴图，只显示mesh网格线
    //YY_PROP_GET_SET(bool, DrawNormal);        // 是否显示法线
    //YY_PROP_GET_SET(bool, DrawSkeleton);    // 是否显示骨骼
    //YY_PROP_GET_SET(bool, DrawBounding);    // 是否显示包围盒
};


NS_MN_END