#include "model_res.h"
#include "mesh.h"
#include "anim.h"
#include "skeleton.h"
#include "mn_render/inc/i_render.h"


ModelRes* ModelRes::Instance()
{
    static ModelRes s_model_res;
    return &s_model_res;
}

MN::IMesh* ModelRes::CreateMesh()
{
    MN::Mesh* pMesh = new MN::Mesh;
    return pMesh;
}

MN::IMesh* ModelRes::LoadMeshFile(const std::string& path, const std::string& file)
{
	MN::Mesh* pMesh = new MN::Mesh;
	pMesh->Load(path, file);
	return pMesh;
}

MN::Skeleton* ModelRes::LoadSkelFile(const std::string& file)
{
	MN::Skeleton* pSkel = new MN::Skeleton;
	LoadSkeleton(pSkel, file);
	return pSkel;
}

MN::IAnim* ModelRes::LoadAnimFile(MN::Skeleton* skel, const std::string& file)
{
	MN::Anim* pAnim = new MN::Anim;
	pAnim->Load(skel, file);
	return pAnim;
}