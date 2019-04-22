#include "stdafx.h"

#include "MineWnd.h"
#include "MineDefs.h"
#include "Mmsystem.h"
#include "resource.h"
#include "DlgCustom.h"
#include "DlgHero.h"
#pragma comment(lib, "winmm")

#define ID_TIMER_EVENT WM_USER+1

CMineWnd::CMineWnd()
{
	m_pSndDead = NULL;
	m_pSndVictory = NULL;
	m_pSndClock = NULL;
	m_uTimer = 0;
	m_brsBG.CreateSolidBrush(COLOR_GRAY);

	LoadConfig();
	if (m_bSoundful)
		LoadWaveSrc();
	InitGame();
}


CMineWnd::~CMineWnd()
{
}



BEGIN_MESSAGE_MAP(CMineWnd, CWnd)
	ON_COMMAND(ID_MENU_PRIMARY, &CMineWnd::OnMenuPrimary)
	ON_COMMAND(ID_MENU_COLOR, &CMineWnd::OnMenuColor)
	ON_COMMAND(ID_MENU_SOUND, &CMineWnd::OnMenuSound)
	ON_COMMAND(ID_MENU_ABOUT, &CMineWnd::OnMenuAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_MENU_START, &CMineWnd::OnMenuStart)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_INITMENU()
	ON_COMMAND(ID_MENU_SECOND, &CMineWnd::OnMenuSecond)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_ADVANCE, &CMineWnd::OnMenuAdvance)
	ON_COMMAND(ID_MENU_CUSTOM, &CMineWnd::OnMenuCustom)
	ON_COMMAND(ID_MENU_EXIT, &CMineWnd::OnMenuExit)
	ON_COMMAND(ID_MENU_HELP_USE, &CMineWnd::OnMenuHelpUse)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENU_HERO, &CMineWnd::OnMenuHero)
END_MESSAGE_MAP()


void CMineWnd::LoadConfig()
{
	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	//-----------------------------------*/	
	strPath += "\\config.ini";

	TCHAR strPrimary[80];
	TCHAR strSecond[80];
	TCHAR strAdvance[80];

	m_uXNum = GetPrivateProfileInt(_T("WINDOW"), _T("XNum"), 10, strPath);
	m_uYNum = GetPrivateProfileInt(_T("WINDOW"), _T("YNum"), 10, strPath);

	m_uMineNum = GetPrivateProfileInt(_T("MINE"), _T("MineNum"), 10, strPath);
	m_uLevel = GetPrivateProfileInt(_T("MINE"), _T("Level"), 0, strPath);

	m_uPrimary = GetPrivateProfileInt(_T("SCORE"), _T("Primary"), 999, strPath);
	m_uSecond = GetPrivateProfileInt(_T("SCORE"), _T("Second"), 999, strPath);
	m_uAdvance = GetPrivateProfileInt(_T("SCORE"), _T("Advance"), 999, strPath);

	GetPrivateProfileString(_T("HOLDER"), _T("PrimaryHolder"), _T("匿名"), strPrimary, 80, strPath);
	GetPrivateProfileString(_T("HOLDER"), _T("SecondHolder"), _T("匿名"), strSecond, 80, strPath);
	GetPrivateProfileString(_T("HOLDER"), _T("AdvanceHolder"), _T("匿名"), strAdvance, 80, strPath);

	m_szPrimary = strPrimary;
	m_szSecond = strSecond;
	m_szAdvance = strAdvance;

	m_bMarkful = GetPrivateProfileInt(_T("CONFIG"), _T("Markful"), 0, strPath);
	m_bColorful = GetPrivateProfileInt(_T("CONFIG"), _T("Colorful"), 1, strPath);
	m_bSoundful = GetPrivateProfileInt(_T("CONFIG"), _T("Soundful"), 1, strPath);
}

void CMineWnd::SaveConfig()
{
	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));

	strPath += _T("\\config.ini");

	CString strXNum, strYNum;
	CString strMineNum, strLevel;
	CString strPrimary, strSecond, strAdvance;
	CString strPrimaryHolder, strSecondHolder, strAdvanceHolder;
	CString strMarkful, strColorful, strSoundful;

	strXNum.Format(_T("%u"), m_uXNum);
	strYNum.Format(_T("%u"), m_uYNum);

	strMineNum.Format(_T("%u"), m_uMineNum);
	strLevel.Format(_T("%u"), m_uLevel);
	
	strPrimary.Format(_T("%u"), m_uPrimary);
	strSecond.Format(_T("%u"), m_uSecond);
	strAdvance.Format(_T("%u"), m_uAdvance);

	strPrimaryHolder.Format(_T("%s"), m_szPrimary);
	strSecondHolder.Format(_T("%s"), m_szSecond);
	strAdvanceHolder.Format(_T("%s"), m_szAdvance);

	strMarkful.Format(_T("%d"), m_bMarkful);
	strColorful.Format(_T("%d"), m_bColorful);
	strSoundful.Format(_T("%d"), m_bSoundful);

	WritePrivateProfileString(_T("WINDOW"), _T("XNum"), strXNum, strPath);
	WritePrivateProfileString(_T("WINDOW"), _T("YNum"), strYNum, strPath);

	WritePrivateProfileString(_T("MINE"), _T("MineNum"), strMineNum, strPath);
	WritePrivateProfileString(_T("MINE"), _T("Level"), strLevel, strPath);

	WritePrivateProfileString(_T("SCORE"), _T("Primary"), strPrimary, strPath);
	WritePrivateProfileString(_T("SCORE"), _T("Second"), strSecond, strPath);
	WritePrivateProfileString(_T("SCORE"), _T("Advance"), strAdvance, strPath);

	WritePrivateProfileString(_T("HOLDER"), _T("PrimaryHolder"), strPrimaryHolder, strPath);
	WritePrivateProfileString(_T("HOLDER"), _T("SecondHolder"), strSecondHolder, strPath);
	WritePrivateProfileString(_T("HOLDER"), _T("AdvanceHolder"), strAdvanceHolder, strPath);

	WritePrivateProfileString(_T("CONFIG"), _T("Markful"), strMarkful, strPath);
	WritePrivateProfileString(_T("CONFIG"), _T("Colorful"), strColorful, strPath);
	WritePrivateProfileString(_T("CONFIG"), _T("Soundful"), strSoundful, strPath);
}

void CMineWnd::LoadWaveSrc()
{
	HMODULE hMdl;
	hMdl = AfxGetResourceHandle();
	HRSRC hSrc;

	hSrc = FindResource(hMdl, MAKEINTRESOURCE(IDR_WAVE_DEAD), _T("WAVE"));
	m_pSndDead = LoadResource(hMdl, hSrc);
	hSrc = FindResource(hMdl, MAKEINTRESOURCE(IDR_WAVE_VICTORY), _T("WAVE"));
	m_pSndVictory = LoadResource(hMdl, hSrc);
	hSrc = FindResource(hMdl, MAKEINTRESOURCE(IDR_WAVE_CLOCK), _T("WAVE"));
	m_pSndClock = LoadResource(hMdl, hSrc);
}

void CMineWnd::SetCheckedColor()
{
	if (m_pSubMenu)
	{
		if (m_bColorful)
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_COLOR, MF_CHECKED | MF_BYCOMMAND);
		}
		else
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_COLOR, MF_CHECKED | MF_BYCOMMAND);
		}
	}
}

void CMineWnd::SetCheckedSound()
{
	if (m_pSubMenu)
	{
		if (m_bSoundful)
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_SOUND, MF_CHECKED | MF_BYCOMMAND);
		}
		else
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_SOUND, MF_CHECKED | MF_BYCOMMAND);
		}
	}
}

void CMineWnd::SetCheckedMark()
{
	if (m_pSubMenu)
	{
		if (m_bMarkful)
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_MARK, MF_CHECKED | MF_BYCOMMAND);
		}
		else
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_MARK, MF_CHECKED | MF_BYCOMMAND);
		}
	}
}


void CMineWnd::SetCheckedLevel()
{
	if (m_pSubMenu)
	{
		m_pSubMenu->CheckMenuItem(ID_MENU_PRIMARY, MF_UNCHECKED | MF_BYCOMMAND);
		m_pSubMenu->CheckMenuItem(ID_MENU_SECOND, MF_UNCHECKED | MF_BYCOMMAND);
		m_pSubMenu->CheckMenuItem(ID_MENU_ADVANCE, MF_UNCHECKED | MF_BYCOMMAND);
		m_pSubMenu->CheckMenuItem(ID_MENU_CUSTOM, MF_UNCHECKED | MF_BYCOMMAND);		
	}
	switch (m_uLevel)
	{
	default:
		break;
	case LEVEL_PRIMARY:
		m_pSubMenu->CheckMenuItem(ID_MENU_PRIMARY, MF_CHECKED | MF_BYCOMMAND);
		break;
	case LEVEL_SECONDRY:
		m_pSubMenu->CheckMenuItem(ID_MENU_SOUND, MF_CHECKED | MF_BYCOMMAND);
		break;
	case LEVEL_ADVANCE:
		m_pSubMenu->CheckMenuItem(ID_MENU_ADVANCE, MF_CHECKED | MF_BYCOMMAND);
		break;
	case LEVEL_CUSTOM:
		m_pSubMenu->CheckMenuItem(ID_MENU_CUSTOM, MFS_CHECKED | MF_BYCOMMAND);
		break;
	}
}

void CMineWnd::OnMenuPrimary()
{
	// TODO: 在此添加命令处理程序代码
	m_uLevel = LEVEL_PRIMARY;
	m_uXNum = PRIMARY_XNUM;
	m_uYNum = PRIMARY_YNUM;
	m_uMineNum = PRIMARY_MINENUM;

	SetCheckedLevel();
	InitGame();
	Invalidate();
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



MINEWND* CMineWnd::GetMine(long x, long y)
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

void CMineWnd::FreeMines()
{

}

void CMineWnd::SizeWindow(void)
{
	UINT uWidth = DEFAULT_FRAME_X + m_uXNum * MINE_WIDTH +
		LINE_WIDTH_0 * 3 + SIDE_WIDTH_0 *2 + SIDE_WIDTH_1*2;
	UINT uHeight = DEFAULT_FRAME_Y + m_uYNum * MINE_HEIGHT +
		LINE_WIDTH_0 * 3 + SIDE_WIDTH_0 * 2 + SIDE_WIDTH_1*2 + SHELL_S_H;

	SetWindowPos(&wndTopMost, 0, 0, uWidth, uHeight,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);

	GetClientRect(&m_rcClient);
	m_uBtnRect[0] = m_rcClient.right / 2 - 12;
	m_uBtnRect[1] = m_rcClient.right / 2 - 13;
	m_uBtnRect[2] = m_rcClient.right / 2 + 12;

	m_uNumRect[0] = m_rcClient.right - 55;
	m_uNumRect[1] = m_rcClient.right - 15;
	m_uNumRect[2] = m_rcClient.right - 54;


	m_uShellRcX[0] = m_rcClient.right;
	m_uShellRcX[1] = m_rcClient.right - 14;

	m_uShellRcY[0] = m_rcClient.bottom;
	m_uShellRcY[1] = m_rcClient.bottom - SHELL_L_START_Y - 5;
}

BOOL CMineWnd::IsInMineArea(UINT row, UINT col)
{
	return (row >= 0 && row < m_uYNum && col >= 0 && col < m_uXNum);
}

void CMineWnd::OnLRBtnDown(UINT row, UINT col)
{
	UINT i, j;
	UINT minRow = (row == 0) ? 0 : (row - 1);
	UINT maxRow = row + 2;
	UINT minCol = (col == 0) ? 0 : (col - 1);
	UINT maxCol = col + 2;

	for (i = minRow; i < maxRow; i++)
	{
		for (j = minCol; j < maxCol; j++)
		{
			if (!IsInMineArea(i, j))
			{
				continue;
			}
			if (m_pMines[i][j].uState == STATE_NORMAL)
			{
				m_pMines[i][j].uState = STATE_EMPTY;
			}
			else if (m_pMines[i][j].uState == STATE_DICEY)
			{
				m_pMines[i][j].uState = STATE_DICEY_DOWN;
			}
		}
	}
}

void CMineWnd::OnLRBtnUp(UINT row, UINT col)
{
	UINT i, j;
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
			if (m_pMines[i][j].uOldState == STATE_NORMAL)
			{
				m_pMines[i][j].uState = STATE_NORMAL;
			}
			else if (m_pMines[i][j].uOldState == STATE_DICEY)
			{
				m_pMines[i][j].uState = STATE_DICEY;
			}
		}
	}
}


void CMineWnd::InitGame()
{
	LoadBitmap();
	m_nLeaveNum = m_uMineNum;
	m_uSpendTime = 0;
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

void CMineWnd::Dead(UINT row, UINT col)
{
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
		MINE_AREA_LEFT + m_uXNum * MINE_WIDTH,
		MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);

	UINT i, j;
	if (m_pMines[row][col].uAttrib == ATTRIB_MINE)
	{
		for (i = 0; i < m_uYNum; i++)
		{
			for (j = 0; j < m_uXNum; j++)
			{
				m_pMines[row][col].uState = STATE_BLAST;
				m_pMines[row][col].uOldState = STATE_BLAST;
				if (m_pMines[i][j].uAttrib == ATTRIB_MINE
					&& m_pMines[i][j].uState != STATE_FLAG)
				{
					m_pMines[i][j].uState = STATE_MINE;
					m_pMines[i][j].uOldState = STATE_MINE;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < m_uYNum; i++)
		{
			for (j = 0; j  < m_uXNum; j ++)
			{
				m_pMines[row][col].uState = STATE_ERROR;
				m_pMines[row][col].uOldState = STATE_ERROR;
				if (m_pMines[i][j].uAttrib == ATTRIB_MINE && m_pMines[i][j].uState != STATE_FLAG)
				{
					m_pMines[i][j].uState = STATE_MINE;
					m_pMines[i][j].uOldState = STATE_MINE;
				}
			}
		}
	}
	InvalidateRect(rcMineArea);
	m_uBtnState = BUTTON_DEAD;
	InvalidateRect(rcBtn);
	m_uGameState = GS_DEAD;
}

void CMineWnd::DrawDownNum(MINEWND *mine, UINT num)
{
	mine->uState = 15 - num;
	mine->uOldState = 15 - num;
	CRect rcMine(mine->uCol * 16, mine->uRow * 16, (mine->uCol + 1) * 16, (mine->uRow + 1) * 16);
	InvalidateRect(rcMine);
}

void CMineWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
		MINE_AREA_LEFT + m_uXNum * MINE_WIDTH, MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);
	SetCapture();
	m_bClickBtn = FALSE;
	m_bLRBtnDown = FALSE;

	if (rcBtn.PtInRect(point))
	{
		m_bClickBtn = TRUE;
		m_uBtnState = BUTTON_DOWN;
		InvalidateRect(rcBtn);
	}
	else if (rcMineArea.PtInRect(point))
	{
		switch (m_uGameState)
		{
		default:
			break;
		case GS_WAIT:
		case GS_RUN:
			m_pNewMine = GetMine(point.x, point.y);
			if (!m_pNewMine)
			{
				return;
			}
			if (m_pNewMine->uState == STATE_NORMAL)
			{
				m_pNewMine->uState = STATE_EMPTY;
			}
			if (m_pNewMine->uState == STATE_DICEY)
			{
				m_pNewMine->uState = STATE_DICEY_DOWN;
			}
			m_pOldMine = m_pNewMine;
			break;
		case GS_DEAD:
		case GS_VICTORY:
			return;
			break;
		}
		m_uBtnState = BUTTON_CLICK;
		InvalidateRect(rcBtn);
		if (nFlags == (MK_LBUTTON | MK_RBUTTON))
		{
			m_bLRBtnDown = TRUE;
			OnLRBtnDown(m_pOldMine->uRow, m_pOldMine->uCol);
		}
		InvalidateRect(rcMineArea);
	}
	else
	{
		if (m_uGameState == GS_WAIT || m_uGameState == GS_RUN)
		{
			m_uBtnState = BUTTON_CLICK;
			InvalidateRect(rcBtn);
		}
	}



	CWnd::OnLButtonDown(nFlags, point);
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

void CMineWnd::DrawSpecialMine(UINT row, UINT col)
{
	CRect rcMine(col * 16, row * 16, (col + 1) * 16, (row + 1) * 16);
	InvalidateRect(rcMine);
}

void CMineWnd::ExpandMines(UINT row, UINT col)
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
					ExpandMines(i, j);
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

	m_bLRBtnDown = FALSE;

	if (rcMineArea.PtInRect(point))
	{
		if (m_uGameState == GS_WAIT||m_uGameState == GS_RUN)
		{
			m_pNewMine = GetMine(point.x, point.y);
			if (!m_pNewMine)
			{
				return ;
			}
			if (nFlags == (MK_LBUTTON|MK_RBUTTON))
			{
				m_bLRBtnDown = TRUE;
				OnLRBtnDown(m_pNewMine->uRow, m_pNewMine->uCol);
			}
			else
			{
				switch (m_pNewMine->uState)
				{
				default:
					break;
				case STATE_NORMAL:
					m_pNewMine->uState = STATE_FLAG;
					m_pNewMine->uOldState = STATE_FLAG;
					m_nLeaveNum--;
					break;
				case STATE_FLAG:
					m_pNewMine->uState = STATE_DICEY;
					m_pNewMine->uOldState = STATE_DICEY;
					m_nLeaveNum++;
					break;
				case STATE_DICEY:
					m_pNewMine->uState = STATE_NORMAL;
					m_pNewMine->uOldState = STATE_NORMAL;
					break;
				}
			}
			Invalidate();
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}



void CMineWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	SizeWindow();
	CWnd::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}


void CMineWnd::OnMenuStart()
{
	// TODO: 在此添加命令处理程序代码
	InitGame();
	Invalidate();
}


void CMineWnd::DrawButton(CPaintDC &dc)
{
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(m_bmpButton);
	dc.StretchBlt(m_uBtnRect[0], 16, 24, 24, &cdc, 0, 24 * m_uBtnState, 24, 24, SRCCOPY);

	dc.Draw3dRect(m_uBtnRect[1], 15, 26, 26, m_clrDark, m_clrDark);
}

void CMineWnd::DrawNumber(CPaintDC &dc)
{
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	dcMemory.SelectObject(m_bmpNumber);

	dc.Draw3dRect(16, 15, 41, 25, m_clrDark, COLOR_WHITE);
	dc.Draw3dRect(m_uNumRect[0], 15, 41, 25, m_clrDark, COLOR_WHITE);
	int num;

	num = (m_nLeaveNum < 0) ? 11 : m_nLeaveNum / 100;
	dc.StretchBlt(17, 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);
	num = (m_nLeaveNum < 0) ? -(m_nLeaveNum - num * 100) / 10 : (m_nLeaveNum - num * 100) / 10;
	dc.StretchBlt(30, 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);
	num = (m_nLeaveNum<0) ? -m_nLeaveNum % 10 : m_nLeaveNum % 10;
	dc.StretchBlt(43, 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);

	num = m_uSpendTime / 100;
	dc.StretchBlt(m_uNumRect[0], 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);
	num = (m_uSpendTime - num * 100) / 10;
	dc.StretchBlt(m_uNumRect[0] + 13, 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);
	num = m_uSpendTime % 10;
	dc.StretchBlt(m_uNumRect[0] + 26, 16, 13, 23, &dcMemory, 0, 276 - 23 * (num + 1), 13, 23, SRCCOPY);

}

void CMineWnd::DrawShell(CPaintDC &dc)
{
	dc.FillSolidRect(0, 0, m_uShellRcX[0], LINE_WIDTH_0, COLOR_WHITE);
	dc.FillSolidRect(0, 0, LINE_WIDTH_0, m_uShellRcY[0], COLOR_WHITE);

	dc.Draw3dRect(SHELL_S_START_X, SHELL_S_START_Y,
		m_uShellRcX[1], SHELL_S_H, m_clrDark, COLOR_WHITE);
	dc.Draw3dRect(SHELL_S_START_X + 1, SHELL_S_START_Y + 1,
		m_uShellRcX[1] - 2, SHELL_S_H - 2, m_clrDark, COLOR_WHITE);

	dc.Draw3dRect(SHELL_L_START_X, SHELL_L_START_Y,
		m_uShellRcX[1], m_uShellRcY[1], m_clrDark, COLOR_WHITE);
	dc.Draw3dRect(SHELL_L_START_X + 1, SHELL_L_START_Y + 1,
		m_uShellRcX[1] - 2, m_uShellRcY[1] - 2, m_clrDark, COLOR_WHITE);
	dc.Draw3dRect(SHELL_L_START_X + 2, SHELL_L_START_Y + 2,
		m_uShellRcX[1] - 4, m_uShellRcY[1] - 4, m_clrDark, COLOR_WHITE);
}

void CMineWnd::DrawMineArea(CPaintDC &dc)
{
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	dcMemory.SelectObject(m_bmpMine);

	for (UINT i = 0; i < m_uYNum; i++)
	{
		for (UINT j = 0; j < m_uXNum; j++)
		{
			dc.StretchBlt(MINEAREA_FRAME_X + 16 * j, MINEAREA_FRAME_Y + 16 * i,
				16, 16, &dcMemory, 0, 16 * m_pMines[i][j].uState, 16, 16, SRCCOPY);
		}
	}
}

void CMineWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	CDC dcMemroy;

	CBitmap bitmap;
	if (!dc.IsPrinting())
	{
		if (dcMemroy.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right, m_rcClient.bottom))
			{
				dcMemroy.SelectObject(&bitmap);
				dcMemroy.FillRect(&m_rcClient, &m_brsBG);
				DrawButton((CPaintDC&)dcMemroy);
				DrawNumber((CPaintDC&)dcMemroy);
				DrawShell((CPaintDC&)dcMemroy);
				DrawMineArea((CPaintDC&)dcMemroy);

				dc.BitBlt(m_rcClient.left, m_rcClient.top,
					m_rcClient.right, m_rcClient.bottom, &dcMemroy, 0, 0, SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}
}


void CMineWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER_EVENT)
	{
		if (m_bSoundful)
		{
			sndPlaySound((LPCTSTR)LockResource(m_pSndClock), SND_MEMORY
				| SND_ASYNC | SND_NODEFAULT);
		}
		m_uSpendTime++;
		CRect rcNum(m_uNumRect[0], 15, m_uNumRect[1], 39);
		Invalidate();
		if (m_uSpendTime >= DEFAULT_RECORD)
		{
			KillTimer(ID_TIMER_EVENT);
			m_uTimer = 0;
		}
	}
	CWnd::OnTimer(nIDEvent);
}

void CMineWnd::OpenAround(UINT row, UINT col)
{
	if (GetAroundFlags(row, col) != GetAroundNum(row, col))
	{
		return;
	}
	UINT i, j;
	UINT around = 0;
	UINT minRow = (row == 0) ? 0 : row - 1;
	UINT maxRow = row + 2;
	UINT minCol = (col == 0) ? 0 : col - 1;
	UINT maxCol = col + 2;

	for (i = minRow; i < maxRow; i++)
	{
		for (j = 0; j < maxCol; j++)
		{
			if (!IsInMineArea(i, j))
			{
				continue;
			}
			if (m_pMines[i][j].uState == STATE_NORMAL)
			{
				ExpandMines(i, j);
				around = GetAroundNum(i, j);
				m_pMines[i][j].uState = 15 - around;
				m_pMines[i][j].uOldState = 15 - around;
			}
		}
	}

	if (Victory())
	{
		for (i = 0; i < m_uYNum; i++)
		{
			for (j = 0; j < m_uXNum; j++)
			{
				if (m_pMines[i][j].uAttrib == ATTRIB_MINE)
				{
					m_pMines[i][j].uState = STATE_FLAG;
					m_pMines[i][j].uOldState = STATE_FLAG;
				}
			}
		}
		m_nLeaveNum = 0;
		Invalidate();
	}
}

UINT CMineWnd::GetAroundFlags(UINT row, UINT col)
{
	UINT i, j;
	UINT flags = 0;
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
			if (m_pMines[i][j].uState == STATE_FLAG)
			{
				flags++;
			}
		}
	}
	return flags;
}

BOOL CMineWnd::ErrorAroundFlag(UINT row, UINT col)
{
	if (GetAroundFlags(row, col) != GetAroundNum(row, col))
	{
		return FALSE;
	}

	int i, j;
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
			if (m_pMines[i][j].uState == STATE_FLAG)
			{
				if (m_pMines[i][j].uAttrib != ATTRIB_MINE)
				{
					Dead(i, j);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CMineWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
	CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
		MINE_AREA_LEFT + m_uXNum * MINE_WIDTH, MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);

	m_pOldMine = GetMine(point.x, point.y);
	if (!m_pOldMine)
	{
		return;
	}
	if (m_bLRBtnDown)
	{
		m_bLRBtnDown = FALSE;
		OnLRBtnUp(m_pOldMine->uRow, m_pOldMine->uCol);
		if (m_uGameState == GS_WAIT)
		{
			m_uBtnState = BUTTON_NORMAL;
			Invalidate();
			return;
		}
		if (m_pOldMine->uState != STATE_FLAG)
		{
			OpenAround(m_pOldMine->uRow, m_pOldMine->uCol);
		}
		if (ErrorAroundFlag(m_pOldMine->uRow, m_pOldMine->uCol))
		{
			return;
		}
	}
	else
	{
		Victory();
	}
	CWnd::OnRButtonUp(nFlags, point);
}


void CMineWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_LBUTTON || nFlags == (MK_LBUTTON|MK_RBUTTON))
	{
		CRect rcBtn(m_uBtnRect[1], 15, m_uBtnRect[2], 39);
		CRect rcMineArea(MINE_AREA_LEFT, MINE_AREA_TOP,
			MINE_AREA_LEFT + m_uXNum * MINE_WIDTH, MINE_AREA_TOP + m_uYNum * MINE_HEIGHT);

		if (rcBtn.PtInRect(point))
		{
			switch (m_uGameState)
			{
			default:
				break;
			case GS_RUN:
				m_uBtnState = (m_bClickBtn) ? BUTTON_DOWN : BUTTON_CLICK;
				break;
			case GS_DEAD:
			case GS_VICTORY:
				if (m_bClickBtn)
				{
					m_uBtnState = BUTTON_DOWN;
				}
				break;
			}
			InvalidateRect(rcBtn);
		}
		else if (rcMineArea.PtInRect(point))
		{
			switch (m_uGameState)
			{
			default:
				break;
			case GS_RUN:
				m_pNewMine = GetMine(point.x, point.y);
				if (!m_pNewMine || !m_pOldMine)
				{
					return;
				}
				if (m_pNewMine->uCol != m_pOldMine->uCol ||
					m_pNewMine->uRow != m_pOldMine->uRow)
				{
					switch (m_pNewMine->uState)
					{
					default:
						break;
					case STATE_NORMAL:
						m_pNewMine->uState = STATE_EMPTY;
						break;
					case STATE_DICEY:
						m_pNewMine->uState = STATE_DICEY_DOWN;
						break;
					}
					switch (m_pOldMine->uOldState)
					{
					default:
						break;
					case STATE_NORMAL:
						m_pOldMine->uState = STATE_NORMAL;
						break;
					case STATE_DICEY:
						m_pOldMine->uState = STATE_DICEY;
						break;
					}
					if (m_bLRBtnDown)
					{
						OnLRBtnUp(m_pOldMine->uRow, m_pOldMine->uCol);
						OnLRBtnDown(m_pNewMine->uRow, m_pNewMine->uCol);
					}
					m_pOldMine = m_pNewMine;
				}
				InvalidateRect(rcMineArea);
				break;
			case GS_VICTORY:
			case GS_DEAD:
				return;
			}
		}
		else
		{
			switch (m_uGameState)
			{
			default:
				break;
			case GS_RUN:
				m_uBtnState = (m_bClickBtn) ? BUTTON_NORMAL : BUTTON_CLICK;
				if (m_pNewMine)
				{
					if (m_pNewMine->uOldState == STATE_NORMAL)
					{
						m_pNewMine->uState = STATE_NORMAL;
					}
					else if (m_pNewMine->uOldState == STATE_DICEY)
					{
						m_pNewMine->uState = STATE_DICEY;
					}
				}
				break;
			case GS_DEAD:
				m_uBtnState = BUTTON_DEAD;
				break;
			case GS_VICTORY:
				m_uBtnState = BUTTON_VICTORY;
				break;
			}
			Invalidate();
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CMineWnd::OnInitMenu(CMenu* pMenu)
{
	CWnd::OnInitMenu(pMenu);

	// TODO: 在此处添加消息处理程序代码
	if ((m_pSubMenu = pMenu->GetSubMenu(0)) == 0)
	{
		AfxMessageBox(_T("初始化菜单失败!"));
		PostQuitMessage(0);
	}
	else
	{
		SetCheckedLevel();
		SetCheckedMark();
		SetCheckedColor();
		SetCheckedSound();
	}
}


void CMineWnd::OnMenuSecond()
{
	// TODO: 在此添加命令处理程序代码
	m_uLevel = LEVEL_SECONDRY;
	m_uXNum = SECONDRY_XNUM;
	m_uYNum = SECONDRY_YNUM;
	m_uMineNum = SECONDRY_MINENUM;

	SetCheckedLevel();
	InitGame();
	Invalidate();
	SizeWindow();
}


void CMineWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SaveConfig();
	KillTimer(ID_TIMER_EVENT);
	CWnd::OnClose();
}


void CMineWnd::OnMenuAdvance()
{
	// TODO: 在此添加命令处理程序代码
	m_uLevel = LEVEL_ADVANCE;
	m_uXNum = ADVANCE_XNUM;
	m_uYNum = ADVANCE_YNUM;
	m_uMineNum = ADVANCE_MINENUM;

	SetCheckedLevel();
	InitGame();
	Invalidate();
	SizeWindow();
}


void CMineWnd::OnMenuCustom()
{
	// TODO: 在此添加命令处理程序代码
	m_uLevel = LEVEL_CUSTOM;
	SetCheckedLevel();
	CDlgCustom Dlg;
	Dlg.InitData(m_uXNum, m_uYNum, m_uMineNum);
	Dlg.DoModal();

	InitGame();
	Invalidate();
	SizeWindow();
}

void CMineWnd::SetCustom(UINT xNum, UINT yNum, UINT mNum)
{
	m_uXNum = xNum;
	m_uYNum = yNum;
	m_uMineNum = mNum;
}

void CMineWnd::ResetRecord()
{
	m_uPrimary = DEFAULT_RECORD;
	m_szPrimary = DEFAULT_HOLDER;
	m_uSecond = DEFAULT_RECORD;
	m_szSecond = DEFAULT_HOLDER;
	m_uAdvance = DEFAULT_RECORD;
	m_szSecond = DEFAULT_HOLDER;
}

void CMineWnd::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	PostQuitMessage(0);
}


void CMineWnd::OnMenuHelpUse()
{
	// TODO: 在此添加命令处理程序代码
	::WinExec("HH NTHelp.CHM", SW_SHOW);
}


void CMineWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	default:
		break;
	case VK_F1:
		OnMenuHelpUse();
		break;
	case VK_F2:
		OnMenuStart();
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMineWnd::OnMenuHero()
{
	// TODO: 在此添加命令处理程序代码
	CDlgHero dlg;
	dlg.SetBRecord(m_uPrimary);
	dlg.SetBHolder(m_szPrimary);
	dlg.SetIRecord(m_uSecond);
	dlg.SetIHolder(m_szSecond);
	dlg.SetERecord(m_uAdvance);
	dlg.SetEHolder(m_szAdvance);
	dlg.DoModal();
}
