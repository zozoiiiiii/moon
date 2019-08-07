/************************************************************************/
/*
@authro:    junliang
@brief:     main
@time:      20140404
*/
/************************************************************************/
#include "render.h"
#include "res/framebuffer.h"
#include "res/renderbuffer.h"
#include "res/texture.h"
#include "res/shader.h"
#include "res/res_mgr.h"
#include "batch/batch_group.h"
#include "public/object/mn_reflection.h"
//#include "render_system.h"

// dll export api
#ifdef _WIN32
extern"C" __declspec(dllexport) void dll_main(MN::ObjectMgr* pEntMgr);
#elif __ANDROID__
//extern"C"  void dll_main(MN::ObjectMgr* pEntMgr);
#elif __APPLE__
#endif

//void plugin_main_render(MN::ObjectMgr* pEntMgr)
extern"C" __declspec(dllexport) void dll_main(MN::ObjectMgr* pEntMgr)
{
	ReflectionMgr* pReflectionMgr = pEntMgr->getReflectionMgr();
	MN_REG(pReflectionMgr, BaseObject);
	MN_REG(pReflectionMgr, Entity);
	MN_REG(pReflectionMgr, Component);
	MN_REG(pReflectionMgr, RenderComponent);

	MN_REG(pReflectionMgr, Render);
	MN_REG(pReflectionMgr, IRes);
	MN_REG(pReflectionMgr, IFrameBuffer);
	MN_REG(pReflectionMgr, IRenderBuffer);
	MN_REG(pReflectionMgr, ITexture);
	MN_REG(pReflectionMgr, IStaticTexture);
	MN_REG(pReflectionMgr, IDynamicTexture);
	MN_REG(pReflectionMgr, IShader);
    MN_REG(pReflectionMgr, IRenderTexture);
	MN_REG(pReflectionMgr, IFontTexture);
	MN_REG(pReflectionMgr, FontTexture);

    MN_REG(pReflectionMgr, FrameBuffer);
    MN_REG(pReflectionMgr, ColorRenderBuffer);
    MN_REG(pReflectionMgr, DepthRenderBuffer);
    MN_REG(pReflectionMgr, StencilRenderBuffer);
    MN_REG(pReflectionMgr, DepthStencilRenderBuffer);
    MN_REG(pReflectionMgr, StaticTexture);
    MN_REG(pReflectionMgr, DynamicTexture);
    MN_REG(pReflectionMgr, ColorTexture);
    MN_REG(pReflectionMgr, DepthTexture);
    MN_REG(pReflectionMgr, Shader);
    MN_REG(pReflectionMgr, BatchGroup);
	MN_REG(pReflectionMgr, ResMgr);

	MN_REG(pReflectionMgr, Vec3f);
	//MN_REG(RenderSystem);

	//pEntMgr->Create("RenderSystem");
}
