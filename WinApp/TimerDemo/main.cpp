#include <Windows.h>
#include <string>
#include "resource.h"


#define IDT_TIMERDEMO		(1)

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

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
	wndclass.lpszMenuName = (LPSTR)IDR_TYPER ;  //加载菜单的方法1  
	//wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;
	
	::RegisterClassEx(&wndclass);

	HWND hWnd = ::CreateWindowEx(
		0,
		szClassName,
		"定时器的使用",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char szText[56];
	static int nNum, bSetTimer;

	switch (message)
	{
	default:
		break;
	case WM_PAINT:
		{
			//HDC 自己有一套前景色和背景色
			//注册窗口类时设定的背景画刷 和这个画刷 时不一样的
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = ::BeginPaint(hWnd, &ps);

			wsprintf(szText, "计数: %d", nNum);

			::TextOut(hdc, 10, 10, szText, strlen(szText));

			::EndPaint(hWnd, &ps);
			return 0;
		}
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_CREATE:   //加载菜单的方法2
		bSetTimer = FALSE;
		break;
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
		if (wParam == IDT_TIMERDEMO)
		{
			HDC hdc = GetDC(hWnd);
			wsprintf(szText, "计数: %d", nNum++);
			::TextOut(hdc, 10, 10, szText, strlen(szText));
			::MessageBeep(MB_OK);
		}
		return 0;
	case WM_LBUTTONDOWN:
		{
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
		}
		break;
	case WM_CLOSE:
		if (bSetTimer)
		{
			::KillTimer(hWnd, IDT_TIMERDEMO);
		}
		break;
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

