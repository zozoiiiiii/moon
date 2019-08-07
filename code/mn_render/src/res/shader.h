/************************************************************************/
/* 
@author:    junliang
@brief:      参考Skeletonanimation的 glsl.h

为何要用到mrt多重渲染:
同时获得一个画面的不同后期效果



unityshader: pass
一个shader对应一种效果； 如果想让一个render texture在不同时刻渲染不同的效果，
就必须要2个shader.
综上: unity3d中一个shader可以有多个pass, 分别对应不同的渲染效果。


@time:      2017-10-27
*/
/************************************************************************/
#pragma once

#include <vector>
#include "mn_render/inc/res/i_Shader.h"

class Shader : public IShader
{
    MN_BEGIN(Shader, IShader);
    MN_END
public:
    Shader();
    virtual bool Load(const char* vsh, const char* fsh);
    bool SetUniform1i(char* Varname, int v0);
    bool SetUniform1f(char* Varname, float v0);
    bool SetUniform2f(char* Varname, float v0, float v1);
    bool SetUniform3f(char* Varname, float v0, float v1, float v2);
    bool SetUniform4f(char* Varname, float v0, float v1, float v2, float v3);
    bool SetUniformMat4fv(char* Varname, int count ,float* val);
    bool Begin(void);
    bool End(void);
    int GetLoc(char* Varname);

    unsigned int GetProgramHandle(){return m_program_handle;}
private:
    bool Attach(int type,const char* filename);
    bool Link();
private:
    std::vector<unsigned int> m_handles;
    unsigned int m_program_handle;
};
