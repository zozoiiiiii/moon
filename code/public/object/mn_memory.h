/************************************************************************/
/*
@auhtor:  junliang
@brief:   memory allocate, 

没有实现内存池, 是因为内存碎片没有想象的那么严重, 而且防止内存泄露是一个程序员基本能力.
这里把所有内存开辟和回收在此统一处理，是为了方便追踪和优化。

使用: 

    c方式：
    char* buf=MPAlloc(10);
    MPFree(buf)

    c++方式, 采用smallObject的方式:
    class Test:public NewAlloc
    {
    public:
        void func()
        {
            char* buf=new buf[10];
            delete buf;
        }
    }


    //会自动释放的一块内存类
    AutoMem<char, 512> strBuf(len);

优化: tcmalloc

@time:    20130510
*/
/************************************************************************/
#pragma once

#include <stdlib.h>
#include "mn_type.h"

NS_MN_BEGIN

template<typename type, size_t size>
class AutoMem
{
public:
    AutoMem(size_t len){
		memset(m_stack, 0, size);
		if (len >= size)
		{
			m_pMem = new type[len+1];
			memset(m_pMem, 0, len+1);
		}
        else
            m_pMem = m_stack;

        m_len = (int)len;
    }

    ~AutoMem(){
        if (m_pMem != m_stack)
            delete[] m_pMem;
    }

    type* GetBuf(){
        return m_pMem;
    }

    int GetLen(){
        return m_len;
    }
private:
    AutoMem(){}
    AutoMem(const AutoMem&){}
    AutoMem& operator=(const AutoMem&){}

private:
    type m_stack[size];
    type* m_pMem;
    int m_len;
};

NS_MN_END