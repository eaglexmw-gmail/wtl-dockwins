// SampleDockingWindow.h: interface for the CSampleDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_)
#define AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_

#include <dockwins/ExtDockingWindow.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSampleDockingWindow :
    public dockwins::CTitleDockingWindowImpl< CSampleDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits>
{
    typedef CSampleDockingWindow    thisClass;
    typedef dockwins::CTitleDockingWindowImpl< CSampleDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits> baseClass;
public:
    DECLARE_WND_CLASS(_T("CSampleDockingWindow"))

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, (HBRUSH)LongToPtr(COLOR_WINDOW + 1));
        dc.SetBkMode(TRANSPARENT);
        dc.DrawText(_T("SampleDockingWindow"),-1,&rc, DT_END_ELLIPSIS | DT_CENTER | DT_VCENTER | DT_SINGLELINE );

        return 0;
    }
};

#endif // !defined(AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_)
