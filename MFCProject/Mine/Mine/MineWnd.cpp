#include "stdafx.h"
#include "MineWnd.h"
#include "MineDefs.h"
#include "resource.h"

CMineWnd::CMineWnd()
{
}


CMineWnd::~CMineWnd()
{
}


void CMineWnd::SizeWindow()
{
	// TODO: 在此处添加实现代码.
	UINT uWidth = DEFAULT_FRAME_X + m_uXNum * MINE_WIDTH +
		LINE_WIDTH_0 * 3 + SIDE_WIDTH_0 + SIDE_WIDTH_1;
	UINT uHeight = DEFAULT_FRAME_Y + m_uYNum * MINE_HEIGHT +
		LINE_WIDTH_0 * 3 + SIDE_WIDTH_0 * 2 + SIDE_WIDTH_1 + SHELL_S_H;
	SetWindowPos(&wndTopMost, 0, 0, uWidth, uHeight,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
}
BEGIN_MESSAGE_MAP(CMineWnd, CWnd)
	ON_COMMAND(ID_MENU_PRIMARY, &CMineWnd::OnMenuPrimary)
END_MESSAGE_MAP()


void CMineWnd::OnMenuPrimary()
{
	// TODO: 在此添加命令处理程序代码
	m_uXNum = PRIMARY_XNUM;
	m_uYNum = PRIMARY_YNUM;

	SizeWindow();
}
