/************************************************************************/
/* 
@author:    junliang
@brief:     shader
@time:      2017-6-16
*/
/************************************************************************/
#pragma once

#include <vector>
#include "i_res.h"

class IShader : public IRes
{
	MN_VIRTUAL_BEGIN(IShader, IRes);
	MN_END
public:
    virtual bool Load(const char* vsh, const char* fsh) = 0;
    virtual bool SetUniform1i(char* Varname, int v0) = 0;
    virtual bool SetUniform1f(char* Varname, float v0) = 0;
    virtual bool SetUniform2f(char* Varname, float v0, float v1) = 0;
    virtual bool SetUniform3f(char* Varname, float v0, float v1, float v2) = 0;
    virtual bool SetUniform4f(char* Varname, float v0, float v1, float v2, float v3) = 0;
    virtual bool SetUniformMat4fv(char* Varname, int count ,float* val) = 0;
    virtual bool Begin(void) = 0;
    virtual bool End(void) = 0;
    virtual int GetLoc(char* Varname) = 0;

    virtual unsigned int GetProgramHandle() = 0;
};
