// DockSiteWindow.h: interface for the CDockSiteWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKSITEWINDOW_H__78B78B04_7909_4BF3_8D73_73EF82ABA491__INCLUDED_)
#define AFX_DOCKSITEWINDOW_H__78B78B04_7909_4BF3_8D73_73EF82ABA491__INCLUDED_

#include <dockwins/DockingFrame.h>
#include "SampleDockingWindow.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDockSiteWindow : public dockwins::CDockingSiteImpl<CDockSiteWindow>//public CWindowImpl<CDockSiteSampleView>
{
    typedef dockwins::CDockingSiteImpl<CDockSiteWindow> baseClass;
public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CDockSiteWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        InitializeDockingFrame();
        CRect rcBar(0,0,300,100);
        m_sampleDockWnd.Create(m_hWnd,rcBar,_T("Sample docking window"));
        m_sampleDockWnd1.Create(m_hWnd,rcBar,_T("Sample docking window"));
        return 0;
    }
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if(m_sampleDockWnd.m_hWnd!=0)
            m_sampleDockWnd.DestroyWindow();
        if(m_sampleDockWnd1.m_hWnd!=0)
            m_sampleDockWnd1.DestroyWindow();
        ::PostQuitMessage(1);
        return 0;
    }
protected:
    CSampleDockingWindow    m_sampleDockWnd;
    CSampleDockingWindow    m_sampleDockWnd1;
};

#endif // !defined(AFX_DOCKSITEWINDOW_H__78B78B04_7909_4BF3_8D73_73EF82ABA491__INCLUDED_)
