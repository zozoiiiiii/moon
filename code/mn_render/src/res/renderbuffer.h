/************************************************************************/
/* 
@author:    junliang
@brief:     render target(rt)
ÿ��rt��Ӧһ��frame buffer��
�������rt, ��ʵ��һ����ͨ������һ���������ͼ����������Ĭ�ϵ�֡���弴��Ļ��
��������ȹ�ϵ���޷���ʾ��ȷ������һ����ͨ�������Ⱦ��rt1�ϣ�Ȼ����Ⱦ����Ļ��
�����������Ⱦ��rt2�ϣ�Ȼ����Ⱦ����Ļ������������������Ȼ���Ӱ�죬rt2��ʾ��rt1�ϡ�


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