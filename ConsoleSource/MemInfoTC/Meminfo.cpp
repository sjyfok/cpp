#include <iostream>
#include <Windows.h>
#include "Meminfo.h"
#include "../wincommon/_afxmsg_.h"
#define IDT_TIMER  (101)

CMyApp theApp;


BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	::ShowWindow(*m_pMainWnd, this->m_nCmdShow);
	::UpdateWindow(*m_pMainWnd);
	return TRUE;
}


CMainWindow::CMainWindow()
{
	m_szText[0] = '\0';
	LPCTSTR lpszClassName =  AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_3DFACE + 1) 
		);
	CreateEx(WS_EX_CLIENTEDGE, lpszClassName,
		"内存使用监视器", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 230, NULL, NULL);
}

BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()

BOOL CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	::GetClientRect(m_hWnd, &m_rcInfo);
	m_rcInfo.left = 30;
	m_rcInfo.top = 20;
	m_rcInfo.right = m_rcInfo.right - 30;
	m_rcInfo.bottom = m_rcInfo.bottom - 30;

	::SetTimer(m_hWnd, IDT_TIMER, 500, NULL);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);
	return TRUE;
}

void CMainWindow::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == IDT_TIMER)
	{
		char szBuff[128];
		MEMORYSTATUS ms;
		::GlobalMemoryStatus(&ms);
		m_szText[0] = '\0';
		wsprintf(szBuff, "\n 物理内存总量: %-5dMB", ms.dwTotalPhys / (1024 * 1024));
		strcat_s(m_szText, szBuff);
		wsprintf(szBuff, "\n 可用物理内存: %-5dMB", ms.dwAvailPhys / (1024 * 1024));
		strcat_s(m_szText, szBuff);
		wsprintf(szBuff, "\n\n 虚拟内存总量： %-5d MB", ms.dwTotalVirtual / (1024 * 1024));
		strcat_s(m_szText, szBuff);
		wsprintf(szBuff, "\n 可用虚拟内存： %-5d MB", ms.dwAvailVirtual / (1024 * 1024));
		strcat_s(m_szText, szBuff);
		wsprintf(szBuff, "\n\n 内存使用率： %d%%", ms.dwMemoryLoad);
		strcat_s(m_szText, szBuff);
		// 无效显示文本的区域，以迫使系统发送 WM_PAINT 消息，更新显示信息
		::InvalidateRect(m_hWnd, &m_rcInfo, TRUE);
	}
}

void CMainWindow::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(m_hWnd, &ps);
	// 设置背景为透明模式
	::SetBkMode(hdc, TRANSPARENT);
	// 创建字体
	// CreateFont 函数用指定的属性创建一种逻辑字体。这个逻辑字体能够被选入到任何设备中。
	HFONT hFont = ::CreateFont(12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, \
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
		VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
	// 创建画刷
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0xa0, 0xa0, 0xa0));
	// 将它们选入到设备环境中
	HFONT hOldFont = (HFONT)::SelectObject(hdc, hFont);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
	// 设置文本颜色
	::SetTextColor(hdc, RGB(0x32, 0x32, 0xfa));
	// 画一个圆角矩形
	::RoundRect(hdc, m_rcInfo.left, m_rcInfo.top, m_rcInfo.right, m_rcInfo.bottom, 5, 5);
	// 绘制文本
	::DrawText(hdc, m_szText, strlen(m_szText), &m_rcInfo, 0);
	// 清除资源
	::DeleteObject(::SelectObject(hdc, hOldFont));
	::DeleteObject(::SelectObject(hdc, hOldBrush));
	::EndPaint(m_hWnd, &ps);
}


void CMainWindow::PostNcDestroy()
{
	delete this;
}