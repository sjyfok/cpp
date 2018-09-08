#ifndef TIC_TAC_MFC_H__
#define	TIC_TAC_MFC_H__

#include <afxwin.h>

#define EX	(1)
#define OH	(2)
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CWnd
{
protected:
	static const CRect m_rcSquaresp[9];
	int m_nGameGrid[9];
	int m_nNextChar;
	int GetRectID(CPoint point);
	void DrawBoard(CDC *pdc);
	void DrawX(CDC *pdc, int nPos);
	void DrawO(CDC *pdc, int nPos);
	void  ResetGame();
	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();
public:
	CMainWindow();
protected:
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT uFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};



#endif
