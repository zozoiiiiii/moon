#ifdef UILIB_STATIC
#	define DUILIB_API 
#else
#	if defined(UILIB_EXPORTS)
#		if	defined(_MSC_VER)
#			define DUILIB_API __declspec(dllexport)
#		else
#			define DUILIB_API 
#		endif
#	else
#		if defined(_MSC_VER)
#			define DUILIB_API __declspec(dllimport)
#		else
#			define DUILIB_API 
#		endif
#	endif
#endif

#define UILIB_COMDAT __declspec(selectany)

#if defined _M_IX86
#	pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#	pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#	pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#	pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <stdio.h>

#include "Utils/Utils.h"
#include "Utils/UIDelegate.h"
#include "Core/UIDefine.h"
#include "Core/UIManager.h"
#include "Core/UIBase.h"
#include "Core/UIControl.h"
#include "Core/UIContainer.h"
#include "Core/UIMarkup.h"
#include "Core/UIDlgBuilder.h"
#include "Core/UIRender.h"
#include "Utils/WinImplBase.h"
#include "Utils/WndShadow.h"

#include "Layout/UIVerticalLayout.h"
#include "Layout/UIHorizontalLayout.h"
#include "Layout/UITileLayout.h"
#include "Layout/UITabLayout.h"
#include "Layout/UIChildLayout.h"

#include "Control/UIList.h"
#include "Control/UITreeView.h"

#include "Control/UILabel.h"
#include "Control/UIText.h"
#include "Control/UIEdit.h"

#include "Control/UIButton.h"



#include <olectl.h>
#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))


// namespace
#ifndef NS_MN_BEGIN
#define NS_MN_BEGIN                     namespace MN {
#define NS_MN_END                       }
#define USING_NS_MN                     using namespace MN;
#endif


// base type
#ifdef _WIN32
typedef signed __int8                   sint8;
typedef unsigned __int8                 uint8;
typedef signed __int16                  sint16;
typedef unsigned __int16                uint16;
typedef signed __int32                  sint32;
typedef unsigned __int32                uint32;
typedef signed __int64                  sint64;
typedef unsigned __int64                uint64;

#elif __ANDROID__
#include <stdint.h>
typedef int8_t                          sint8;
typedef uint8_t                         uint8;
typedef int16_t                         sint16;
typedef uint16_t                        uint16;
typedef int32_t                         sint32;
typedef uint32_t                        uint32;
typedef int64_t                         sint64;
typedef uint64_t                        uint64;

#elif __APPLE__
#endif