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


class CThread
{
private:
	typedef void (__cdecl* THREAD_FUNC)(void*);
public:
	CThread(THREAD_FUNC func, void* context)
	{
		m_threadFunc = func;
        m_hThread = (HANDLE)_beginthread(func, 0, context);
	}
	
	~CThread()
    {
        if (m_hThread != NULL)
        {
            WaitThreadExit(m_hThread);
            m_hThread = NULL;
        }
    }
private:
	bool WaitThreadExit(HANDLE handle)
	{
		DWORD res = WaitForSingleObject(handle, 1000);
		if (res == WAIT_OBJECT_0)
		{
			return true;
		}
		else if (res == WAIT_TIMEOUT)
		{
            TerminateThread(handle, 1);
		}
		return true;
	}

private:
	THREAD_FUNC m_threadFunc;
	HANDLE m_hThread;
};


class CThreadWaiter
{
public:
	CThreadWaiter()
	{
		m_hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	}

	~CThreadWaiter()
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

