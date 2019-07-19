// App.cpp : Defines the entry point for the application.
//

#include <exdisp.h>
#include <comdef.h>


#include "ControlEx.h"

class CGameFrameWnd : public CWindowWnd, public INotifyUI, public IListCallbackUI
{
public:
    CGameFrameWnd();
    LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const;
    void OnFinalMessage(HWND /*hWnd*/);

    void Init();
    void OnPrepare();
    void SendChatMessage();
    void Notify(TNotifyUI& msg);
    LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    // HandleMessage
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pCloseBtn;
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    //...
};