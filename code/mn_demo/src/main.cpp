
#include "main_view.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
#if 0
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
    CPaintManagerUI::SetResourceZip(_T("GameRes.zip"));
#else
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin/GameRes"));
#endif

    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;

    CGameFrameWnd* pFrame = new CGameFrameWnd();
    if( pFrame == NULL ) return 0;
	pFrame->SetIcon(IDI_ICON_DUILIB);
    pFrame->Create(NULL, _T("ÓÎÏ·ÖÐÐÄ"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1024, 738);
    pFrame->CenterWindow();
    ::ShowWindow(*pFrame, SW_SHOWMAXIMIZED);

    CPaintManagerUI::MessageLoop();

    ::CoUninitialize();
    return 0;
}
