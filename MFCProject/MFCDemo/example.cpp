
#include "example.h"
#include "Project/resource.h"
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
	//LPCTSTR lpszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 
	//	::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_3DFACE + 1));

	//CreateEx(WS_EX_CLIENTEDGE, lpszClassName, 
	//	"框架程序测创建的窗口", WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

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
	m_btnModeless.Create("Modeless Dialog", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(220, 30, 350, 70), this, IDC_MODELESS);
	

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

CMyDialog::CMyDialog(CWnd *pParentWnd) :CDialog(IDD_MYDIALOG, pParentWnd)
{
	m_bModeless = FALSE;
}

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDC_START, OnStart)
END_MESSAGE_MAP()

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText("框架程序窗口的对话框");
	return TRUE;
}

void CMyDialog::OnCancel()
{
	if (m_bModeless)
	{
		DestroyWindow();
	}
	else
	{
		CDialog::OnCancel();
	}
}

void CMyDialog::OnStart()
{
	MessageBox("开始！");
}

void CMyDialog::PostNcDestroy()
{
	if (m_bModeless)
	{
		delete this;
	}
}
//int CMyApp::ExitInstance()
//{
//	::MessageBox(NULL, "主线程将要退出!", "CMyApp::ExitInstance", MB_OK);
//	return 0;
//}

