
// BoxMan_Edit.h: BoxMan_Edit 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CBoxManEditApp:
// 有关此类的实现，请参阅 BoxMan_Edit.cpp
//

class CBoxManEditApp : public CWinApp
{
public:
	CBoxManEditApp();

public:
	CWnd * m_pBoxManEditerWnd;
// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:

	DECLARE_MESSAGE_MAP()
};

extern CBoxManEditApp theApp;
