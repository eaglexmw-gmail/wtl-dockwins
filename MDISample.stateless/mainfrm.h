// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__07FAAE85_FAE5_4CEF_8688_3823D32BADD1__INCLUDED_)
#define AFX_MAINFRM_H__07FAAE85_FAE5_4CEF_8688_3823D32BADD1__INCLUDED_

#include <dockwins/DockingFrame.h>
#include "SampleDockingWindow.h"
#include "FoldersDockingWindow.h"
#include "OutputDockingWindow.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/*
class CMainFrame : public CMDIFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
        public CMessageFilter, public CIdleHandler
*/
class CMainFrame :
        public dockwins::CMDIDockingFrameImpl<CMainFrame>,
        public CUpdateUI<CMainFrame>,
        public CMessageFilter,
        public CIdleHandler
{
    typedef dockwins::CMDIDockingFrameImpl<CMainFrame> baseClass;
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

#if (_WTL_VER >= 0x0700)
        CMDICommandBarCtrl              m_CmdBar;
#else
        CCommandBarCtrl                 m_CmdBar;
#endif
    CSampleDockingWindow    m_sampleDockWnd;
    CSampleDockingWindow    m_sampleDockWnd1;
    CFoldersDockingWindow    m_foldersDockWnd;
    COutputDockingWindow    m_outputDockWnd;

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        if(baseClass::PreTranslateMessage(pMsg))
            return TRUE;

        if (m_hWnd) {
            HWND hWnd = MDIGetActive();
            if(hWnd != NULL)
                return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);
        }

        return FALSE;
    }

    virtual BOOL OnIdle()
    {
        UIUpdateToolBar();
        return FALSE;
    }

    BEGIN_MSG_MAP(CMainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
        COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
        COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
        COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
        COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
        COMMAND_ID_HANDLER(ID_WINDOW_CASCADE, OnWindowCascade)
        COMMAND_ID_HANDLER(ID_WINDOW_TILE_HORZ, OnWindowTile)
        COMMAND_ID_HANDLER(ID_WINDOW_ARRANGE, OnWindowArrangeIcons)

        CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(CMainFrame)
        UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // create command bar window
        HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
        // attach menu
        m_CmdBar.AttachMenu(GetMenu());
        // load command bar images
        m_CmdBar.LoadImages(IDR_MAINFRAME);
        // remove old menu
        SetMenu(NULL);

        HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

        CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
        AddSimpleReBarBand(hWndCmdBar);
        AddSimpleReBarBand(hWndToolBar, NULL, TRUE);
        CreateSimpleStatusBar();

        CreateMDIClient();
        m_CmdBar.SetMDIClient(m_hWndMDIClient);

        UIAddToolBar(hWndToolBar);
        UISetCheck(ID_VIEW_TOOLBAR, 1);
        UISetCheck(ID_VIEW_STATUS_BAR, 1);

        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);
///////////
        InitializeDockingFrame();
        CRect rcBar(0,0,300,100);
        m_sampleDockWnd.Create(m_hWnd,rcBar,_T("Sample docking window - initially floating"));
        CRect rcDef(0,0,100,100);
        m_sampleDockWnd1.Create(m_hWnd,rcDef,_T("Sample docking window - initially docked"));
        DockWindow(m_sampleDockWnd1,dockwins::CDockingSide(dockwins::CDockingSide::sBottom),
                        0/*nBar*/,float(0.0)/*fPctPos*/,100/*nWidth*/,100/* nHeight*/);

        m_foldersDockWnd.Create(m_hWnd,rcDef,_T("Folders"));
        DockWindow(m_foldersDockWnd,dockwins::CDockingSide(dockwins::CDockingSide::sLeft),
                        0/*nBar*/,float(0.0)/*fPctPos*/,200/*nWidth*/,100/* nHeight*/);

        m_outputDockWnd.Create(m_hWnd,rcDef,_T("Output"));
        DockWindow(m_outputDockWnd,
                    dockwins::CDockingSide(dockwins::CDockingSide::sRight),
                    0/*nBar*/,float(0.0)/*fPctPos*/,200/*nWidth*/,100/* nHeight*/);

        return 0;
    }

    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        PostMessage(WM_CLOSE);
        return 0;
    }

    LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CChildFrame* pChild = new CChildFrame;
        pChild->CreateEx(m_hWndClient);

        // TODO: add code to initialize document

        return 0;
    }

    LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        static BOOL bVisible = TRUE;    // initially visible
        bVisible = !bVisible;
        CReBarCtrl rebar = m_hWndToolBar;
        int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);    // toolbar is 2nd added band
        rebar.ShowBand(nBandIndex, bVisible);
        UISetCheck(ID_VIEW_TOOLBAR, bVisible);
        UpdateLayout();
        return 0;
    }

    LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
        ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
        UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
        UpdateLayout();
        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }

    LRESULT OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        MDICascade();
        return 0;
    }

    LRESULT OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        MDITile();
        return 0;
    }

    LRESULT OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        MDIIconArrange();
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__07FAAE85_FAE5_4CEF_8688_3823D32BADD1__INCLUDED_)
