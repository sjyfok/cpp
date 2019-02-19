
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
protected:
	UINT m_uXNum;
	UINT m_uYNum;
	UINT m_uMineNum;
	BOOL m_bColorful;
	BOOL m_bSoundful;
	WINEWND m_pMines[100][100];
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuPrimary();
	afx_msg void OnMenuColor();
	afx_msg void OnMenuSound();
	afx_msg void OnMenuAbout();
	void LayMines(UINT row, UINT col);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
