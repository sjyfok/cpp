
// Mine.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Mine.h"
#include "MineDefs.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMineApp

BEGIN_MESSAGE_MAP(CMineApp, CWinApp)
/*	ON_COMMAND(ID_APP_ABOUT, &CMineApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)*/
END_MESSAGE_MAP()


// CMineApp 构造

CMineApp::CMineApp() noexcept
{
	// 支持重新启动管理器
//	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
//#ifdef _MANAGED
//	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
//	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
//	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
//	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
//#endif
//
//	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
//	//为 CompanyName.ProductName.SubProduct.VersionInformation
//	SetAppID(_T("Mine.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMineApp 对象

CMineApp theApp;


// CMineApp 初始化
const CString className = _T("MineClass");
BOOL CMineApp::InitInstance()
{
	SetRegistryKey(_T("CSER_513_2"));
	m_uXMineNum = GetProfileInt(GAME_SETTING, CUSTOM_XNUM, PRIMARY_XNUM);
	m_uYMineNum = GetProfileInt(GAME_SETTING, CUSTOM_YNUM, PRIMARY_YNUM);
	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	m_pMineWnd = new CMineWnd();
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(IDC_ARROW);
	wc.hIcon = LoadIcon(IDR_MAINFRAME);
	wc.lpszClassName = className;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
	if (!AfxRegisterClass(&wc))
	{
		AfxMessageBox(_T("注册类失败!"));
		return FALSE;
	}
	UINT uWidth = DEFAULT_FRAME_X+m_uXMineNum*MINE_WIDTH+
		LINE_WIDTH_0*3+SIDE_WIDTH_0*2 + SIDE_WIDTH_1*2 ;
	UINT uHeight = DEFAULT_FRAME_Y + m_uYMineNum * MINE_HEIGHT +
		LINE_WIDTH_0 * 3 + SIDE_WIDTH_0 * 2 + SIDE_WIDTH_1*2 + SHELL_S_H;

	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;

	if (!m_pMineWnd->CreateEx(NULL, className, _T("扫雷"),
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL))
	{
		AfxMessageBox(_T("创建主窗口失败！"));
		return FALSE;
	}

	m_pMainWnd = m_pMineWnd;
	m_pMainWnd->ShowWindow(SW_NORMAL);
	return TRUE;
}

// CMineApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMenuHelpFind();
//	afx_msg void OnMenuStart();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_MENU_HELP_FIND, &CAboutDlg::OnMenuHelpFind)
//	ON_COMMAND(ID_MENU_START, &CAboutDlg::OnMenuStart)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMineApp 消息处理程序





//void CAboutDlg::OnMenuHelpFind()
//{
//	// TODO: 在此添加命令处理程序代码
//	::WinExec("HH WINMINE.CHM", SW_SHOW);
//}


//void CAboutDlg::OnMenuStart()
//{
//	// TODO: 在此添加命令处理程序代码
//	InitGame();
//	Invalidate();
//}
