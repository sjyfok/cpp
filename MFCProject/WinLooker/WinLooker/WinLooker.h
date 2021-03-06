
// WinLooker.h: WinLooker 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CWinLookerApp:
// 有关此类的实现，请参阅 WinLooker.cpp
//

class CMyApp : public CWinApp
{
//public:
//	CMyApp();


// 重写
public:
	virtual BOOL InitInstance();
	//virtual int ExitInstance();

// 实现

//public:
//	afx_msg void OnAppAbout();
//	DECLARE_MESSAGE_MAP()
};

extern CMyApp theApp;

#define BUFFER_SIZE 256

class CWindowInfo
{
public:
	CWindowInfo();
	// 更新数据
	void GetInfo(HWND hWnd);
	// 绘制矩形外框
	void DrawFrame();
	// 擦除矩形外框
	void EraseFrame();

	HWND m_hWnd;
	CString  m_szWindowCaption;// [BUFFER_SIZE];
	CString  m_szWindowClass;// [BUFFER_SIZE];
	CString m_szExeFile;// [MAX_PATH];
};
class CMainWindow :public CWnd
{
protected:
	int m_cxChar;	// 字符的平均宽度
	int m_cyChar;	// 字符的高
	int m_cyLine;	// 一行字符占用的空间的垂直长度

	HCURSOR m_hCursorArrow;		// 通常模式下使用的光标句柄（箭头光标）
	HCURSOR m_hCursorTarget;	// 用户选定窗口时使用的光标句柄（自定义光标）

	RECT m_rcMouseDown;		// 接受鼠标下按的方框的位置坐标
	RECT m_rcMsgBoxBorder;		// 消息框边框的位置坐标
	RECT m_rcMsgBox;		// 消息框的位置坐标
	CPoint m_ptHeaderOrigin;	// 绘制标题的起始位置

	BOOL m_bCatchMouseDown;		// 是否捕捉到鼠标下按事件
	CWindowInfo m_wndInfo;		// 一个目标窗口对象
public:
	CMainWindow();

protected:
	void DrawMouseInput(CDC* pDC);
	void DrawMsg(CDC* pDC);
	void DrawMsgHeader(CDC* pDC);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};