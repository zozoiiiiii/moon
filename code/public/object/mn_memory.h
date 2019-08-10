/************************************************************************/
/*
@auhtor:  junliang
@brief:   memory allocate, 

û��ʵ���ڴ��, ����Ϊ�ڴ���Ƭû���������ô����, ���ҷ�ֹ�ڴ�й¶��һ������Ա��������.
����������ڴ濪�ٺͻ����ڴ�ͳһ������Ϊ�˷���׷�ٺ��Ż���

ʹ��: 

    c��ʽ��
    char* buf=MPAlloc(10);
    MPFree(buf)

    c++��ʽ, ����smallObject�ķ�ʽ:
    class Test:public NewAlloc
    {
    public:
        void func()
        {
            char* buf=new buf[10];
            delete buf;
        }
    }


    //���Զ��ͷŵ�һ���ڴ���
    AutoMem<char, 512> strBuf(len);

�Ż�: tcmalloc

@time:    20130510
*/
/************************************************************************/
#pragma once

#include <stdlib.h>
#include "platform/mn_platform.h"

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