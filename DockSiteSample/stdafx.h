// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__90B2E463_9E2C_482D_8FDF_4C043468AC9E__INCLUDED_)
#define AFX_STDAFX_H__90B2E463_9E2C_482D_8FDF_4C043468AC9E__INCLUDED_

// Change these values to use different versions
#define WINVER        0x0400
//#define _WIN32_WINNT    0x0400
#define _WIN32_IE    0x0400
#define _RICHEDIT_VER    0x0100
#include <atlbase.h>
#if (_ATL_VER >= 0x0700)
#include <atlstr.h>
#endif //(_ATL_VER >= 0x0700)
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlmisc.h>

#if (_ATL_VER >= 0x0700)
#define _WTL_NO_CSTRING
#include <atlcoll.h>
#endif //(_ATL_VER >= 0x0700)

#pragma message("to add/remove auto-hiding features just add/remove #include <DWAutoHide.h>")
#include <dockwins/DWAutoHide.h>

#ifdef _MSC_VER
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif // _MSC_VER

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__90B2E463_9E2C_482D_8FDF_4C043468AC9E__INCLUDED_)
