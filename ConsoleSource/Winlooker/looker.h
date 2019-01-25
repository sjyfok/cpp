#ifndef __LOOKER_H__
#define __LOOKER_H__

#include "afxwin.h"

class CMyApp :public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

class CMainWindow :public CWnd
{
protected:
	int m_cxChar;
	int m_cyChar;
	int m_cyLine;
	HCURSOR m_hCursorArrow;
	HCURSOR m_hCursorTarget;
	RECT m_rcMouseDown;
	RECT m_rcMsgBoxBorder;
	RECT m_rcMsgBox;
	CPoint m_ptHeaderOrigin;
	BOOL m_bCatchMouseDown;
};
#endif // !__LOOKER_H__
