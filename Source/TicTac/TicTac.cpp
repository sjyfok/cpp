#include <afxwin.h>
#include "TicTac.h"

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

const CRect CMainWindow::m_rcSquares[9] = {
	CRect(16, 16, 112, 112),
	CRect(128, 16, 224, 112),
	CRect(240, 16, 336, 112),
	CRect(16, 128, 112, 224),
	CRect(128, 128, 224, 224),
	CRect(240, 128, 336, 224),
	CRect(16, 240, 112, 336),
	CRect(128, 240, 224, 336),
	CRect(240, 240, 336, 336)
};

CMainWindow::CMainWindow()
{
	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	CString strWndClass = AfxRegisterWndClass(
		CS_DBLCLKS,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO)
		);

	CreateEx(0, strWndClass, _T("Tic-Tac_Toe"),
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL);

		CRect rect(0, 0, 352, 352);
		CalcWindowRect(&rect);
		SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	
	DrawBoard(&dc);
}

void CMainWindow::PostNcDestroy()
{
	delete this;
}

void CMainWindow::DrawBoard(CDC *pdc)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 0));
	CPen *pOldPen = pdc->SelectObject(&pen);

	pdc->MoveTo(120, 16);
	pdc->LineTo(120, 336);

	pdc->MoveTo(232, 16);
	pdc->LineTo(232, 336);

	pdc->MoveTo(16, 120);
	pdc->LineTo(336, 120);

	pdc->MoveTo(16, 232);
	pdc->LineTo(336, 232);

	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == EX)
			DrawX(pdc, i);
		else if (m_nGameGrid[i] == OH)
			DrawO(pdc, i);
	}
	pdc->SelectObject(pOldPen);
}

void CMainWindow::DrawO(CDC *pdc, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen *pOldPen = pdc->SelectObject(&pen);
	pdc->SelectStockObject(NULL_BRUSH);

	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pdc->Ellipse(rect);
	pdc->SelectObject(pOldPen);
}

void CMainWindow::DrawX(CDC *pdc, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen *pOldPen = pdc->SelectObject(&pen);
	
	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pdc->MoveTo(rect.left, rect.top);
	pdc->LineTo(rect.right, rect.bottom);
	pdc->MoveTo(rect.left, rect.bottom);
	pdc->LineTo(rect.right, rect.top);

	pdc->SelectObject(pOldPen);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nNextChar != EX)
		return;
	int nPos = GetRectID(point);
	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
		return;

	m_nGameGrid[nPos] = EX;
	m_nNextChar = OH;

	CClientDC dc(this);
	DrawX(&dc, nPos);
	CheckForGameOver();
}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_nNextChar != OH)
		return;

	int nPos = GetRectID(point);
	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
		return;
	m_nGameGrid[nPos] = OH;
	m_nNextChar = EX;
	CClientDC dc(this);
	DrawO(&dc, nPos);
	CheckForGameOver();
}

void CMainWindow::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	if (dc.GetPixel(point) == RGB(0, 0, 0))
		ResetGame();
}

int CMainWindow::GetRectID(CPoint point)
{
	for (int i = 0; i < 9; i++)
	{
		if (m_rcSquares[i].PtInRect(point))
			return i;
	}
	return -1;
}

void CMainWindow::CheckForGameOver()
{
	int nWinner = 0;

	if (nWinner = IsWinner())
	{
		CString string = (nWinner == EX) ?
			_T("X wins") : _T("O wins");
		MessageBox(string, _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
		ResetGame();
	}
	else if (IsDraw())
	{
		MessageBox(_T("It's a draw!"), _T("Game Over"),
			MB_ICONEXCLAMATION | MB_OK);
		ResetGame();
	}
}

int CMainWindow::IsWinner()
{
	static int nPattern[8][3] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		0, 3, 6,
		1, 4, 7,
		2, 5, 8,
		0, 4, 8,
		2, 4, 6
	};

	for (int i = 0; i < 8; i++)
	{
		if ((m_nGameGrid[nPattern[i][0]] == EX)
			&& (m_nGameGrid[nPattern[i][1]] == EX)
			&& (m_nGameGrid[nPattern[i][2]] == EX))
			return EX;
		if ((m_nGameGrid[nPattern[i][0]] == OH)
			&& (m_nGameGrid[nPattern[i][1]] == OH)
			&& (m_nGameGrid[nPattern[i][2]] == OH))
			return OH;
	}
	return 0;
}

BOOL CMainWindow::IsDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == 0)
			return FALSE;
	}
	return TRUE;
}

void CMainWindow::ResetGame()
{
	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	Invalidate();
}