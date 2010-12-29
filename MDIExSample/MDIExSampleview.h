// MDIExSampleView.h : interface of the CMDIExSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIEXSAMPLEVIEW_H__112B7E00_7321_4DA3_B49B_2A3F8ABE24FE__INCLUDED_)
#define AFX_MDIEXSAMPLEVIEW_H__112B7E00_7321_4DA3_B49B_2A3F8ABE24FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMDIExSampleView : public CWindowImpl<CMDIExSampleView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CMDIExSampleView)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//    LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//    LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//    LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

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

#endif // !defined(AFX_MDIEXSAMPLEVIEW_H__112B7E00_7321_4DA3_B49B_2A3F8ABE24FE__INCLUDED_)
