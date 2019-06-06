#include "stdafx.h"
#include "BoxMan.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define MAP_BACKGROUP	(48)
#define MAP_WHITEWALL	(49)
#define MAP_BLUEWALL	(50)
#define MAP_BALL		(51)
#define MAP_YELLOWBOX	(52)
#define MAP_REDBOX		(53)
#define MAP_MANWALL		(54)
#define MAP_MANBALL		(55)


#define SOUND_STATE_START		(0)
#define SOUND_STATE_MOVE		(1)
#define SOUND_STATE_PUSH		(2)
#define SOUND_STATE_VICTORY		(3)

#define BLOCK_WIDTH			(20)
#define BLOCK_HEIGHT		(20)

int MAX_MISSION_NUM = 1;



CBoxMan::CBoxMan()
{
}


CBoxMan::~CBoxMan()
{
}

void CBoxMan::DrawGameArea(CDC *pDC)
{
	int i, j, x, y;
	for (i = 0; i < M_TAB_HEIGHT; i++)
	{
		for (j = 0; j < M_TAB_WIDTH; j ++)
		{
			x = j * BLOCK_WIDTH;
			y = i * BLOCK_HEIGHT;
			switch (m_cMap[i][j])
			{
			default:
				break;
			case MAP_BACKGROUP:
				DrawBackGroup(x, y, pDC);
				break;
			case MAP_WHITEWALL:
				DrawWhiteWall(x, y, pDC);
				break;
			case MAP_BLUEWALL:
				DrawBlueWall(x, y, pDC);
				break;
			case MAP_BALL:
				DrawBall(x, y, pDC);
				break;
			case MAP_YELLOWBOX:
				DrawYellowBox(x, y, pDC);
				break;
			case MAP_REDBOX:
				DrawRedBox(x, y, pDC);
				break;
			case MAP_MANWALL:
				DrawManWall(x, y, pDC);
				break;
			case MAP_MANBALL:
				DrawManBall(x, y, pDC);
				break;
			}
		}
	}
	COLORREF crOldText = pDC->GetTextColor();
	COLORREF crOldBack = pDC->GetBkColor();
	pDC->SetTextColor(RGB(0, 0, 102));
	pDC->SetBkColor(RGB(0, 0, 0));
	CString sTmp;
	sTmp.Format(_T("当前关数: %d "), m_iMissionNum);
	pDC->TextOut(50, 270, sTmp);

	pDC->SetTextColor(crOldText);
	pDC->SetBkColor(crOldBack);
}

void CBoxMan::LoadMap(int iMissionNum)
{
	char str[M_TAB_WIDTH];
	sprintf_s(str, "[%d]", iMissionNum);
	/*str.Format(_T("[%d]"), iMissionNum);*/

	FILE *pFile = fopen("map.info", "rt");
	if (pFile == NULL)
	{
		AfxMessageBox(_T("载入地图文件失败"));
		return;
	}
	char cTmp[M_TAB_WIDTH * 2];
	fgets(cTmp, M_TAB_WIDTH * 2, pFile);
	while (strncmp(cTmp, str, 3)!= 0)
	{
		fgets(cTmp, M_TAB_WIDTH * 2, pFile);
	}
	for (int  i = 0; i < M_TAB_HEIGHT; i++)
	{
		fgets(m_cMap[i], M_TAB_WIDTH * 2, pFile);
	}
	fclose(pFile);
}

void CBoxMan::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	DispatchMsg(nChar);
	if (IsFinish())
	{
		m_soundState = SOUND_STATE_VICTORY;
		m_iMissionNum = m_iMissionNum + 1;
		if (m_iMissionNum > MAX_MISSION_NUM)
		{
			m_iMissionNum = 1;
		}
		LoadMap(m_iMissionNum);
		m_ptManPosition = GetManPosition();
	}
	BoxManPlaySound();
}

CPoint CBoxMan::GetManPosition()
{
	CPoint manPosition(0, 0);
	for (int i = 0; i < M_TAB_HEIGHT; i++)
	{
		for (int j = 0; j < M_TAB_WIDTH; j++)
		{
			if (m_cMap[i][j] == MAP_MANWALL || m_cMap[i][j] == MAP_MANBALL)
			{
				manPosition.x = j;
				manPosition.y = i;
			}
		}
	}
	return manPosition;
}

void CBoxMan::BoxManPlaySound(void)
{
	if (m_bSound)
	{
		CString strFileName;
		switch (m_soundState)
		{
		default:
			break;
		case SOUND_STATE_START:
			strFileName.Format(_T("%s"), _T("start.wav"));
			break;
		case SOUND_STATE_MOVE:
			strFileName.Format(_T("%s"), _T("move.wav"));
			//strcpy(strFileName, "move.wav");
			break;
		case SOUND_STATE_PUSH:
			strFileName.Format(_T("%s"), _T("push.wav"));
			//strcpy(strFileName, "push.wav");
			break;
		case SOUND_STATE_VICTORY:
			strFileName.Format(_T("%s"), _T("victory.wav"));
			//strcpy(strFileName, "victory.wav");
			break;
		}
		PlaySound(strFileName, NULL, SND_ASYNC | SND_FILENAME);
	}
}

void CBoxMan::DispatchMsg(UINT nChar)
{
	int x1, y1, x2, y2, x3, y3;

	x1 = m_ptManPosition.x;
	y1 = m_ptManPosition.y;

	switch (nChar)
	{
	default:
		break;
	case VK_UP:
		x2 = x1;
		y2 = y1 - 1;
		x3 = x1;
		y3 = y1 - 2;
		UpdateMap(x1, y1, x2, y2, x3, y3);
		break;
	case VK_DOWN:
		x2 = x1 - 1;
		y2 = y1;
		x3 = x1 - 2;
		y3 = y1;
		UpdateMap(x1, y1, x2, y2, x3, y3);
		break;
	case VK_LEFT:
		x2 = x1 - 1;
		y2 = y1;
		x3 = x1 - 2;
		y3 = y1;
		UpdateMap(x1, y1, x2, y2, x3, y3);
		break;
	case VK_RIGHT:
		x2 = x1 + 1;
		y2 = y1;
		x3 = x1 + 2;
		y3 = y1;
		UpdateMap(x1, y1, x2, y2, x3, y3);
		break;
	case 82:
	case 114:
		LoadMap(m_iMissionNum);
		m_ptManPosition = GetManPosition();
		break;
	case 113:
		m_iMissionNum = m_iMissionNum + 1;
		if (m_iMissionNum > MAX_MISSION_NUM)
		{
			m_iMissionNum = 1;
		}
		LoadMap(m_iMissionNum);
		m_ptManPosition = GetManPosition();
		break;
	case 112:
		m_iMissionNum -= 1;
		if (m_iMissionNum < 1)
			m_iMissionNum = MAX_MISSION_NUM;
		LoadMap(m_iMissionNum);
		m_ptManPosition = GetManPosition();
	}
}

bool CBoxMan::IsFinish()
{
	bool bFinish = true;
	for (int i = 0; i < M_TAB_HEIGHT; i++)
	{
		for (int j = 0; j < M_TAB_WIDTH; j++)
		{
			if (m_cMap[i][j] == MAP_BALL || m_cMap[i][j] == MAP_MANBALL)
			{
				bFinish = false;
			}
		}
	}
	return bFinish;
}

void CBoxMan::UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
	switch (m_cMap[y2][x2])
	{
	default:
		break;
	case MAP_BACKGROUP:
		AfxMessageBox(_T("wrong map"));
		break;
	case MAP_WHITEWALL:
		break;
	case MAP_BLUEWALL:
		m_cMap[y2][x2] = MAP_MANBALL;
		if (m_cMap[y1][x1] == MAP_MANWALL)
			m_cMap[y1][x1] = MAP_BLUEWALL;
		else if (m_cMap[y1][x1] == MAP_MANBALL)
			m_cMap[y1][x1] = MAP_BALL;
		m_ptManPosition.x = x2;
		m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_MOVE;		
		break;
	case MAP_BALL:
		m_cMap[y2][x2] = MAP_MANBALL;
		if (m_cMap[y1][x1] == MAP_MANWALL)
			m_cMap[y1][x1] = MAP_BLUEWALL;
		else if (m_cMap[y1][x1] == MAP_MANBALL)
			m_cMap[y1][x1] = MAP_BALL;
		m_ptManPosition.x = x2;
		m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_MOVE;
		break;
	case MAP_YELLOWBOX:
		if (m_cMap[y3][x3] == MAP_BALL)
		{
			m_cMap[y3][x3] = MAP_REDBOX;
			m_cMap[y2][x2] = MAP_MANWALL;
			if (m_cMap[y1][x1] == MAP_MANWALL)
				m_cMap[y1][x1] = MAP_BLUEWALL;
			else if (m_cMap[y1][x1] == MAP_MANBALL)
				m_cMap[y1][x1] = MAP_BALL;
			m_ptManPosition.x = x2;
			m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
		}
		else if (m_cMap[y3][x3] == MAP_BLUEWALL)
		{
			m_cMap[y3][x3] = MAP_YELLOWBOX;
			m_cMap[y2][x2] = MAP_MANWALL;
			if (m_cMap[y1][x1] = MAP_MANWALL)
				m_cMap[y1][x1] = MAP_BLUEWALL;
			else if (m_cMap[y1][x1] == MAP_MANBALL)
				m_cMap[y1][x1] = MAP_BALL;
			m_ptManPosition.x = x2;
			m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
		}
		break;
	case MAP_REDBOX:
		if (m_cMap[y3][x3] == MAP_BALL)
		{
			m_cMap[y3][x3] = MAP_REDBOX;
			m_cMap[y2][x2] = MAP_MANBALL;
			if (m_cMap[y1][x1] == MAP_MANWALL)
				m_cMap[y1][x1] = MAP_BLUEWALL;
			else if (m_cMap[y1][x1] == MAP_MANBALL)
				m_cMap[y1][x1] = MAP_BALL;
			m_ptManPosition.x = x2;
			m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
		}
		else if (m_cMap[y3][x3] == MAP_BLUEWALL)
		{
			m_cMap[y3][x3] = MAP_YELLOWBOX;
			m_cMap[y2][x2] = MAP_MANBALL;
			if (m_cMap[y1][x1] == MAP_MANWALL)
				m_cMap[y1][x1] = MAP_BLUEWALL;
			else if (m_cMap[y1][x1] == MAP_MANBALL)
				m_cMap[y1][x1] = MAP_BALL;
			m_ptManPosition.x = x2;
			m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
		}
		break;
	case MAP_MANWALL:
		AfxMessageBox(_T("wrong map"));
		break;
	case MAP_MANBALL:
		AfxMessageBox(_T("wrong map"));
		break;
	}
}

void CBoxMan::DrawBackGroup(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 0);
	pDC->FillSolidRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, clr);
}

void CBoxMan::DrawWhiteWall(int x, int y, CDC *pDC)
{
	COLORREF clr1 = RGB(255, 255, 255);
	COLORREF clr2 = RGB(48, 48, 48);
	COLORREF clr3 = RGB(192, 192, 192);

	pDC->FillSolidRect(x, y, 19, 19, clr1);
	pDC->FillSolidRect(x + 1, y + 1, 19, 19, clr2);
	pDC->FillSolidRect(x + 1, y + 1, 18, 18, clr3);

	pDC->MoveTo(x, y + 10);
	pDC->LineTo(x + 20, y + 10);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 20);
}

void CBoxMan::DrawBlueWall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 255);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	pDC->MoveTo(x, y + 10);
	pDC->LineTo(x + 20, y + 10);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 20);
}

void CBoxMan::DrawBall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 255);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	pDC->MoveTo(x, y + 10);
	pDC->LineTo(x + 20, y + 10);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 20);
	pDC->Ellipse(x, y, x + 20, y + 20);
	pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);
}

void CBoxMan::DrawYellowBox(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 255);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	COLORREF clr2 = RGB(255, 292, 0);
	pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
	COLORREF clr3 = RGB(0, 0, 0);
	pDC->SetPixel(x + 3, y + 3, clr3);
	pDC->SetPixel(x + 17, y + 3, clr3);
	pDC->SetPixel(x + 3, y + 17, clr3);
	pDC->SetPixel(x + 17, y + 17, clr3);
}

void CBoxMan::DrawRedBox(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(255, 255, 0);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	COLORREF clr2 = RGB(255, 0, 0);
	pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
	COLORREF clr3 = RGB(0, 0, 0);
	pDC->SetPixel(x + 3, y + 3, clr3);
	pDC->SetPixel(x + 17, y + 3, clr3);
	pDC->SetPixel(x + 3, y + 17, clr3);
	pDC->SetPixel(x + 17, y + 17, clr3);
}

void CBoxMan::DrawManWall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 255);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	pDC->MoveTo(x, y + 10);
	pDC->LineTo(x + 20, y + 10);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 20);

	pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);
	pDC->MoveTo(x + 2, y + 11);
	pDC->LineTo(x + 18, y + 11);

	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 12);
	
	pDC->MoveTo(x + 2, y + 20);
	pDC->LineTo(x + 10, y + 12);
	pDC->LineTo(x + 18, y + 20);
}

void CBoxMan::DrawManBall(int x, int y, CDC *pDC)
{
	COLORREF clr = RGB(0, 0, 255);
	pDC->FillSolidRect(x, y, 20, 20, clr);
	pDC->MoveTo(x, y + 10);
	pDC->LineTo(x + 20, y + 10);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 20);
	pDC->Ellipse(x, y, x + 20, y + 20);
	pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);

	pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);
	pDC->MoveTo(x + 2, y + 11);
	pDC->LineTo(x + 18, y + 11);
	pDC->MoveTo(x + 10, y + 10);
	pDC->LineTo(x + 10, y + 12);
	pDC->MoveTo(x + 2, y + 20);
	pDC->LineTo(x + 10, y + 12);
	pDC->LineTo(x + 18, y + 20);
}

void CBoxMan::IsSound(BOOL bUse)
{
	m_bSound = bUse;
}

BOOL CBoxMan::ChangeMissionNum(int iNum)
{
	if ((iNum > MAX_MISSION_NUM) || (iNum < 1))
	{
		return FALSE;
	}
	else
	{
		m_iMissionNum = iNum;
		LoadMap(m_iMissionNum);
		m_ptManPosition = GetManPosition();
		return TRUE;
	}
}