#include "looker.h"

CMyApp theApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMainWindow::CMainWindow()
{
	m_bCatchMouseDown = FALSE;
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorTarget = AfxGetApp()->LoadCursor(IDC_TARGET);
}