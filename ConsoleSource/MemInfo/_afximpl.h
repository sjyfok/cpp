#pragma once
#include "_afxwin.h"

#define AFX_WND_REG		(0x0001)
#define AFX_WNDFRAMEORVIEW_REG	(0x0002)
#define AFX_WND	("Wnd")
#define AFX_WNDFRAMEORVIEW	("FrameOrView")

extern const TCHAR _afxWnd[];
extern const TCHAR _afxWndFrameOrView[];

union MessageMapFunctions
{
	AFX_PMSG pfn;
	void(CWnd::*pfn_vv)(void);
	void(CWnd::*pfn_vw)(UINT);
	int (CWnd::*pfn_is)(LPTSTR);
};