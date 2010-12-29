// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__95628E42_589A_4EEE_AE78_25615B718DCD__INCLUDED_)
#define AFX_CHILDFRM_H__95628E42_589A_4EEE_AE78_25615B718DCD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CChildFrame : public CMDIChildWindowImpl<CChildFrame>
{
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MDICHILD)

    CMDISampleView m_view;

    virtual void OnFinalMessage(HWND /*hWnd*/)
    {
        delete this;
    }

    BEGIN_MSG_MAP(CChildFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_FORWARDMSG, OnForwardMsg)
        CHAIN_MSG_MAP(CMDIChildWindowImpl<CChildFrame>)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

        bHandled = FALSE;
        return 1;
    }

    LRESULT OnForwardMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        LPMSG pMsg = (LPMSG)lParam;

        if(CMDIChildWindowImpl<CChildFrame>::PreTranslateMessage(pMsg))
            return TRUE;

        return m_view.PreTranslateMessage(pMsg);
    }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__95628E42_589A_4EEE_AE78_25615B718DCD__INCLUDED_)
