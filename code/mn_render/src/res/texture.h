/************************************************************************/
/* 
@author:    junliang
@brief:     texture
@time:      2017-9-21
*/
/************************************************************************/
#pragma once

//#include "mn_core.h"
#include "mn_render/inc/res/i_texture.h"

class StaticTexture : public IStaticTexture
{
    MN_BEGIN(StaticTexture, IStaticTexture);
    MN_END
public:
    virtual void Generate(int w, int h, int n, const void* pData);
};

class DynamicTexture : public IDynamicTexture
{
    MN_BEGIN(DynamicTexture, IDynamicTexture);
    MN_END
public:
    virtual void Generate(int w, int h, int n, const void* pData){}
};

class ColorTexture : public IRenderTexture
{
    MN_BEGIN(ColorTexture, IRenderTexture);
    MN_END
public:
    virtual void Generate();
};



class DepthTexture : public IRenderTexture
{
    MN_BEGIN(DepthTexture, IRenderTexture);
    MN_END
public:
    virtual void Generate();
};


class FontTexture : public IFontTexture
{
	MN_BEGIN(FontTexture, IFontTexture);
	MN_END
public:
	virtual void Generate(int w, int h, int n, const void* pData);
};
