/************************************************************************/
/*
@author:   [junliang]
@time:     [7/19/2019]
@desc:     
*/
/************************************************************************/
#pragma once

#include "mn_ui/inc/Core/i_window.h"

class MNWindow : public IWindow
{
public:
    virtual void OnCreate();
    virtual void OnDestroy();
    virtual bool create(const char* name, int x, int y, int width, int height)=0;
    virtual void show()=0;
    virtual void close()=0;






    CWindowWnd();

    HWND GetHWND() const;

    bool RegisterWindowClass();

    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
    void ShowWindow(bool bShow = true, bool bTakeFocus = true);
    UINT ShowModal();
    void Close(UINT nRet = IDOK);
    void CenterWindow();
    void SetIcon(UINT nRes);
    void ResizeClient(int cx = -1, int cy = -1);

protected:
    static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    HWND m_hWnd;
};
