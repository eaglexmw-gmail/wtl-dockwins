// SDISample.cpp : main source file for SDISample.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>


#include "resource.h"

#include "SDISampleView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

CAppModule _Module;

class CSDISampleThreadManager
{
public:
    // thread init param
    struct _RunData
    {
        LPTSTR lpstrCmdLine;
        int nCmdShow;
    };

    // thread proc
    static DWORD WINAPI RunThread(LPVOID lpData)
    {
        CMessageLoop theLoop;
        _Module.AddMessageLoop(&theLoop);

        _RunData* pData = (_RunData*)lpData;
        CMainFrame wndFrame;

        if(wndFrame.CreateEx() == NULL)
        {
            ATLTRACE(_T("Frame window creation failed!\n"));
            return 0;
        }

//        wndFrame.ShowWindow(pData->nCmdShow);
        ::SetForegroundWindow(wndFrame);    // Win95 needs this
        delete pData;

        int nRet = theLoop.Run();

        _Module.RemoveMessageLoop();
        return nRet;
    }

    DWORD m_dwCount;
    HANDLE m_arrThreadHandles[MAXIMUM_WAIT_OBJECTS - 1];

    CSDISampleThreadManager() : m_dwCount(0)
    { }

// Operations
    DWORD AddThread(LPTSTR lpstrCmdLine, int nCmdShow)
    {
        if(m_dwCount == (MAXIMUM_WAIT_OBJECTS - 1))
        {
            ::MessageBox(NULL, _T("ERROR: Cannot create ANY MORE threads!!!"), _T("SDISample"), MB_OK);
            return 0;
        }

        _RunData* pData = new _RunData;
        pData->lpstrCmdLine = lpstrCmdLine;
        pData->nCmdShow = nCmdShow;
        DWORD dwThreadID;
        HANDLE hThread = ::CreateThread(NULL, 0, RunThread, pData, 0, &dwThreadID);
        if(hThread == NULL)
        {
            ::MessageBox(NULL, _T("ERROR: Cannot create thread!!!"), _T("SDISample"), MB_OK);
            return 0;
        }

        m_arrThreadHandles[m_dwCount] = hThread;
        m_dwCount++;
        return dwThreadID;
    }

    void RemoveThread(DWORD dwIndex)
    {
        ::CloseHandle(m_arrThreadHandles[dwIndex]);
        if(dwIndex != (m_dwCount - 1))
            m_arrThreadHandles[dwIndex] = m_arrThreadHandles[m_dwCount - 1];
        m_dwCount--;
    }

    int Run(LPTSTR lpstrCmdLine, int nCmdShow)
    {
        MSG msg;
        // force message queue to be created
        ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

        AddThread(lpstrCmdLine, nCmdShow);

        int nRet = m_dwCount;
        DWORD dwRet;
        while(m_dwCount > 0)
        {
            dwRet = ::MsgWaitForMultipleObjects(m_dwCount, m_arrThreadHandles, FALSE, INFINITE, QS_ALLINPUT);

            if(dwRet == 0xFFFFFFFF)
                ::MessageBox(NULL, _T("ERROR: Wait for multiple objects failed!!!"), _T("SDISample"), MB_OK);
            else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + m_dwCount - 1))
                RemoveThread(dwRet - WAIT_OBJECT_0);
            else if(dwRet == (WAIT_OBJECT_0 + m_dwCount))
            {
                ::GetMessage(&msg, NULL, 0, 0);
                if(msg.message == WM_USER)
                	AddThread("", SW_SHOWNORMAL);
                else
                	::MessageBeep((UINT)-1);
            }
            else
                ::MessageBeep((UINT)-1);
        }

        return nRet;
    }
};

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
    HINSTANCE hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName());
    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));


    CSDISampleThreadManager mgr;
    int nRet = mgr.Run(lpstrCmdLine, nCmdShow);

    _Module.Term();
    ::FreeLibrary(hInstRich);
    ::CoUninitialize();

    return nRet;
}
