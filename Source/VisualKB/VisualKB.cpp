#include <afxwin.h>
#include "VisualKB.h"

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_CHAR()
	ON_WM_SYSCHAR()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	m_nTextPos = 0;
	m_nMsgPos = 0;
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorIBeam = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
	
	CString strWndClass = AfxRegisterWndClass(
		0,
		NULL,
		(HBRUSH)(COLOR_3DFACE + 1),
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO)
	);
	CreateEx(0, strWndClass,_T("Visual keyboard"),
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL);
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight;
	m_cyLine = tm.tmHeight + tm.tmExternalLeading;

	m_rcTextBoxBorder.SetRect(16, 16, (m_cxChar * 64) +	16,
		((m_cyChar * 3) / 2) + 16);

	m_rcTextBox = m_rcTextBoxBorder;
	m_rcTextBox.InflateRect(-2, -2);

	m_rcMsgBoxBorder.SetRect(16, (m_cyChar * 4) + 16,
		(m_cxChar * 64) + 16, (m_cyLine*MAX_STRINGS) +
		(m_cyChar * 6) + 16);
	m_rcScroll.SetRect(m_cxChar + 16, (m_cyChar * 6) + 16,
		(m_cxChar * 63) + 16, (m_cyLine*MAX_STRINGS) +
		(m_cyChar * 5) + 16);

	m_ptTextOrigin.x = m_cxChar + 16;
	m_ptTextOrigin.y = (m_cyChar / 4) + 16;
	m_ptCarePos = m_ptTextOrigin;
	m_nTextLimit = (m_cxChar * 63) + 16;

	m_ptHeaderOrigin.x = m_cxChar + 16;
	m_ptHeaderOrigin.y = m_cyChar * 3 + 16;

	m_ptUpperMsgOrigin.x = m_cxChar + 16;
	m_ptUpperMsgOrigin.y = (m_cyChar * 5) + 16;

	m_ptLowerMsgOrigin.x = m_cxChar + 16;
	m_ptLowerMsgOrigin.y = (m_cyChar * 5) + 
		(m_cyLine*(MAX_STRINGS - 1)) + 16;

	m_nTabStops[0] = (m_cxChar * 24) + 16;
	m_nTabStops[1] = (m_cxChar * 30) + 16;
	m_nTabStops[2] = (m_cxChar * 36) + 16;
	m_nTabStops[3] = (m_cxChar * 42) + 16;
	m_nTabStops[4] = (m_cxChar * 46) + 16;
	m_nTabStops[5] = (m_cxChar * 50) + 16;
	m_nTabStops[6] = (m_cxChar * 54) + 16;

	CRect rect(0, 0, m_rcMsgBoxBorder.right + 16,
		m_rcMsgBoxBorder.bottom + 16);
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
	return 0;
}

void CMainWindow::PostNcDestroy()
{
	delete this;
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	
	dc.DrawEdge(m_rcTextBoxBorder, EDGE_SUNKEN, BF_RECT);
	dc.DrawEdge(m_rcMsgBoxBorder, EDGE_SUNKEN, BF_RECT);

	DrawInputText(&dc);
	DrawMessageHeader(&dc);
	DrawMeaages(&dc);
}

void CMainWindow::OnSetFocus(CWnd *pWnd)
{
	CreateSolidCaret(max(2, ::GetSystemMetrics(SM_CSBORDER)),
		m_cyChar);
	SetCaretPos(m_ptCarePos);
	ShowCaret();
}

void CMainWindow::OnKillFocus(CWnd *pWnd)
{
	HideCaret();
	m_ptCarePos = GetCaretPos();
	::DestroyCaret();
}

BOOL CMainWindow::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest == HTCLIENT)
	{
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);
		::SetCursor(m_rcTextBox.PtInRect(point) ?
			m_hCursorIBeam : m_hCursorArrow);
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}



