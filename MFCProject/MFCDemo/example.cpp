
#include "example.h"

CMyApp theApp;



BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDC_MODEL, OnModel)
	ON_COMMAND(IDC_MODELESS, OnModeless)
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	LPCTSTR lpszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_3DFACE + 1));

	CreateEx(WS_EX_CLIENTEDGE, lpszClassName, 
		"框架程序测创建的窗口", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
}


BOOL CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_btnModel.Create("Model Dialog", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(50, 30, 180, 70), this, IDC_MODEL);
	m_btnModel.Create("Modeless Dialog", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(220, 30, 350, 70), this, IDC_MODEL);
	

	return TRUE;
}

void CMainWindow::OnModel()
{

	CMyDialog dlg(this);
	dlg.DoModal();
}

void CMainWindow::OnModeless()
{
	CMyDialog *pDlg = new CMyDialog(this);
	pDlg->m_bModeless = TRUE;
	pDlg->Create(IDD_MYDIALOG);
	pDlg->CenterWindow();
	pDlg->ShowWindow(SW_NORMAL);
	pDlg->UpdateData();
}

void CMainWindow::PostNcDestroy()
{
	delete this;
}
//int CMyApp::ExitInstance()
//{
//	::MessageBox(NULL, "主线程将要退出!", "CMyApp::ExitInstance", MB_OK);
//	return 0;
//}

