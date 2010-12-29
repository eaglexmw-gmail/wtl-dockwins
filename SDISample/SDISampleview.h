// SDISampleView.h : interface of the CSDISampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDISAMPLEVIEW_H__B1B7A8D8_7A62_4F18_997F_DADD78892F41__INCLUDED_)
#define AFX_SDISAMPLEVIEW_H__B1B7A8D8_7A62_4F18_997F_DADD78892F41__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSDISampleView : public CWindowImpl<CSDISampleView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CSDISampleView)
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

#endif // !defined(AFX_SDISAMPLEVIEW_H__B1B7A8D8_7A62_4F18_997F_DADD78892F41__INCLUDED_)
