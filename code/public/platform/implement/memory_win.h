/************************************************************************/
/*
@author:  junliang
@time:    20190810
@brief:
*/
/************************************************************************/
#pragma once

#include "../mn_platform.h"
#include <stdlib.h>


template<typename type, size_t size>
class AutoMNMem
{
public:
	AutoMNMem(size_t len)
	{
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

    ~AutoMNMem()
	{
        if (m_pMem != m_stack)
            delete[] m_pMem;
    }

    type* GetBuf(){return m_pMem;}
    int GetLen(){return m_len;}
private:
	// prevent this kind of use
	AutoMNMem(){}
	AutoMNMem(const AutoMNMem&){}
	AutoMNMem& operator=(const AutoMNMem&){}

private:
    type m_stack[size];
    type* m_pMem;
    int m_len;
};