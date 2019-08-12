/************************************************************************/
/*
@author:   [junliang]
@time:     [8/9/2019]
@desc:     




int g_nCnt;
CThread* g_pThread;
CThreadWaiter* g_pThreadWaiter;
void ThreadFunc(void* lpParameter)
{
    for(;;)
    {
        int* nCnt = (int*)lpParameter;
        g_pThreadWaiter->Wait(100);
        static int tmp=100;
        tmp++;
        *nCnt = tmp;
        g_pThreadWaiter->Signal();
    }
}


int main()
{
    g_nCnt=9;
    g_pThreadWaiter = new CThreadWaiter();
    g_pThread = new CThread(&ThreadFunc, &g_nCnt);
    Sleep(5000);
    delete g_pThread;
	return 0;
}

*/
/************************************************************************/
#pragma once

#include "mn_platform.h"

#ifdef _MN_PLATFORM_WIN32_
    #include "implement/thread_win.h"
#elif defined(_MN_PLATFORM_UTIL_APPLE_)
    #include "implement/thread_ios.h"
#elif defined(_MN_PLATFORM_ANDROID_)
    #include "implement/thread_linux.h"
#endif