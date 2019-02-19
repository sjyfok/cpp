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
	ON_COMMAND(ID_MENU_COLOR, &CMineWnd::OnMenuColor)
	ON_COMMAND(ID_MENU_SOUND, &CMineWnd::OnMenuSound)
	ON_COMMAND(ID_MENU_ABOUT, &CMineWnd::OnMenuAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CMineWnd::OnMenuPrimary()
{
	// TODO: 在此添加命令处理程序代码
	m_uXNum = PRIMARY_XNUM;
	m_uYNum = PRIMARY_YNUM;

	SizeWindow();
}


void CMineWnd::OnMenuColor()
{
	// TODO: 在此添加命令处理程序代码
}


void CMineWnd::OnMenuSound()
{
	// TODO: 在此添加命令处理程序代码
}


void CMineWnd::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	ShellAbout(this->m_hWnd, _T("扫雷"), _T("songjyf@126.com"), NULL);
}


void CMineWnd::LayMines(UINT row, UINT col)
{
	// TODO: 在此处添加实现代码.
	srand((unsigned)time(NULL));
	UINT i, j;
	for (UINT index = 0; index < m_uMineNum;) 
	{
		i = rand() % m_uYNum;
		j = rand() % m_uXNum;
		if (i == row && j == col)
		{
			continue;
		}
		if (m_pMines[i][j].uAttrib != ATTRIB_MINE)
		{
			m_pMines[i][j].uAttrib = ATTRIB_MINE;
			index++;
		}
	}
}


void CMineWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CMineWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
		MINE_AREA_LEFT + m_uXNum * MINE_WIDTH,
		MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);
	if (rcBtn.PtInRect(point))
	{
		Invalidate();
		InitGame();
	}
	else if (rcMineArea.PtInRect(point))
	{
		CString value;
		UINT around = 0;
		switch (m_uGameState)
		{
		case GS_WAIT:
		case GS_RUN:
			m_pOldMine = GetMine(point.x, point.y);
			if (!m_pOldMine)
			{
				ReleaseCapture();
				return;
			}
			if (m_bLRBtnDown)
			{

			}
			else
			{
				if (m_uGameState == GS_WAIT)
				{
					if (m_uTimer)
					{
						KillTimer(ID_TIMER_EVENT);
						m_uTimer = 0;
					}
					m_uSpendTime = 1;
					Invalidate();
					m_uTimer = SetTimer(ID_TIMER_EVENT, 1000, NULL);
					LayMines(m_pOldMine->uRow, m_pOldMine->uCol);
					m_uGameState = GS_RUN;
				}
			}
			if (m_pOldMine->uOldState == STATE_NORMAL)
			{
				if (IsMine(m_pOldMine->uRow, m_pOldMine->uCol))
				{
					Dead(m_pOldMine->uRow, m_pOldMine->uCol);
					ReleaseCapture();
					return;
				}
				around = GetAroundNum(m_pOldMine->uRow, m_pOldMine->uCol);
				if (around == 0)
				{
					ExpandMines(m_pOldMine->uRow, m_pOldMine->uCol);
				}
				else
				{
					DrawDownNum(m_pOldMine, around);
				}
				if (Victory())
				{
					Invalidate();
					ReleaseCapture();
					return;
				}
			}
			break;
		case GS_VICTORY:
		case GS_DEAD:
			ReleaseCapture();
			return;
		default:
			break;
		}
		m_uBtnState = BUTTON_NORMAL;
		Invalidate();
	}
	else
	{
		if (m_uGameState == GS_WAIT || m_uGameState == GS_RUN)
		{
			m_uBtnState = BUTTON_NORMAL;
			InvalidateRect(rcBtn);
		}
	}
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}
