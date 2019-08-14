/************************************************************************/
/*
@author:   [junliang]
@time:     [8/9/2019]
@desc:     thread implement in windows
*/
/************************************************************************/
#pragma once

#include <windows.h>
#include <process.h>


class MNThread
{
private:
	typedef void (__cdecl* THREAD_FUNC)(void*);
public:
	MNThread(THREAD_FUNC func, void* context)
	{
		m_threadFunc = func;
        m_hThread = (HANDLE)_beginthread(func, 0, context);
	}
	
	~MNThread()
    {
        if (m_hThread != NULL)
        {
            DWORD res = WaitForSingleObject(m_hThread, 1000);
            if (res == WAIT_TIMEOUT)
            {
                TerminateThread(m_hThread, 1);
            }
        }
    }
private:
	THREAD_FUNC m_threadFunc;
	HANDLE m_hThread;
};


class MNThreadWaiter
{
public:
	MNThreadWaiter()
	{
		m_hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	}

	~MNThreadWaiter()
	{
		CloseHandle(m_hEvent);
	}
	
	bool Wait(int ms)
	{
		if (ms < 0)
		{
            // INFINITE
			WaitForSingleObject(m_hEvent, INFINITE);
		}
		else
		{
			DWORD res = WaitForSingleObject(m_hEvent, ms);
			if (WAIT_TIMEOUT == res)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Signal()
	{
		return SetEvent(m_hEvent) == TRUE;
	}
	
private:
	HANDLE m_hEvent;
};

