#pragma once

#define M_TAB_WIDTH		(20)
#define M_TAB_HEIGHT	(20)


class CBoxMan
{
public:
	CBoxMan();
	~CBoxMan();
public:
	BOOL ChangeMissionNum(int iNum);
	void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawGameArea(CDC *pDC);
	void IsSound(BOOL bUse);
protected:
	char m_cMap[M_TAB_WIDTH][M_TAB_HEIGHT];
	CPoint m_ptManPosition;
	int m_iMissionNum;

	int m_soundState;
	int m_bSound;
protected:
	void DrawBackGroup(int x, int y, CDC* pDC);
	void DrawWhiteWall(int x, int y, CDC *pDC);
	void DrawBlueWall(int x, int y, CDC *pDC);
	void DrawBall(int x, int y, CDC *pDC);
	void DrawYellowBox(int x, int y, CDC *pDC);
	void DrawRedBox(int x, int y, CDC *pDC);
	void DrawManWall(int x, int y, CDC *pDC);
	void DrawManBall(int x, int y, CDC *pDC);
	void LoadMap(int iMissionNum);
	void DispatchMsg(UINT nChar);
	CPoint GetManPosition();
	void UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3);
	bool IsFinish(void);
	void BoxManPlaySound(void);

};

