////////////////////////////////////////////
// _AFXIMPL.H�ļ�

#ifndef __AFXIMPL_H__
#define __AFXIMPL_H__

#include "_afxwin.h"

// ����������ͱ�־
#define AFX_WND_REG (0x0001)		// ʹ�õ�1λ	
#define AFX_WNDFRAMEORVIEW_REG (0x0002) // ʹ�õ�2λ

#define AFX_WND ("Wnd")
#define AFX_WNDFRAMEORVIEW ("FrameOrView")

// ��ܳ���ע�ᴰ����ʱʹ�õ���������Щ����������WINCORE.CPP�ļ�
extern const TCHAR _afxWnd[];
extern const TCHAR _afxWndFrameOrView[];


union MessageMapFunctions
{
	AFX_PMSG pfn;

	void (CWnd::*pfn_vv)(void);
	void (CWnd::*pfn_vw)(UINT);
	int (CWnd::*pfn_is)(LPTSTR);
};

#endif	// __AFXIMPL_H__