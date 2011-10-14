// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__FF6062EE_F8DC_4B97_8E74_0069145120B8__INCLUDED_)
#define AFX_MAINFRM_H__FF6062EE_F8DC_4B97_8E74_0069145120B8__INCLUDED_

#include <dockwins/dbstate.h>
#ifdef STORE_PRIVATE_DATA_IN_XML
#include <dockwins/stgxml.h>
#else
#include <dockwins/stgreg.h>
#endif //STORE_PRIVATE_DATA_IN_XML
#include <dockwins/DockingFrame.h>


#include "SampleDockingWindow.h"
#include "FoldersDockingWindow.h"
#include "OutputDockingWindow.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/*
class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
        public CMessageFilter, public CIdleHandler
*/

const UINT CWM_INITIALIZE = dockwins::WMDF_LAST+1;

class CMainFrame :
        public dockwins::CDockingFrameImpl<CMainFrame>,
        public CUpdateUI<CMainFrame>,
        public CMessageFilter,
        public CIdleHandler
{
    typedef dockwins::CDockingFrameImpl<CMainFrame> baseClass;
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    CSDISampleView m_view;

    CCommandBarCtrl m_CmdBar;
    CSampleDockingWindow    m_sampleDockWnd1;
    CSampleDockingWindow    m_sampleDockWnd2;
    CSampleDockingWindow    m_sampleDockWnd3;
    CSampleDockingWindow    m_sampleDockWnd4;
    CFoldersDockingWindow    m_foldersDockWnd;
    COutputDockingWindow    m_outputDockWnd;
#ifdef STORE_PRIVATE_DATA_IN_XML
    sstate::CWindowStateMgr<sstate::CStgXML> m_stateMgr;
    class  CConfig :
        public sstate::CStgXML
    {
    public:
        CConfig()
        {
            TCHAR name[_MAX_PATH];
            int len=::GetModuleFileName(_Module.GetModuleInstance(), name,_MAX_PATH);
            if(len!=0)
            {
                m_filename.assign(name,len);
                m_filename+=_T(".config");
                Load(m_filename.c_str());
            }
            if(Root()==0)
                Create();
        }
        ~CConfig()
        {
            if(!m_filename.empty()
                && (Root()!=0))
                Save(m_filename.c_str());
        }
    private:
        std::basic_string<TCHAR> m_filename;
    } m_config;
#else
    sstate::CWindowStateMgr<sstate::CStgRegistry> m_stateMgr;
#endif //STORE_PRIVATE_DATA_IN_XML


    CMainFrame()
        : m_sampleDockWnd1(IDI_ICON1),
            m_sampleDockWnd2(IDI_ICON2),
            m_sampleDockWnd3(IDI_ICON3),
            m_sampleDockWnd4(IDI_ICON4)
    {
    }

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        if(baseClass::PreTranslateMessage(pMsg))
            return TRUE;

        return m_view.PreTranslateMessage(pMsg);
    }
    bool IsToolbarVisible() const
    {
        CReBarCtrl rebar(m_hWndToolBar);
        int i = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);    // toolbar is 2nd added band
        REBARBANDINFO rbi;
        ZeroMemory(&rbi,sizeof(REBARBANDINFO));
        rbi.cbSize = sizeof(REBARBANDINFO);
        rbi.fMask = RBBIM_STYLE;
        rebar.GetBandInfo(i, &rbi);
        return !(rbi.fStyle&RBBS_HIDDEN);
    }

    virtual BOOL OnIdle()
    {
        UIUpdateToolBar();
        UISetCheck(ID_VIEW_TOOLBAR,IsToolbarVisible());
        UISetCheck(ID_VIEW_STATUS_BAR,::IsWindowVisible(m_hWndStatusBar));
        UISetCheck(ID_VIEW_FOLDERS,m_foldersDockWnd.IsWindowVisible());
        UISetCheck(ID_VIEW_OUTPUT,m_outputDockWnd.IsWindowVisible());

        UISetCheck(ID_VIEW_SAMPLE_WND1,m_sampleDockWnd1.IsWindowVisible());
        UISetCheck(ID_VIEW_SAMPLE_WND2,m_sampleDockWnd2.IsWindowVisible());
        UISetCheck(ID_VIEW_SAMPLE_WND3,m_sampleDockWnd3.IsWindowVisible());
        UISetCheck(ID_VIEW_SAMPLE_WND4,m_sampleDockWnd4.IsWindowVisible());

        return FALSE;
    }

    BEGIN_MSG_MAP(CMainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(CWM_INITIALIZE, OnInitialize)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)

        COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
        COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
        COMMAND_ID_HANDLER(ID_FILE_NEW_WINDOW, OnFileNewWindow)
        COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
        COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
        COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)

        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_FOLDERS,m_foldersDockWnd)
        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_OUTPUT,m_outputDockWnd)

        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_SAMPLE_WND1,m_sampleDockWnd1)
        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_SAMPLE_WND2,m_sampleDockWnd2)
        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_SAMPLE_WND3,m_sampleDockWnd3)
        COMMAND_TOGGLE_MEMBER_HANDLER(ID_VIEW_SAMPLE_WND4,m_sampleDockWnd4)

        CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
        CHAIN_MSG_MAP(baseClass)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(CMainFrame)
        UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_FOLDERS, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_OUTPUT, UPDUI_MENUPOPUP)

        UPDATE_ELEMENT(ID_VIEW_SAMPLE_WND1, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_SAMPLE_WND2, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_SAMPLE_WND3, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_VIEW_SAMPLE_WND4, UPDUI_MENUPOPUP)

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

        m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

        UIAddToolBar(hWndToolBar);
//        UISetCheck(ID_VIEW_TOOLBAR, 1);
//        UISetCheck(ID_VIEW_STATUS_BAR, 1);

        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);
///////////
        InitializeDockingFrame();
        DWORD dwStyle=WS_OVERLAPPEDWINDOW | WS_POPUP| WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

        CRect rcBar(0,0,300,100);
        m_sampleDockWnd1.Create(m_hWnd,rcBar,_T("<<1>>"),dwStyle);
        CRect rcDef(0,0,100,100);

        m_sampleDockWnd2.Create(m_hWnd,rcBar,_T("<<<<2>>>>"),dwStyle);
        DockWindow(m_sampleDockWnd1,dockwins::CDockingSide(dockwins::CDockingSide::sBottom),
                        0/*nBar*/,float(0.0)/*fPctPos*/,100/*nWidth*/,100/* nHeight*/);

        m_sampleDockWnd3.Create(m_hWnd,rcBar,_T("<<<<<<3>>>>>>>"),dwStyle);
        m_sampleDockWnd3.DockTo(m_sampleDockWnd2);

        m_sampleDockWnd4.Create(m_hWnd,rcDef,_T("<<<<<<<<<<<<<4>>>>>>>>>>"),dwStyle);
        m_sampleDockWnd4.DockTo(m_sampleDockWnd1);


        m_foldersDockWnd.Create(m_hWnd,rcDef,_T("Folders"),dwStyle);
        DockWindow(m_foldersDockWnd,dockwins::CDockingSide(dockwins::CDockingSide::sLeft),
                        0/*nBar*/,float(0.0)/*fPctPos*/,200/*nWidth*/,100/* nHeight*/);

        m_outputDockWnd.Create(m_hWnd,rcDef,_T("Output"),dwStyle);
        DockWindow(m_outputDockWnd,
                    dockwins::CDockingSide(dockwins::CDockingSide::sRight),
                    0/*nBar*/,float(0.0)/*fPctPos*/,200/*nWidth*/,100/* nHeight*/);
        PostMessage(CWM_INITIALIZE);
        return 0;
    }

    LRESULT OnInitialize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        sstate::CDockWndMgrEx mgrDockWnds(m_hWnd);
        mgrDockWnds.Add(sstate::CDockingWindowStateAdapterEx<CSampleDockingWindow>(m_sampleDockWnd1));
        mgrDockWnds.Add(sstate::CDockingWindowStateAdapterEx<CSampleDockingWindow>(m_sampleDockWnd2));
        mgrDockWnds.Add(sstate::CDockingWindowStateAdapterEx<CSampleDockingWindow>(m_sampleDockWnd3));
        mgrDockWnds.Add(sstate::CDockingWindowStateAdapterEx<CSampleDockingWindow>(m_sampleDockWnd4));

        mgrDockWnds.Add(sstate::CDockingWindowStateAdapter<COutputDockingWindow>(m_outputDockWnd));
        mgrDockWnds.Add(sstate::CDockingWindowStateAdapter<CFoldersDockingWindow>(m_foldersDockWnd));

        m_stateMgr.Initialize(m_hWnd);
        m_stateMgr.Add(sstate::CRebarStateAdapter(m_hWndToolBar));
        m_stateMgr.Add(sstate::CToggleWindowAdapter(m_hWndStatusBar));
        m_stateMgr.Add(mgrDockWnds);
#ifdef STORE_PRIVATE_DATA_IN_XML
        if(!m_config
            || !m_stateMgr.Restore(m_config) )
                m_stateMgr.RestoreDefault();
#else
        CRegKey key;
        if(key.Open(HKEY_CURRENT_USER,_T("SOFTWARE\\WTL Docking Window\\SDITabbedSample"),KEY_READ)==ERROR_SUCCESS)
        {
            sstate::CStgRegistry reg(key.Detach());
            m_stateMgr.Restore(reg);
        }
        else
            m_stateMgr.RestoreDefault();
#endif //STORE_PRIVATE_DATA_IN_XML
        UpdateLayout();
        return 0;
    }

    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled=false;
#ifdef STORE_PRIVATE_DATA_IN_XML
        if(!(!m_config))
            m_stateMgr.Store(m_config);
#else
        CRegKey key;
        if(key.Create(HKEY_CURRENT_USER,_T("SOFTWARE\\WTL Docking Window\\SDITabbedSample"))==ERROR_SUCCESS)
        {
            sstate::CStgRegistry reg(key.Detach());
            m_stateMgr.Store(reg);
        }
#endif //STORE_PRIVATE_DATA_IN_XML
        return 0;
    }


    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        PostMessage(WM_CLOSE);
        return 0;
    }

    LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // TODO: add code to initialize document

        return 0;
    }

    LRESULT OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
        return 0;
    }

    LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        static BOOL bVisible = IsToolbarVisible();
        bVisible = !bVisible;
        CReBarCtrl rebar = m_hWndToolBar;
        int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);    // toolbar is 2nd added band
        rebar.ShowBand(nBandIndex, bVisible);
//        UISetCheck(ID_VIEW_TOOLBAR, bVisible);
        UpdateLayout();
        return 0;
    }

    LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
        ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
//        UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
        UpdateLayout();
        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__FF6062EE_F8DC_4B97_8E74_0069145120B8__INCLUDED_)
