#pragma once
#include "_afxwin.h"
enum AfxSig
{
	AfxSig_end = 0,
	AfxSig_vv,
	AfxSig_vw,
	AfxSig_is,
};


#define ON_WM_CREATE() \
	{WM_CREATE, 0, 0, 0, AfxSig_is, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(LPCREATESTRUCT))&OnCreate},
#define ON_WM_PAINT() \
	{WM_PAINT, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(HDC))&OnPaint},
#define ON_WM_CLOSE() \
	{WM_CLOSE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(void))&OnClose},
#define ON_WM_DESTROY() \
	{WM_DESTROY, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(void))&OnDestroy},
#define ON_WM_NCDESTROY() \
	{WM_NCDESTROY, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(void))&OnNcDestroy},
#define ON_WM_TIMER() \
	{WM_TIMER, 0, 0, 0, AfxSig_vw, \
		(AFX_PMSG)(AFX_PMSGW)(int(CWnd::*)(UINT))&OnTimer},