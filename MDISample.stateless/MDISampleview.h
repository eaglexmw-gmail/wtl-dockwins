// MDISampleView.h : interface of the CMDISampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDISAMPLEVIEW_H__BF82751A_9923_4832_BF82_54CE6E9443E8__INCLUDED_)
#define AFX_MDISAMPLEVIEW_H__BF82751A_9923_4832_BF82_54CE6E9443E8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMDISampleView : public CWindowImpl<CMDISampleView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CMDISampleView)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CPaintDC dc(m_hWnd);

        //TODO: Add your drawing code here

        return 0;
    }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDISAMPLEVIEW_H__BF82751A_9923_4832_BF82_54CE6E9443E8__INCLUDED_)
