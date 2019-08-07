/************************************************************************/
/* 
@author:    junliang
@brief:      �ο�Skeletonanimation�� glsl.h

Ϊ��Ҫ�õ�mrt������Ⱦ:
ͬʱ���һ������Ĳ�ͬ����Ч��



unityshader: pass
һ��shader��Ӧһ��Ч���� �������һ��render texture�ڲ�ͬʱ����Ⱦ��ͬ��Ч����
�ͱ���Ҫ2��shader.
����: unity3d��һ��shader�����ж��pass, �ֱ��Ӧ��ͬ����ȾЧ����


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
