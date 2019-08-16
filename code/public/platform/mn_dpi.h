/************************************************************************/
/*
@author:  junliang
@time:    20190810
@brief:   windows DPI, application should consider if run in 4k monitor
https://zhuanlan.zhihu.com/p/77930304

shellscalingapi.h is not suppport in the winsdk6 which used by vs2008, so here has to use 
*/
/************************************************************************/
#pragma once

#include "mn_platform.h"

#ifdef _MN_PLATFORM_WIN32_


// Windows Header Files:
#include <windows.h>
#include <windowsx.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Specific header required by the program
//#include <shellscalingapi.h>

typedef enum PROCESS_DPI_AWARENESS {
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

class CDPI
{
public:
    CDPI()
    {
        m_nScaleFactor = 0;
        m_nScaleFactorSDA = 0;
        m_Awareness = PROCESS_DPI_UNAWARE;
    }

    int  Scale(int x)
    {
        // DPI Unaware:  Return the input value with no scaling.
        // These apps are always virtualized to 96 DPI and scaled by the system for the DPI of the monitor where shown.
        if (m_Awareness == PROCESS_DPI_UNAWARE)
        {
            return x;
        }

        // System DPI Aware:  Return the input value scaled by the factor determined by the system DPI when the app was launched.
        // These apps render themselves according to the DPI of the display where they are launched, and they expect that scaling
        // to remain constant for all displays on the system.
        // These apps are scaled up or down when moved to a display with a different DPI from the system DPI.
        if (m_Awareness == PROCESS_SYSTEM_DPI_AWARE)
        {
            return MulDiv(x, m_nScaleFactorSDA, 100);
        }

        // Per-Monitor DPI Aware:  Return the input value scaled by the factor for the display which contains most of the window.
        // These apps render themselves for any DPI, and re-render when the DPI changes (as indicated by the WM_DPICHANGED window message).
        return MulDiv(x, m_nScaleFactor, 100);
    }

    UINT GetScale()
    {
        if (m_Awareness == PROCESS_DPI_UNAWARE)
        {
            return 100;
        }

        if (m_Awareness == PROCESS_SYSTEM_DPI_AWARE)
        {
            return m_nScaleFactorSDA;
        }

        return m_nScaleFactor;
    }

    void SetScale(__in UINT iDPI)
    {
        m_nScaleFactor = MulDiv(iDPI, 100, 96);
        if (m_nScaleFactorSDA == 0)
        {
            m_nScaleFactorSDA = m_nScaleFactor;  // Save the first scale factor, which is all that SDA apps know about
        }
        return;
    }

    PROCESS_DPI_AWARENESS GetAwareness()
    {
        HANDLE hProcess;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId());
       // GetProcessDpiAwareness(hProcess, &m_Awareness);
        return m_Awareness;
    }

    void SetAwareness(PROCESS_DPI_AWARENESS awareness)
    {
        HRESULT hr = E_FAIL;
       // hr = SetProcessDpiAwareness(awareness);
        if (hr == S_OK)
        {
            m_Awareness = awareness;
        }
        else
        {
            MessageBox(NULL, (LPCWSTR) L"SetProcessDpiAwareness Error", (LPCWSTR) L"Error", MB_OK);
        }
        return;
    }

    // Scale rectangle from raw pixels to relative pixels.
    void ScaleRect(__inout RECT *pRect)
    {
        pRect->left = Scale(pRect->left);
        pRect->right = Scale(pRect->right);
        pRect->top = Scale(pRect->top);
        pRect->bottom = Scale(pRect->bottom);
    }

    // Scale Point from raw pixels to relative pixels.
    void ScalePoint(__inout POINT *pPoint)
    {
        pPoint->x = Scale(pPoint->x);
        pPoint->y = Scale(pPoint->y);
    }

private:
    UINT m_nScaleFactor;
    UINT m_nScaleFactorSDA;
    PROCESS_DPI_AWARENESS m_Awareness;
};
#endif