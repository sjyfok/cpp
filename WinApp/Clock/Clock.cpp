//WindowsProject1.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Clock.h"
#include <math.h>

#define MAX_LOADSTRING 100

#define IDT_CLOCK		(1)

static int s_nPreHour;
static int s_nPreMinute;
static int s_nPreSecond;

static int s_cxClient;
static int s_cyClient;

static BOOL s_bTopMost;

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void SetIsotropic(HDC hdc, int cx, int cy)
{
	::SetMapMode(hdc, MM_ISOTROPIC);
	::SetWindowExtEx(hdc, 1000, 1000, NULL);
	::SetViewportExtEx(hdc, cx, -cy, NULL);
	::SetViewportOrgEx(hdc, cx / 2, cy / 2, NULL);
}


void DrawClockFace(HDC hdc)
{
	const int SQUARESIZE = 20;
	static POINT pt[] = {
		0, 450,
		225, 390,
		390, 225,
		450, 0,
		390, -225,
		225, -390,
		0, -450,
		-255, -390,
		-390, -225,
		-450, 0,
		-390, 225,
		-225, 390
	};
	::SelectObject(hdc, ::GetStockObject(BLACK_BRUSH));
	for (int i = 0; i < 12; i++)
	{
		::Ellipse(hdc, pt[i].x - SQUARESIZE, pt[i].y + SQUARESIZE,
			pt[i].x + SQUARESIZE, pt[i].y - SQUARESIZE);
	}
}

void DrawHand(HDC hdc, int nLength, int nWidth, int nDegrees, COLORREF clrColor)
{
	double nRadians = (double)nDegrees*0.0174533;
	POINT pt[2];
	pt[0].x = (int)(nLength*sin(nRadians));
	pt[0].y = (int)(nLength*cos(nRadians));
	pt[1].x = -pt[0].x / 5;
	pt[1].y = -pt[0].y / 5;

	HPEN hPen = ::CreatePen(PS_SOLID, nWidth, clrColor);
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

	::MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
	::LineTo(hdc, pt[1].x, pt[1].y);
	SelectObject(hdc, hOldPen);
	::DeleteObject(hPen);
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int nNum;
	TCHAR szText[56];// = _T("最简单的窗口程序!");
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)
    {
	case WM_CREATE:
	{
		SYSTEMTIME time;
		::GetLocalTime(&time);
		s_nPreHour = time.wHour % 12;
		s_nPreMinute = time.wMinute;
		s_nPreSecond = time.wSecond;
		::SetTimer(hWnd, IDT_CLOCK, 1000, NULL);
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			SetIsotropic(hdc, s_cxClient, s_cyClient);
			DrawClockFace(hdc);
			DrawHand(hdc, 200, 8, s_nPreHour * 30 + s_nPreMinute / 2, RGB(0, 0, 0));
			DrawHand(hdc, 400, 6, s_nPreMinute * 6, RGB(0, 0, 0));
			DrawHand(hdc, 400, 1, s_nPreSecond * 6, RGB(0, 0, 0));
			//wsprintf(szText, _T("计数: %d"), nNum);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			//::TextOut(hdc, 10, 10, szText, _tcslen(szText));
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
	{
		if (::IsIconic(hWnd))
			return 0;
		SYSTEMTIME time;
		::GetLocalTime(&time);
		HDC hdc = ::GetDC(hWnd);
		SetIsotropic(hdc, s_cxClient, s_cyClient);
		COLORREF crfColor = ::GetSysColor(COLOR_3DFACE);
		if (time.wMinute != s_nPreMinute)
		{
			DrawHand(hdc, 200, 8, s_nPreHour * 30 + s_nPreMinute / 2, crfColor);
			DrawHand(hdc, 400, 6, s_nPreMinute * 6, crfColor);
			s_nPreHour = time.wHour;
			s_nPreMinute = time.wMinute;
		}
		if (time.wSecond != s_nPreSecond)
		{
			DrawHand(hdc, 400, 1, s_nPreSecond * 6, crfColor);
			DrawHand(hdc, 400, 1, time.wSecond * 6, RGB(0, 0, 0));
			DrawHand(hdc, 200, 8, time.wHour * 30 + time.wMinute / 2, RGB(0, 0, 0));
			DrawHand(hdc, 400, 6, time.wMinute * 6, RGB(0, 0, 0));
			s_nPreSecond = time.wSecond;
		}
		break;
	}
	case WM_CLOSE:
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
		s_cxClient = LOWORD(lParam);
		s_cyClient = HIWORD(lParam);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
