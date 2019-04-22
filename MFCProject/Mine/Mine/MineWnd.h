
#include <afxwin.h>

typedef struct
{
	UINT uRow;
	UINT uCol;
	UINT uState;
	UINT uAttrib;
	UINT uOldState;
} MINEWND;

class CMineWnd :
	public CWnd
{
public:
	CMineWnd();
	~CMineWnd();
	void ResetRecord();
	void SetCustom(UINT xNum, UINT yNum, UINT mNum);
	
protected:
	UINT m_uXNum;
	UINT m_uYNum;
	UINT m_uMineNum;
	int m_nLeaveNum;
	UINT m_uSpendTime;
	UINT m_uGameState;
	UINT m_uTimer;

	UINT	m_uLevel;
	UINT	m_uPrimary;
	UINT	m_uSecond;
	UINT	m_uAdvance;
	CString	m_szPrimary;
	CString	m_szSecond;
	CString	m_szAdvance;

	BOOL m_bLRBtnDown;
	BOOL m_bClickBtn;
	BOOL m_bMarkful;
	BOOL m_bColorful;
	BOOL m_bSoundful;
	CMenu *m_pSubMenu;
	
	
	RECT m_rcClient;
	UINT m_uBtnRect[3];
	UINT m_uBtnState;
	UINT m_uNumRect[3];
	UINT m_uShellRcX[2];
	UINT m_uShellRcY[2];

	MINEWND m_pMines[100][100];
	MINEWND *m_pNewMine;
	MINEWND *m_pOldMine;

	CBitmap m_bmpMine;
	CBitmap m_bmpNumber;
	CBitmap m_bmpButton;

	CBrush		m_brsBG;
	COLORREF	m_clrDark;

	void* m_pSndDead;
	void* m_pSndVictory;
	void* m_pSndClock;
public:
	void LoadConfig();
	void SaveConfig();
	void LoadWaveSrc();
	void InitGame();
	void LoadBitmap();
	void FreeMines();
	void SizeWindow();
	void LayMines(UINT row, UINT col);
	
	void DrawShell(CPaintDC &dc);
	void DrawButton(CPaintDC &dc);
	void DrawNumber(CPaintDC &dc);
	void DrawMineArea(CPaintDC &dc);

	void DrawDownNum(MINEWND *mine, UINT num);
	void DrawSpecialMine(UINT row, UINT col);

	void SetCheckedSound();
	void SetCheckedColor();
	void SetCheckedMark();
	void SetCheckedLevel();

	void ExpandMines(UINT row, UINT col);
	BOOL IsInMineArea(UINT row, UINT col);
	BOOL IsMine(UINT row, UINT col);
	UINT GetAroundNum(UINT row, UINT col);
	UINT GetAroundFlags(UINT row, UINT col);
	void Dead(UINT row, UINT col);
	BOOL Victory();

	void OnLRBtnDown(UINT row, UINT col);
	void OnLRBtnUp(UINT row, UINT col);
	void OpenAround(UINT row, UINT col);
	BOOL ErrorAroundFlag(UINT row, UINT col);

	MINEWND *GetMine(long x, long y);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuStart();
	afx_msg void OnMenuPrimary();
	afx_msg void OnMenuSecond();
	afx_msg void OnMenuAdvance();
	afx_msg void OnMenuCustom();
	afx_msg void OnMenuColor();
	afx_msg void OnMenuSound();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuHelpUse();
	afx_msg void OnMenuAbout();	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInitMenu(CMenu* pMenu);	
	afx_msg void OnClose();	
	afx_msg void OnMenuHero();
};
