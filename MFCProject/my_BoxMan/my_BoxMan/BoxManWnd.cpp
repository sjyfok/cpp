#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManWnd.h"
#include "resource.h"
#include "LoadMapDlg.h"

IMPLEMENT_DYNCREATE(CBoxManWnd, CWnd)

CBoxManWnd::CBoxManWnd()
{
}


CBoxManWnd::~CBoxManWnd()
{
}
BEGIN_MESSAGE_MAP(CBoxManWnd, CWnd)
	ON_WM_KEYDOWN()
	ON_WM_INITMENU()
	ON_COMMAND(ID_MENU_GAME_MUSIC, &CBoxManWnd::OnMenuGameMusic)
	ON_COMMAND(ID_MENU_LOAD_MAP, &CBoxManWnd::OnMenuLoadMap)
END_MESSAGE_MAP()


void CBoxManWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_boxMan.KeyDown(nChar, nRepCnt, nFlags);
	Invalidate(FALSE);
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CBoxManWnd::OnInitMenu(CMenu* pMenu)
{
	CWnd::OnInitMenu(pMenu);

	// TODO: 在此处添加消息处理程序代码
	if ((m_pSubMenu = pMenu->GetSubMenu(0)) == 0)
	{
		AfxMessageBox(_T("初始化菜单失败"));
		PostQuitMessage(0);
	}
}


void CBoxManWnd::OnMenuGameMusic()
{
	// TODO: 在此添加命令处理程序代码
	m_bSound = (!m_bSound);
	m_boxMan.IsSound(m_bSound);
	if (m_pSubMenu)
	{
		if (m_bSound == TRUE)
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_CHECKED|MF_BYCOMMAND);
		}
		else
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_UNCHECKED | MF_BYCOMMAND);
		}
	}
}


void CBoxManWnd::OnMenuLoadMap()
{
	// TODO: 在此添加命令处理程序代码
	CLoadMapDlg loadMapDlg;
	if (loadMapDlg.DoModal() == IDOK)
	{
		int iMissionNum = loadMapDlg.m_iMisslionLev;
		m_boxMan.ChangeMissionNum(iMissionNum);
		Invalidate(FALSE);
	}
}
