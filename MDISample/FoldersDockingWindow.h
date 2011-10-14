// FoldersDockingWindow.h: interface for the CFoldersDockingWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERSDOCKINGWINDOW_H__46F73EC2_257A_4C57_A311_B5ECB00535DF__INCLUDED_)
#define AFX_FOLDERSDOCKINGWINDOW_H__46F73EC2_257A_4C57_A311_B5ECB00535DF__INCLUDED_

#include <sstream>
#include <dockwins/ExtDockingWindow.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFoldersDockingWindow :
    public dockwins::CTitleDockingWindowImpl< CFoldersDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits>
{
    typedef CFoldersDockingWindow    thisClass;
    typedef dockwins::CTitleDockingWindowImpl< CFoldersDockingWindow,CWindow,dockwins::COutlookLikeTitleDockingWindowTraits> baseClass;
protected:
    void FillTree(CTreeViewCtrl& tree)
    {
        for( int i =0; i < 10; i++)
        {
            std::basic_stringstream<TCHAR> text;
            text<<_T("item ")<<i;
            HTREEITEM hItem=tree.InsertItem(text.str().c_str(),0,1,TVI_ROOT,TVI_LAST);
            for( int j = 0; j < 5; j++)
            {
                std::basic_stringstream<TCHAR> text;
                text<<_T("sub item ")<<j;
                tree.InsertItem(text.str().c_str(),0,1,hItem,TVI_LAST);
            }
        }

    }
public:
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

    DECLARE_WND_CLASS_EX(_T("CFoldersDockingWindow"), 0, COLOR_WINDOW)

    BEGIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_images.Create(16, 16, TRUE, 3, 0);

        ATLASSERT(m_images.m_hImageList);
        CBitmap bmp;

        bmp.LoadBitmap(IDB_DUMMYBMP);

        m_images.Add( bmp, RGB(255,255,255));

        m_tree.Create(m_hWnd,NULL,NULL,
                        TVS_SHOWSELALWAYS | TVS_HASBUTTONS |
                        TVS_LINESATROOT | TVS_HASLINES |
                        TVS_EDITLABELS|TVS_SHOWSELALWAYS|
                        TVS_DISABLEDRAGDROP|
                        WS_CHILD | WS_VISIBLE);
        m_tree.SetImageList(m_images, TVSIL_NORMAL);
        FillTree(m_tree);
        return 0;
    }
    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(wParam != SIZE_MINIMIZED )
        {
            RECT rc;
            GetClientRect(&rc);
            ::SetWindowPos(m_tree.m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top ,SWP_NOZORDER | SWP_NOACTIVATE);
        }
        bHandled = FALSE;
        return 1;
    }
protected:
    CTreeViewCtrl    m_tree;
    CImageList        m_images;
};

#endif // !defined(AFX_FOLDERSDOCKINGWINDOW_H__46F73EC2_257A_4C57_A311_B5ECB00535DF__INCLUDED_)
