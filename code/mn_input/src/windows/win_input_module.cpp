#include "win_input_module.h"
#include "public/object/mn_object_mgr.h"
#include "public/object/mn_varlist.h"


#define _WIN32_WINNT 0x0400
#include <windows.h>

void WinInputModule::OnCreate() 
{
    m_pEventMgr = GetObjectMgr()->getEventMgr();
}

void WinInputModule::OnDestroy()
{

}

bool WinInputModule::MsgProc(unsigned int msg, size_t param1, size_t param2, int& result)
{
    switch(msg)
    {
    case WM_KEYDOWN:
        {

        }break;
    case WM_KEYUP:
        {

        }break;
    case WM_MOUSEMOVE:
        {
            int nx = LOWORD(param2); 
            int ny = HIWORD(param2);
            m_pEventMgr->Invoke(NULL, "input",  MN::VarList()<<IET_Mouse_Move<<nx<<ny);
        }break;
		/*
	case WM_MOUSEWHEEL:
		{
			
		}break;
        */
    case WM_LBUTTONDOWN:
        {
            int nx = LOWORD(param2); 
            int ny = HIWORD(param2);
            m_pEventMgr->Invoke(NULL, "input", MN::VarList()<<IET_Mouse_LDown<<nx<<ny);
        }break;
    case WM_LBUTTONUP:
        {
            int nx = LOWORD(param2); 
            int ny = HIWORD(param2);
            m_pEventMgr->Invoke(NULL, "input", MN::VarList()<<IET_Mouse_LUp<<nx<<ny);
        }break;
	case WM_RBUTTONDOWN:
		{
			int nx = LOWORD(param2); 
            int ny = HIWORD(param2);
            m_pEventMgr->Invoke(NULL, "input", MN::VarList()<<IET_Mouse_RDown<<nx<<ny);
		}break;
	case WM_RBUTTONUP:
		{
			int nx = LOWORD(param2); 
            int ny = HIWORD(param2);
            m_pEventMgr->Invoke(NULL, "input", MN::VarList()<<IET_Mouse_RUp<<nx<<ny);
		}break;
	default:
		break;
	}


	return true;

}