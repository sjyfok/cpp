// TestScroll.cpp: 实现文件
//

#include "stdafx.h"
#include "MdiSquares.h"
#include "TestScroll.h"


// CTestScroll

IMPLEMENT_DYNCREATE(CTestScroll, CScrollView)

CTestScroll::CTestScroll()
{

}

CTestScroll::~CTestScroll()
{
}


BEGIN_MESSAGE_MAP(CTestScroll, CScrollView)
END_MESSAGE_MAP()


// CTestScroll 绘图

void CTestScroll::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CTestScroll::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
	pDC->TextOutA(0, 0, _T("Hello"));
}


// CTestScroll 诊断

#ifdef _DEBUG
void CTestScroll::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestScroll::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestScroll 消息处理程序
