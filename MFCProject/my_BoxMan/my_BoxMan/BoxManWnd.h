#pragma once
#include "BoxMan.h"

class CBoxManWnd : public CWnd
{
	DECLARE_DYNCREATE(CBoxManWnd)
public:
	CBoxManWnd();
	~CBoxManWnd();
public:
	CBoxMan m_boxMan;
	CMenu *m_pSubMenu;
	BOOL m_bSound;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnMenuGameMusic();
	afx_msg void OnMenuLoadMap();
};

