// DockSiteSample.cpp : main source file for DockSiteSample.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>


#include "resource.h"

#include "DockSiteWindow.h"

CAppModule _Module;


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//    HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
    INITCOMMONCONTROLSEX iccx;
    iccx.dwSize = sizeof(iccx);
    iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
    BOOL bRet = ::InitCommonControlsEx(&iccx);
    bRet;
    ATLASSERT(bRet);
#else
    ::InitCommonControls();
#endif

    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));

    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

    CDockSiteWindow wndMain;

    if(wndMain.Create(NULL,CWindow::rcDefault,_T("Sample Docking Site Window"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS) == NULL)
    {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }

    wndMain.ShowWindow(nCmdShow);

    int nRet = theLoop.Run();

    _Module.RemoveMessageLoop();

    _Module.Term();
    ::CoUninitialize();

    return nRet;
}
