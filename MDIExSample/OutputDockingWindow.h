// OutputDockingWindow.h: interface for the COutputDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_)
#define AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_

#include <dockwins/TabDockingBox.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutputDockingWindow :
    public dockwins::CBoxedDockingWindowImpl<  COutputDockingWindow,CWindow,dockwins::CVC6LikeBoxedDockingWindowTraits>
{
    typedef COutputDockingWindow thisClass;
    typedef dockwins::CBoxedDockingWindowImpl<  COutputDockingWindow,CWindow,dockwins::CVC6LikeBoxedDockingWindowTraits> baseClass;
public:
    DECLARE_WND_CLASS(_T("COutputDockingWindow"))

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
        MESSAGE_HANDLER(WM_KILLFOCUS , OnKillFocus)
        MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_OUTPUT),
                IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);
        m_edit.Create(m_hWnd,NULL, NULL, WS_CHILD | WS_VISIBLE );
        m_edit.AppendText(_T("some text here..."));
        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(wParam != SIZE_MINIMIZED )
        {
            RECT rc;
            GetClientRect(&rc);
            m_edit.SetWindowPos(HWND_TOP, &rc , NULL );
        }
        bHandled = FALSE;
        return 1;
    }

    LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled=FALSE;
        m_edit.SetFocus();
        return 0;
    }

    LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

    LRESULT OnMouseActivate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled=FALSE;
        m_edit.SetFocus();
        ATLASSERT(GetFocus()==m_edit.m_hWnd);
        return MA_ACTIVATE;   // activation already done
    }

protected:
    CEdit m_edit;
};

#endif // !defined(AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_)
