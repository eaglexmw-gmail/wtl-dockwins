// SampleDockingWindow.h: interface for the CSampleDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_)
#define AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_

#include <dockwins/TabDockingBox.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSampleDockingWindow :
    public dockwins::CBoxedDockingWindowImpl< CSampleDockingWindow,CWindow,dockwins::COutlookLikeBoxedDockingWindowTraits>
{
    typedef CSampleDockingWindow    thisClass;
    typedef dockwins::CBoxedDockingWindowImpl< CSampleDockingWindow,CWindow,dockwins::COutlookLikeBoxedDockingWindowTraits> baseClass;
public:
    CSampleDockingWindow(DWORD dwIcon = IDR_MAINFRAME)
        :m_dwIcon(dwIcon)
    {
    }
    DECLARE_WND_CLASS(_T("CSampleDockingWindow"))

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
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
        int txtLen = GetWindowTextLength()+1;
        TCHAR* pTxt = new TCHAR[txtLen];
        GetWindowText(pTxt,txtLen);
        dc.DrawText(pTxt/*_T("SampleDockingWindow")*/,-1,&rc, DT_END_ELLIPSIS | DT_CENTER | DT_VCENTER | DT_SINGLELINE );
        delete [] pTxt;
//        dc.DrawText(_T("SampleDockingWindow"),-1,&rc, DT_END_ELLIPSIS | DT_CENTER | DT_VCENTER | DT_SINGLELINE );
        return 0;
    }
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
/*
        HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(dwIcon),
                IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
        SetIcon(hIcon, TRUE);
*/
        HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(m_dwIcon),
                IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);
                return 0;
    }
protected:
    DWORD m_dwIcon;
};

#endif // !defined(AFX_SAMPLEDOCKINGWINDOW_H__4C41BD02_6310_48F1_8FF9_1E22A9E5E293__INCLUDED_)
