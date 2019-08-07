/************************************************************************/
/* 
@author:    junliang
@brief:     render target(rt)
每个rt对应一个frame buffer。
如果不用rt, 想实现一个普通场景，一个摄像机视图场景，都用默认的帧缓冲即屏幕，
则由于深度关系，无法显示正确。必须一个普通摄像机渲染到rt1上，然后渲染到屏幕；
摄像机场景渲染到rt2上，然后渲染到屏幕。这样两个场景的深度互不影响，rt2显示在rt1上。


@time:      2017-9-21
*/
/************************************************************************/
#pragma once

//#include "mn_core.h"
#include "mn_render/inc/res/i_renderbuffer.h"


class ColorRenderBuffer : public IRenderBuffer
{
    MN_BEGIN(ColorRenderBuffer, IRenderBuffer);
    MN_END
public:
	virtual void Generate();
};

class DepthRenderBuffer : public IRenderBuffer
{
    MN_BEGIN(DepthRenderBuffer, IRenderBuffer);
    MN_END
public:
    virtual void Generate();
};

class StencilRenderBuffer : public IRenderBuffer
{
    MN_BEGIN(StencilRenderBuffer, IRenderBuffer);
    MN_END
public:
    virtual void Generate();
};

class DepthStencilRenderBuffer : public IRenderBuffer
{
    MN_BEGIN(DepthStencilRenderBuffer, IRenderBuffer);
    MN_END
public:
    virtual void Generate();
};