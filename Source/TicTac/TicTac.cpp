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
END_MESSAGE_MAP()

const CRect CMainWindow::m_rcSquaresp[9] = {
	CRect(16, 16, 112, 112),
	CRect(128, 16, 224, 112),
	CRect(240, 16, 336, 112),
	CRect(16, 128, 112, 224),
	CRect(128, 128, 224, 225),
	CRect(240, 128, 336, 224),
	CRect(16, 240, 224, 336),
	CRect(128, 240, 224, 336),
	CRect(240, 240, 336, 336)
};

CMainWindow::CMainWindow()
{
	m_nNextChar = EX;
	CString strWndClass = AfxRegisterWndClass(
		CS_DBLCLKS,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO)
		);

	CreateEx(0, strWndClass, _T("Tic-Tac_Toe"),
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZE,
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

	CRect rect = m_rcSquaresp[nPos];
	rect.DeflateRect(16, 16);
	pdc->Ellipse(rect);
	pdc->SelectObject(pOldPen);
}

void CMainWindow::DrawX(CDC *pdc, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen *pOldPen = pdc->SelectObject(&pen);
	
	CRect rect = m_rcSquaresp[nPos];
	rect.DeflateRect(16, 16);
	pdc->MoveTo(rect.left, rect.top);
	pdc->LineTo(rect.right, rect.bottom);
	pdc->MoveTo(rect.left, rect.bottom);
	pdc->LineTo(rect.right, rect.top);

	pdc->SelectObject(pOldPen);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{

}


