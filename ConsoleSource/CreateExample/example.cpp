#include <iostream>
#include <Windows.h>
#include "example.h"

CMyApp theApp;

using namespace std;


BOOL CMyApp::InitInstance()
{
	//::MessageBox(NULL, "主线程开始执行!", "CMyApp::InitInstance", 0);
	//	return FALSE;

	m_pMainWnd = new CMyWnd;
	::ShowWindow(*m_pMainWnd, this->m_nCmdShow);
	::UpdateWindow(*m_pMainWnd);
	return TRUE;
}


CMyWnd::CMyWnd()
{
	LPCTSTR lpszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_3DFACE + 1));
	CreateEx(WS_EX_CLIENTEDGE, lpszClassName, "框架程序测创建的窗口", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
}

LRESULT CMyWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCDESTROY)
	{
		::PostQuitMessage(0);
		delete this;
		return 0;
	}
	return Default();
}

//int CMyApp::ExitInstance()
//{
//	::MessageBox(NULL, "主线程将要退出!", "CMyApp::ExitInstance", MB_OK);
//	return 0;
//}