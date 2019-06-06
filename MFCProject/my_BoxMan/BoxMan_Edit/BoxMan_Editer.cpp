
// BoxMan_Edit.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "BoxMan_Editer.h"
#include "Boxman_EditerWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBoxManEditApp

BEGIN_MESSAGE_MAP(CBoxManEditApp, CWinApp)

END_MESSAGE_MAP()


// CBoxManEditApp 构造

CBoxManEditApp::CBoxManEditApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("BoxManEdit.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CBoxManEditApp 对象

CBoxManEditApp theApp;

extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int MAP_SMALL_SQUARE_SIZE;

const CString className = _T("skyblue_boxmanediter_class");
// CBoxManEditApp 初始化

BOOL CBoxManEditApp::InitInstance()
{
	m_pBoxManEditerWnd = new CBoxman_EditerWnd();
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
		AfxMessageBox(_T("注册窗口类失败"));
		return FALSE;
	}

	UINT uWidth = MAP_WIDTH * MAP_SMALL_SQUARE_SIZE + 10;
	UINT uHeight = MAP_HEIGHT * MAP_SMALL_SQUARE_SIZE + 56;
	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;

	if (!m_pBoxManEditerWnd->CreateEx(NULL, className, _T("推箱子_地图编辑器"),
		WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL)	)
	{
		AfxMessageBox(_T("创建主窗口失败!"));
		return FALSE;
	}
	m_pBoxManEditerWnd->ShowWindow(SW_NORMAL);
	m_pMainWnd = m_pBoxManEditerWnd;
	return TRUE;
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	//INITCOMMONCONTROLSEX InitCtrls;
	//InitCtrls.dwSize = sizeof(InitCtrls);
	//// 将它设置为包括所有要在应用程序中使用的
	//// 公共控件类。
	//InitCtrls.dwICC = ICC_WIN95_CLASSES;
	//InitCommonControlsEx(&InitCtrls);

	//CWinApp::InitInstance();


	//// 初始化 OLE 库
	//if (!AfxOleInit())
	//{
	//	AfxMessageBox(IDP_OLE_INIT_FAILED);
	//	return FALSE;
	//}

	//AfxEnableControlContainer();

	//EnableTaskbarInteraction(FALSE);

	//// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	//// AfxInitRichEdit2();

	//// 标准初始化
	//// 如果未使用这些功能并希望减小
	//// 最终可执行文件的大小，则应移除下列
	//// 不需要的特定初始化例程
	//// 更改用于存储设置的注册表项
	//// TODO: 应适当修改该字符串，
	//// 例如修改为公司或组织名
	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	//// 若要创建主窗口，此代码将创建新的框架窗口
	//// 对象，然后将其设置为应用程序的主窗口对象
	//CMDIFrameWnd* pFrame = new CMainFrame;
	//if (!pFrame)
	//	return FALSE;
	//m_pMainWnd = pFrame;
	//// 创建主 MDI 框架窗口
	//if (!pFrame->LoadFrame(IDR_MAINFRAME))
	//	return FALSE;
	//// 试图加载共享 MDI 菜单和快捷键表
	////TODO: 添加附加成员变量，并加载对
	////	应用程序可能需要的附加菜单类型的调用
	//HINSTANCE hInst = AfxGetResourceHandle();
	//m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_BoxManEditTYPE));
	//m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_BoxManEditTYPE));




	//// 主窗口已初始化，因此显示它并对其进行更新
	//pFrame->ShowWindow(m_nCmdShow);
	//pFrame->UpdateWindow();

	//return TRUE;
}

int CBoxManEditApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	if (m_hMDIMenu != nullptr)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != nullptr)
		FreeResource(m_hMDIAccel);

	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

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
//	afx_msg void OnMenuMapBall();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_MENU_MAP_BALL, &CAboutDlg::OnMenuMapBall)
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CBoxManEditApp 消息处理程序





//void CAboutDlg::OnMenuMapBall()
//{
//	// TODO: 在此添加命令处理程序代码
//	m_now_Select
//}


//void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}
