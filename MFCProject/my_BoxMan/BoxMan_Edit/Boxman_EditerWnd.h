#pragma once
#include "BoxMan_Edit.h"

class CBoxman_EditerWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CBoxman_EditerWnd)
public:
	CBoxman_EditerWnd();
	~CBoxman_EditerWnd();
protected:
	CToolBar m_wndToolBar;
	int m_now_Select;
	CBoxMan_Edit m_boxManEdit;
	BOOL m_bMouseDown;
	CPoint m_mousePoint;

public:
	BOOL CreateExToolBar(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuMapBall();
	afx_msg void OnMenuMapBluewall();
	afx_msg void OnMenuMapManWallBall();
	afx_msg void OnMenuMapWhitewall();
	afx_msg void OnMenuMapYellowbox();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuSaveMap();
};

