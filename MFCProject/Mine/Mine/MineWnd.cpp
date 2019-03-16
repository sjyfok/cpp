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
	GetClientRect(&m_rcClient);
	m_uBtnRect[0] = m_rcClient.right / 2 - 12;
	m_uBtnRect[1] = m_rcClient.right / 2 - 13;
	m_uBtnRect[2] = m_rcClient.right / 2 + 12;

}
BEGIN_MESSAGE_MAP(CMineWnd, CWnd)
	ON_COMMAND(ID_MENU_PRIMARY, &CMineWnd::OnMenuPrimary)
	ON_COMMAND(ID_MENU_COLOR, &CMineWnd::OnMenuColor)
	ON_COMMAND(ID_MENU_SOUND, &CMineWnd::OnMenuSound)
	ON_COMMAND(ID_MENU_ABOUT, &CMineWnd::OnMenuAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
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

WINEWND* CMineWnd::GetMine(long x, long y)
{
	if (x < MINEAREA_FRAME_X || y < MINEAREA_FRAME_Y)
	{
		return NULL;
	}
	UINT uCol = (UINT)(x - MINEAREA_FRAME_X) / 16;
	UINT uRow = (UINT)(y - MINEAREA_FRAME_Y) / 16;
	return &m_pMines[uRow][uCol];
}

void CMineWnd::LoadBitmap()
{
	if (m_bColorful)
	{
		m_clrDark = COLOR_DARK_GRAY;
		m_bmpMine.DeleteObject();
		m_bmpMine.LoadBitmap(IDB_MINE_COLOR);
		m_bmpNumber.DeleteObject();
		m_bmpNumber.LoadBitmap(IDB_NUM_COLOR);
		m_bmpButton.DeleteObject();
		m_bmpButton.LoadBitmap(IDB_BTN_COLOR);
	}
	else
	{
		m_clrDark = COLOR_BLACK;
		m_bmpMine.DeleteObject();
		m_bmpMine.LoadBitmap(IDB_MINE_GRAY);
		m_bmpNumber.DeleteObject();
		m_bmpNumber.LoadBitmap(IDB_NUM_GRAY);
		m_bmpButton.DeleteObject();
		m_bmpButton.LoadBitmap(IDB_BTN_GRAY);
	}
}

void CMineWnd::InitGame()
{
	LoadBitmap();
	m_nLeaveNum = m_uMineNum;
	m_uSleepTime = 0;
	m_uBtnState = BUTTON_NORMAL;
	m_uGameState = GS_WAIT;

	if (m_uTimer)
	{
		KillTimer(ID_TIMER_EVENT);
		m_uTimer = 0;
	}

	m_pNewMine = NULL;
	m_pOldMine = NULL;

	FreeMines();
	for (UINT i = 0; i < m_uYNum; i++)
	{
		for (UINT j = 0; j < m_uXNum; j++)
		{
			m_pMines[i][j].uRow = i;
			m_pMines[i][j].uCol = j;
			m_pMines[i][j].uState = STATE_NORMAL;
			m_pMines[i][j].uAttrib = ATTRIB_EMPTY;
			m_pMines[i][j].uOldState = STATE_NORMAL;
		}
	}
}

void CMineWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39); //中间的笑脸
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
				m_bLRBtnDown = FALSE;
				OnLRBtnUp(m_pOldMine->uRow, m_pOldMine->uCol);
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


BOOL CMineWnd::IsMine(UINT row, UINT col)
{
	// TODO: 在此处添加实现代码.
	return (m_pMines[row][col].uAttrib == ATTRIB_MINE);
}


UINT CMineWnd::GetAroundNum(UINT row, UINT col)
{
	// TODO: 在此处添加实现代码.
	UINT i, j;
	UINT around = 0;
	UINT minRow = (row == 0) ? 0 : row - 1;
	UINT maxRow = row + 2;
	UINT minCol = (col == 0) ? 0 : col - 1;
	UINT maxCol = col + 2;
	for (i = minRow; i < maxRow; i++)
	{
		for (j = minCol; j < maxCol; j++)
		{
			if (!IsInMineArea(i, j))
			{
				continue;
			}
			if (m_pMines[i][j].uAttrib == ATTRIB_MINE)
			{
				around++;
			}
		}
	}
	return around;
}


void CMineWnd::ExPandMines(UINT row, UINT col)
{
	// TODO: 在此处添加实现代码.
	UINT i, j;
	UINT minRow = (row == 0) ? 0 : row - 1;
	UINT maxRow = row + 2;
	UINT minCol = (col == 0) ? 0 : col - 1;
	UINT maxCol = col + 2;
	UINT around = GetAroundNum(row, col);
	
	m_pMines[row][col].uState = 15 - around;
	m_pMines[row][col].uOldState = 15 - around;

	DrawSpecialMine(row, col);
	if (around == 0)
	{
		for (i = minRow; i < maxRow; i++)
		{
			for (j = minCol; j < maxCol; j++)
			{
				if (!(i == row && j == col)&&m_pMines[i][j].uState == STATE_NORMAL
					&&m_pMines[i][j].uAttrib != ATTRIB_MINE)
				{
					if (!IsInMineArea(i, j))
					{
						continue;
					}
					ExPandMines(i, j);
				}
			}
		}
	}
}



BOOL CMineWnd::Victory()
{
	// TODO: 在此处添加实现代码.
	UINT i, j;
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	for (i = 0; i < m_uYNum; i++)
	{
		for (j = 0; j  < m_uXNum; j ++)
		{
			if (m_pMines[i][j].uState == STATE_NORMAL)
			{
				return FALSE;
			}
			if (m_pMines[i][j].uState == STATE_DICEY)
			{
				return FALSE;
			}
		}
	}
	m_uBtnState = BUTTON_VICTORY;
	m_uGameState = GS_VICTORY;
	Invalidate();
	if (m_uTimer != 0)
	{
		KillTimer(ID_TIMER_EVENT);
		m_uTimer = 0;
	}
	return TRUE;
}


void CMineWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
		MINE_AREA_LEFT + m_uXNum * MINE_WIDTH,
		MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);
	if (rcMineArea.PtInRect(point))
	{
		if (m_uGameState == GS_WAIT||m_uGameState == GS_RUN)
		{

		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}
