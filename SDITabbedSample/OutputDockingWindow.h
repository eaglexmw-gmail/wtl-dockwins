// OutputDockingWindow.h: interface for the COutputDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_)
#define AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_

#include <dockwins/ExtDockingWindow.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutputDockingWindow :
    public dockwins::CTitleDockingWindowImpl< COutputDockingWindow,CWindow,dockwins::CVC6LikeTitleDockingWindowTraits>
{
    typedef COutputDockingWindow thisClass;
    typedef dockwins::CTitleDockingWindowImpl< COutputDockingWindow,CWindow,dockwins::CVC6LikeTitleDockingWindowTraits> baseClass;
public:
    DECLARE_WND_CLASS(_T("COutputDockingWindow"))

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_edit.Create(m_hWnd,NULL, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE);
        m_edit.AppendText(_T("some text here..."));
        return 0;
    }
    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(wParam != SIZE_MINIMIZED )
        {
            RECT rc;
            GetClientRect(&rc);
            m_edit.SetWindowPos(NULL, &rc ,SWP_NOZORDER | SWP_NOACTIVATE );
        }
        bHandled = FALSE;
        return 1;
    }

protected:
    CRichEditCtrl m_edit;
};

#endif // !defined(AFX_OUTPUTDOCKINGWINDOW_H__0D6B82E7_6A06_4FCC_B621_B21ED1C742E9__INCLUDED_)
