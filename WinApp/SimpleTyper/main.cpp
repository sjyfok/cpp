#include <Windows.h>
#include <string>
#include "resource.h"

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
	//wndclass.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIcon = ::LoadIcon(hInstance, (LPSTR)IDI_TYPER);
	wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	//wndclass.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	//wndclass.lpszMenuName = (LPSTR)IDR_TYPER ;  //���ز˵��ķ���1  
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;
	
	::RegisterClassEx(&wndclass);

	HWND hWnd = ::CreateWindowEx(
		0,
		szClassName,
		"My first Window!",
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
		::MessageBox(NULL, "�������ڳ���!", "error", MB_OK);
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
	char szText[] = "��򵥵Ĵ��ڳ���!";
	static std::string str;
	HMENU hMenu;
	switch (message)
	{
	default:
		break;
	case WM_PAINT:
	{
		//HDC �Լ���һ��ǰ��ɫ�ͱ���ɫ
		//ע�ᴰ����ʱ�趨�ı�����ˢ �������ˢ ʱ��һ����
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = ::BeginPaint(hWnd, &ps);
		::SetTextColor(hdc, RGB(255, 0, 0));
		::SetBkColor(hdc, ::GetSysColor(COLOR_3DFACE));
		::TextOut(hdc, 10, 10, str.c_str(), str.length());

		::EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_CREATE:   //���ز˵��ķ���2
		hMenu = ::LoadMenu(::GetModuleHandle(NULL), (LPCTSTR)IDR_TYPER);
		::SetMenu(hWnd, hMenu);
		::SetWindowText(hWnd, "���ª�Ĵ��ֳ���");
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
	case WM_CHAR:
		str = str + char(wParam);
		::InvalidateRect(hWnd, NULL, 0);
		return 0;
	case WM_LBUTTONDOWN:
	{
		char szPoint[56];
		wsprintf(szPoint, "X=%d,Y=%d", LOWORD(lParam), HIWORD(lParam));
		str = szPoint;
		if (wParam & MK_SHIFT)
		{
			str = str + " Shift Key is down";
		}
		::InvalidateRect(hWnd, NULL, 1);
		return 0;
	}
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

