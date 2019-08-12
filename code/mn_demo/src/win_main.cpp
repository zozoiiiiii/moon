/************************************************************************/
/*
@author:  junliang
@brief:   main
@time:    20180528
*/
/************************************************************************/

#include <iostream>
#include <windows.h>
#include "egl_device.h"
#include "public/util/time_util.h"
#include "public/util/file_util.h"
#include "public/object/mn_object_mgr.h"
#include "mn_render/inc/i_render.h"
#include "mn_ui/inc/i_gui.h"
#include "platform/mn_thread.h"

EGLDevice g_eglDevice;
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    //if (App::Instance()->IsOpened())
    {
        if (message == WM_SIZE)
        {
            g_eglDevice.ResetSurface();

            int fwSizeType = wParam; // resizing flag
            int nWidth = LOWORD(lParam); // width of client area
            int nHeight = HIWORD(lParam); // height of client area
            //App::Instance()->Resize(nWidth, nHeight);
        }

       // bool ret ;//= App::Instance()->OnMsg(message, (unsigned int)wParam, (unsigned int)lParam);
       // if (ret)
            //return 0;
    }

    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


void LoadDll(ObjectMgr* pObjectMgr, const char* dllName)
{
    std::string path = FileUtil::ExePath()  + "\\" + dllName+".dll";
    HMODULE hdll = ::LoadLibraryA(path.c_str());

    typedef void (*cb_Plugin)(MN::ObjectMgr*);
    cb_Plugin func = (cb_Plugin)::GetProcAddress(hdll, "dll_main" );
    if ( NULL == func )
    {
        FreeLibrary(hdll);
        return;
    }
    (*func)(pObjectMgr);
}

HWND CreateMyWindow(HINSTANCE hInstance, int width, int height, const std::string& title, WNDPROC func)
{
    WNDCLASSEX wndclass = {0}; 
    RECT     windowRect;
    //HINSTANCE hInstance = GetModuleHandle(NULL);

    wndclass.cbSize         = sizeof(WNDCLASSEX);
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;;
    wndclass.lpfnWndProc   = (WNDPROC)func; 
    wndclass.cbClsExtra        = 0;
    wndclass.cbWndExtra        = 0;
    wndclass.hInstance        = hInstance;
    wndclass.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground    = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName    = L"WINCLASS1";
    wndclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    if(RegisterClassEx (&wndclass) == 0)
        return NULL;


    // Adjust the window rectangle so that the client area has
    // the correct number of pixels
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = width;
    windowRect.bottom = height;

    DWORD wsStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION;
    AdjustWindowRect ( &windowRect, WS_SYSMENU | WS_CAPTION, FALSE );

    HWND hWnd = CreateWindowA("WINCLASS1",title.c_str(), wsStyle,0,0,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        hInstance,
        NULL);

    if(hWnd == NULL)
        return NULL;

    ShowWindow ( hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    return hWnd;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int iCmdShow)
{
    int width=1024;
    int height=768;
    HWND nHwnd = CreateMyWindow(hInstance, width,height, "hello", &WndProc);

    g_eglDevice.InitDevice(nHwnd);

    std::string exe_path = FileUtil::ExePath();
    std::string pre_exe_path = FileUtil::GetPrePath(exe_path);
    std::string res = pre_exe_path + "\\res\\";
    

    MN::ObjectMgr* pObjectMgr = new MN::ObjectMgr;
    LoadDll(pObjectMgr, "mn_render");
    LoadDll(pObjectMgr, "mn_ui");

    IRender* pRender = IRender::Instance(pObjectMgr);
    pRender->SetResPath(res);
    pRender->SetWinWidth(width);
    pRender->SetWinHeight(height);
    pRender->SetDeviceWidth(width);
    pRender->SetDeviceHeight(height);
    pRender->CreateDevice();

    MN::IGUI* pGUI = MN::IGUI::Instance(pObjectMgr);
    pGUI->open();
    pGUI->ReSize(width, height);


    // create game
    pObjectMgr->create("Demo");

    MSG	msg;
    for (;;)
    {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return 1;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


        static sint64 lasttime = TimeUtil::TimeStamp();
        static sint64 curtime = lasttime;
        static sint64 detla = 0;        // micro seconds
        static float fdetla = 0.0f;    // seconds
        curtime = TimeUtil::TimeStamp();
        detla = curtime - lasttime;
        fdetla = (float)(detla) / 1000.0f;
        fdetla /= 1000.0f;
        pObjectMgr->onExcute(fdetla);
        lasttime = curtime;

        // in the past, one framebuffer show to one display, use the raster-scan, this would result tearing, in which the sceen shows parts of the old frame and the parts of the new frame;
        // now, there are two framebuffers, the display reads from the front buffer, while we can write the next frame to back buffer. when we finish, we signal to GPU to swap the front and back buffer.
        g_eglDevice.SwapBuffers();
    }
    return 0;
}