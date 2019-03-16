
#include <afxwin.h>

typedef struct
{
	UINT uRow;
	UINT uCol;
	UINT uState;
	UINT uAttrib;
	UINT uOldState;
} WINEWND;

class CMineWnd :
	public CWnd
{
public:
	CMineWnd();
	~CMineWnd();
	void SizeWindow();

	WINEWND *GetMine(long x, long y);
protected:
	UINT m_uXNum;
	UINT m_uYNum;
	UINT m_uMineNum;
	UINT m_uGameState;
	BOOL m_bColorful;
	BOOL m_bSoundful;
	
	BOOL m_bLRBtnDown;
	RECT m_rcClient;
	UINT m_uBtnRect[3];

	WINEWND m_pMines[100][100];
	WINEWND *m_pNewMine;
	WINEWND *m_pOldMine;

	CBitmap m_bmpMine;
	CBitmap m_bmpNumber;
	CBitmap m_bmpButton;

	COLORREF m_clrDark;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuPrimary();
	afx_msg void OnMenuColor();
	afx_msg void OnMenuSound();
	afx_msg void OnMenuAbout();
	void LayMines(UINT row, UINT col);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL IsMine(UINT row, UINT col);
	UINT GetAroundNum(UINT row, UINT col);
	void ExPandMines(UINT row, UINT col);
	BOOL Victory();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void InitGame();
	void LoadBitmap();
};
