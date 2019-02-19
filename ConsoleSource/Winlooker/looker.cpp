#include "afxwin.h"
#include "looker.h"
#include "ConsoleApplication/ConsoleApplication/resource.h"

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

	LPCTSTR lpszClassName = AfxRegisterWndClass(0, NULL, (HBRUSH)COLOR_3DFACE + 1,
		AfxGetApp()->LoadIcon(IDI_MAIN));

	CreateEx(0, lpszClassName, "´°¿Ú²é¿´Æ÷",
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL
	);
}