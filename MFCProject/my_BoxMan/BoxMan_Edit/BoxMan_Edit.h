#pragma once
#define M_TAB_WIDTH		(20)
#define M_TAB_HEIGHT	(20)

class CBoxMan_Edit
{
public:
	CBoxMan_Edit();
	~CBoxMan_Edit();
public:
	void ChangeMap(int x, int y, int iState);
	int GetNowMissionNum(void);
	BOOL ChangeMissionNum(int iNum);
	void DrawMouseCursor(int x, int y, int iState, CDC *pDC);
	void DrawMap(CDC* pDC);
	void ClearMap(void);
	void SaveMap(void);
	void LoadMap(int iMissionNum);
protected:
	CPoint GetManPosition();
	void DrawBackGroup(int x, int y, CDC *pDC);
	void DrawWhiteWall(int x, int y, CDC *pDC);
	void DrawBlueWall(int x, int y, CDC *pDC);
	void DrawBall(int x, int y, CDC *pDC);
	void DrawYellowBox(int x, int y, CDC *pDC);
	void DrawRedBox(int x, int y, CDC *pDC);
	void DrawManWall(int x, int y, CDC *pDC);
	void DrawManBall(int x, int y, CDC *pDC);
	void UpdateMap(UINT nChar);
	void UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3);
	bool IsFinish(void);
	
	int LoadMaxMissionNum(void);

protected:
	char m_cMap[M_TAB_WIDTH][M_TAB_HEIGHT];
	int m_iMissionNum;
	CPoint m_ptManPosition;
};

