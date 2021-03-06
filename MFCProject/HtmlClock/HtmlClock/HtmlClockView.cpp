
// HtmlClockView.cpp: CHtmlClockView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HtmlClock.h"
#endif

#include "HtmlClockDoc.h"
#include "HtmlClockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlClockView

IMPLEMENT_DYNCREATE(CHtmlClockView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlClockView, CHtmlView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHtmlClockView 构造/析构

CHtmlClockView::CHtmlClockView()
{
	// TODO: 在此处添加构造代码

}

CHtmlClockView::~CHtmlClockView()
{
}

BOOL CHtmlClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CHtmlView::PreCreateWindow(cs);
}

void CHtmlClockView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, sizeof(szPath) / sizeof(TCHAR));

	CString string = szPath;
	int nIndex = string.ReverseFind(_T('\\'));
	string = string.Left(nIndex + 1) + _T("Clock.htm");
	Navigate2(string);
}


// CHtmlClockView 打印


void CHtmlClockView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}


void CHtmlClockView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHtmlClockView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHtmlClockView 诊断

#ifdef _DEBUG
void CHtmlClockView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlClockView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlClockDoc* CHtmlClockView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlClockDoc)));
	return (CHtmlClockDoc*)m_pDocument;
}
#endif //_DEBUG


// CHtmlClockView 消息处理程序
