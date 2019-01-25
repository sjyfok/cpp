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
public:
	CMainWindow();
protected:
	void DrawMouseInput(CDC *pDC);
	void DrawMsg(CDC *pDC);
	void DrawMsgHeader(CDC *pDC);
protected:
	virtual void PostNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};
#endif // !__LOOKER_H__
