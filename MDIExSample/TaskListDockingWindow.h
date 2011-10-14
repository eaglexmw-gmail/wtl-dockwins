// TaskListDockingWindow.h: interface for the CTaskListDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKLISTDOCKINGWINDOW_H__2A6E117E_C650_480D_84F3_1E40C395859C__INCLUDED_)
#define AFX_TASKLISTDOCKINGWINDOW_H__2A6E117E_C650_480D_84F3_1E40C395859C__INCLUDED_

#include <sstream>
#include <dockwins/ExtDockingWindow.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTaskListDockingWindow :
    public dockwins::CBoxedDockingWindowImpl< CTaskListDockingWindow,CWindow,dockwins::COutlookLikeExBoxedDockingWindowTraits>
{
    typedef CTaskListDockingWindow    thisClass;
    typedef dockwins::CBoxedDockingWindowImpl< CTaskListDockingWindow,CWindow,dockwins::COutlookLikeExBoxedDockingWindowTraits> baseClass;
protected:
    enum{nColumns=2, nItems=3};
    void FillList(CListViewCtrl& list)
    {
        for( int i =0; i < nColumns; i++)
        {
            std::basic_stringstream<TCHAR> text;
            text<<_T("column ")<<i+1;
            list.InsertColumn(i,text.str().c_str(),LVCFMT_RIGHT,100,0);
        }
        {
            for(int i =0; i < nItems; i++)
            {
                std::basic_stringstream<TCHAR> text;
                text<<_T("item ")<<i+1;
                list.InsertItem(i,text.str().c_str(),0);
            }
        }
    }
public:
    DECLARE_WND_CLASS(_T("CTaskListDockingWindow"))

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_TASKLIST),
                IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);
        m_list.Create(m_hWnd,NULL,NULL,WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SINGLESEL|LVS_NOSORTHEADER);
        m_list.SetExtendedListViewStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT);
        FillList(m_list);
        return 0;
    }
    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(wParam != SIZE_MINIMIZED )
        {
            RECT rc;
            GetClientRect(&rc);
            ::SetWindowPos(m_list.m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top ,SWP_NOZORDER | SWP_NOACTIVATE);
        }
        bHandled = FALSE;
        return 1;
    }
    void OnDocked(dockwins::HDOCKBAR hBar,bool bHorizontal)
    {
        DWORD dwStyle = GetWindowLong(GWL_STYLE)&(~WS_SIZEBOX);
        SetWindowLong( GWL_STYLE, dwStyle);

        baseClass::OnDocked(hBar,bHorizontal);
    }
    void OnUndocked(dockwins::HDOCKBAR hBar)
    {
        DWORD dwStyle = GetWindowLong(GWL_STYLE) | WS_SIZEBOX;
        SetWindowLong( GWL_STYLE , dwStyle);

        baseClass::OnUndocked(hBar);
    }
protected:
    CListViewCtrl    m_list;
};

#endif // !defined(AFX_TASKLISTDOCKINGWINDOW_H__2A6E117E_C650_480D_84F3_1E40C395859C__INCLUDED_)
