#include <Windows.h>
#include <string>
#include "resource.h"


#define IDT_TIMERDEMO		(1)

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND hWnd);
void SetIsotropic(HDC hdc, int cx, int cy);
void DrawClockFace(HDC hdc);
void DrawHand(HDC hdc, int nLenth, int nWidth, int nDegrees, COLORREF clrColor);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	char szClassName[] = "MainWClass";
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	//wndclass.hIcon = ::LoadIcon(hInstance, (LPSTR)IDI_TYPER);
	wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	//wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	//wndclass.lpszMenuName = (LPSTR)IDR_TYPER ;  //加载菜单的方法1  
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;
	
	::RegisterClassEx(&wndclass);

	HWND hWnd = ::CreateWindowEx(
		0,
		szClassName,
		"时钟",
		//WS_OVERLAPPEDWINDOW,
		WS_POPUP | WS_SYSMENU | WS_SIZEBOX,
		100,//CW_USEDEFAULT,
		100,//CW_USEDEFAULT,
		300,//CW_USEDEFAULT,
		300,//CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (hWnd == NULL)
	{
		::MessageBox(NULL, "创建窗口出错!", "error", MB_OK);
		return -1;
	}
	::ShowWindow(hWnd, nCmdShow);
	::UpdateWindow(hWnd);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

static int s_nPerHour;
static int s_nPerMinute;
static int s_nPerSecond;

static int s_cxClient;
static int s_cyClient;

static int s_bTopMost;

const int IDM_TOPMOST = 101;
const int IDM_HELP = 100;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char szText[56];

	switch (message)
	{
	default:
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_CREATE:   //加载菜单的方法2
		{
		SYSTEMTIME time;
		::GetLocalTime(&time);
		s_nPerHour = time.wHour % 12;
		s_nPerMinute = time.wMinute;
		s_nPerSecond = time.wSecond;
		::SetTimer(hWnd, IDT_TIMERDEMO, 1000, NULL);
		HMENU hSysMenu;
		hSysMenu = ::GetSystemMenu(hWnd, FALSE);
		::AppendMenu(hSysMenu, MF_SEPARATOR, 0, NULL);
		::AppendMenu(hSysMenu, MF_STRING, IDM_TOPMOST, "总在最前面");
		::AppendMenu(hSysMenu, MF_STRING, IDM_HELP, "帮助");
		return 0;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			break;
		case ID_FILE_EXIT:
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_TIMER:
		{
			if (::IsIconic(hWnd))
			{
				return 0;
			}
			SYSTEMTIME time;
			::GetLocalTime(&time);
			HDC hdc = ::GetDC(hWnd);
			SetIsotropic(hdc, s_cxClient, s_cyClient);
			COLORREF crfColor = RGB(255, 255, 255);//::GetSysColor(WHITE_BRUSH);
			if (time.wMinute != s_nPerMinute)
			{
				DrawHand(hdc, 200, 8, s_nPerHour * 30 + s_nPerMinute / 2, crfColor);
				DrawHand(hdc, 400, 6, s_nPerMinute * 6, crfColor);
				s_nPerHour = time.wHour;
				s_nPerMinute = time.wMinute;
			}
			if (time.wSecond != s_nPerSecond)
			{
				DrawHand(hdc, 400, 1, s_nPerSecond * 6, crfColor);

				DrawHand(hdc, 400, 1, time.wSecond * 6, RGB(0, 0, 0));
				DrawHand(hdc, 200, 8, time.wHour*30+time.wMinute/2, RGB(0, 0, 0));
				DrawHand(hdc, 400, 6, time.wMinute * 6, RGB(0, 0, 0));
				s_nPerSecond = time.wSecond;
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		/*{
			if (bSetTimer)
			{
				::KillTimer(hWnd, IDT_TIMERDEMO);
				bSetTimer = FALSE;
			}
			else
			{
				if (::SetTimer(hWnd, IDT_TIMERDEMO, 350, NULL)==0)
				{
					::MessageBox(hWnd, "安装定时器失败!", "Timer", MB_OK);
				}
				else
				{
					bSetTimer = TRUE;
				}
			}
		}*/
		break;
	case WM_CLOSE:
		{
			::KillTimer(hWnd, IDT_TIMERDEMO);
			::DestroyWindow(hWnd);
			return 0;
		}
	case WM_SIZE:
		s_cxClient = LOWORD(lParam);
		s_cyClient = HIWORD(lParam);
		return 0;
	case WM_NCHITTEST:
		UINT nHitTest;
		nHitTest = ::DefWindowProc(hWnd, message, wParam, lParam);
		if (nHitTest == HTCLIENT && ::GetAsyncKeyState(MK_LBUTTON)<0)
			nHitTest = HTCAPTION;
		return nHitTest;
	case WM_CONTEXTMENU:
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		{
			HMENU hSysMenu = ::GetSystemMenu(hWnd, FALSE);
			int nID = ::TrackPopupMenu(hSysMenu, TPM_LEFTALIGN | TPM_RETURNCMD,
				pt.x, pt.y, 0, hWnd, NULL);
			if (nID)
				::SendMessage(hWnd, WM_SYSCOMMAND, nID, 0);
			return 0;
		}
	case WM_SYSCOMMAND:
	{
		int nID = wParam;
		if (nID == IDM_HELP)
		{
			::MessageBox(hWnd, "一个时钟的例子", "时钟", 0);
		}
		else if (nID == IDM_TOPMOST)
		{
			HMENU hSysMenu = ::GetSystemMenu(hWnd, FALSE);
			if (s_bTopMost)
			{
				::CheckMenuItem(hSysMenu, IDM_TOPMOST, MF_UNCHECKED);
				::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);
				s_bTopMost = FALSE;
			}
			else
			{
				::CheckMenuItem(hSysMenu, IDM_TOPMOST, MF_CHECKED);
				::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0
					, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);
				s_bTopMost = TRUE;
			}
		}
		return ::DefWindowProc(hWnd, WM_SYSCOMMAND, nID, 0) ;
	}
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}


void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(hWnd, &ps);
	RECT rt;
	GetClientRect(hWnd, &rt);
	SetIsotropic(hdc, rt.right - rt.left, rt.bottom - rt.top);
	DrawClockFace(hdc);
	
	DrawHand(hdc, 200, 8, s_nPerHour * 30 + s_nPerMinute / 2, RGB(0, 0, 0));
	DrawHand(hdc, 400, 6, s_nPerMinute * 6, RGB(0, 0, 0));
	DrawHand(hdc, 400, 1, s_nPerSecond * 6, RGB(0, 0, 0));

	//::SetMapMode(hdc, MM_ANISOTROPIC);
	//::SetWindowExtEx(hdc, 500, 500, NULL);
	//::SetViewportExtEx(hdc, 0, 0, NULL);
	//::SelectObject(hdc, ::GetStockObject(BLACK_BRUSH));
	//::Ellipse(hdc, 0, 0, 500, 500);
	//TextOut(hdc, 10, 10, "hello", sizeof("hello"));
	::EndPaint(hWnd, &ps);
}

void SetIsotropic(HDC hdc, int cx, int cy)
{
	::SetMapMode(hdc, MM_ISOTROPIC);  //设置映射模式
	::SetWindowExtEx(hdc, 1000, 1000, NULL);  //设置逻辑长度
	::SetViewportExtEx(hdc, cx, -cy, NULL);  //设置坐标系的正负
	::SetViewportOrgEx(hdc, cx / 2, cy / 2, NULL); //设置坐标原点
}

void DrawClockFace(HDC hdc)
{
	const int SQUARESIZE = 20;
	static POINT pt[] = {
		0, 450,
		255, 390,
		390, 225,
		450, 0,
		390, -225,
		225, -390,
		0,	-450,
		-225, -390,
		-390,-225,
		-450, 0,
		-390, 225,
		-225, 390
	};

	SelectObject(hdc, ::GetStockObject(BLACK_BRUSH));
	for (int  i = 0; i < 12; i++)
	{
		::Ellipse(hdc, pt[i].x - SQUARESIZE, pt[i].y + SQUARESIZE,
			pt[i].x + SQUARESIZE, pt[i].y - SQUARESIZE);
	}
}

void DrawHand(HDC hdc, int nLenth, int nWidth, int nDegrees, COLORREF clrColor)
{
	double nRadians = (double)nDegrees*0.0174533;

	POINT pt[2];
	pt[0].x = (int)(nLenth*sin(nRadians));
	pt[0].y = (int)(nLenth*cos(nRadians));
	pt[1].x = -pt[0].x / 5;
	pt[1].y = -pt[0].y / 5;

	HPEN hPen = ::CreatePen(PS_SOLID, nWidth, clrColor);
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
	::MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
	::LineTo(hdc, pt[1].x, pt[1].y);
	::SelectObject(hdc, hOldPen);
	::DeleteObject(hPen);
}