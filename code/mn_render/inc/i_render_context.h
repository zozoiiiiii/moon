/************************************************************************/
/* 
@author:    junliang
@brief:     render context, ÀàËÆopenglµÄ×´Ì¬»ú
@time:      11/28/2016
*/
/************************************************************************/
#pragma once

//#include "mn_core.h"
//#include "i_transform.h"
#include "mn_render/inc/res/i_shader.h"
#include "mn_render/inc/res/i_framebuffer.h"
#include "public/math/inc/mn_mat4f.h"


enum RenderType
{
    RT_Normal,      // normal render
    RT_Shadow,      // shader render
    RT_Reflect,     // reflect on water.
};


struct RenderContext
{
    MN::Mat4f viewMatrix;
    MN::Mat4f projMatrix;
    IShader* pShader_ShadowMap;
    int nRenderType;

    // viewport
    //int x,y,w,h;

    IFrameBuffer* pFBO;
    IRenderTexture* pRenderTexture;
    IRenderBuffer* pDepthRenderBuffer;

    // light
    // ambient
    MN::Vec3f ambient_color;
    float ambient_intensity;

    // direction light
    MN::Vec3f directionLight_color;
    float directionLight_intensity;
    MN::Vec3f directionLight_direction;
};