// Copyright (c) 2002
// Sergey Klimov (kidd@ukr.net)
// WTL Docking windows
//
// This code is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included. If
// the source code in  this file is used in any commercial application
// then a simple email would be nice.

#ifndef WTL_DW_SIMPLESPLITTERBAR_H_INCLUDED_
#define WTL_DW_SIMPLESPLITTERBAR_H_INCLUDED_

#pragma once

#ifndef __ATLMISC_H__
#error SimpleSplitterBar.h requires atlmisc.h to be included first
#endif

#include "dockwins.h"

namespace dockwins
{

struct CSimpleSplitterBarTraits
{
    static int GetWidth()
    {
        return ::GetSystemMetrics(SM_CYSIZEFRAME);
    }

    static int GetHeight()
    {
        return ::GetSystemMetrics(SM_CYSIZEFRAME);
    }

    static int GetSize(bool vertical)
    {
        return vertical ? GetWidth() : GetHeight();
    }
};

template<class TTraits = CSimpleSplitterBarTraits>
class CSimpleSplitterBar
    : public CRect
{
public:
    typedef TTraits Traits;

    CSimpleSplitterBar(bool bHorizontal = true)
        : m_bHorizontal(bHorizontal)
    {
    }

    CSimpleSplitterBar(const CSimpleSplitterBar& ref)
        : CRect(ref), m_bHorizontal(ref.IsHorizontal())
    {
    }

    long GetThickness()
    {
        return m_bHorizontal ? TTraits::GetHeight() : TTraits::GetWidth();
    }

    void SetOrientation(bool bHorizontal)
    {
        m_bHorizontal = bHorizontal;
    }

    bool IsHorizontal() const
    {
        return m_bHorizontal;
    }

    bool IsPtIn(const CPoint& pt) const
    {
        return (PtInRect(pt) != FALSE);
    }

    HCURSOR GetCursor(const CPoint& pt) const
    {
        HCURSOR hCursor = NULL;

        if (IsPtIn(pt))
        {
            CDWSettings settings;
            hCursor = ((IsHorizontal())
                       ? settings.HResizeCursor()
                       : settings.VResizeCursor());
        }

        return hCursor;
    }

    void Draw(CDC& dc) const
    {
        dc.FillRect(this, (HBRUSH)LongToPtr(COLOR_3DFACE + 1));
    }

    void DrawGhostBar(CDC& dc) const
    {
        CBrush brush = CDCHandle::GetHalftoneBrush();

        if (brush.m_hBrush != NULL)
        {
            HBRUSH hBrushOld = dc.SelectBrush(brush);
            dc.PatBlt(this->left, this->top, this->Width(), this->Height(), PATINVERT);
            dc.SelectBrush(hBrushOld);
        }
    }

    void CleanGhostBar(CDC& dc) const
    {
        DrawGhostBar(dc);
    }

protected:
    bool m_bHorizontal;
};

template<class TTraits = CSimpleSplitterBarTraits>
class CSimpleSplitterBarEx
    : public CSimpleSplitterBar<TTraits>
{
    typedef CSimpleSplitterBar<TTraits> baseClass;
public:
    CSimpleSplitterBarEx(bool bHorizontal = true)
        : baseClass(bHorizontal)
    {
    }
    CSimpleSplitterBarEx(const CSimpleSplitterBarEx& ref)
        : baseClass(ref)
    {
    }

    void Draw(CDC& dc, DockingSide side = DockingSide_None)
    {
        dc.FillRect(this, COLOR_3DFACE);

        CRect rc(*this);

        DWORD flags = 0;

        switch (side)
        {
            case DockingSide_Left:
                flags = BF_RIGHT;
                break;
            case DockingSide_Right:
                flags = BF_LEFT;
                break;
            case DockingSide_Top:
                flags = BF_BOTTOM;
                break;
            case DockingSide_Bottom:
                flags = BF_TOP;
                break;
        }

        dc.DrawEdge(&rc, EDGE_RAISED, flags);
    }

};

template<class T>
class CSimpleSplitterBarSlider
{
    typedef T CSplitter;
    typedef CSimpleSplitterBarSlider<CSplitter> thisClass;
public:
    CSimpleSplitterBarSlider(CSplitter& splitter)
        : m_splitter(splitter)
    {
        if (!m_splitter.IsHorizontal())
        {
            m_pTop = &m_splitter.left;
            m_pDependant = &m_splitter.right;
        }
        else
        {
            m_pTop = &m_splitter.top;
            m_pDependant = &m_splitter.bottom;
        }
    }
    operator long() const
    {
        return *m_pTop;
    }

    long operator=(long val)
    {
        *m_pDependant = val + m_splitter.GetThickness();
        return *m_pTop = val;
    }

    thisClass& operator += (long val)
    {
        *this = *this + val;
        return *this;
    }
    thisClass& operator -= (long val)
    {
        *this = *this - val;
        return *this;
    }

protected:
    CSplitter& m_splitter;
    long*    m_pTop;
    long*    m_pDependant;
};

}//namespace dockwins

#endif // WTL_DW_SIMPLESPLITTERBAR_H_INCLUDED_
