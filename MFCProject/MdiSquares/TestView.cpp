// TestView.cpp: 实现文件
//

#include "stdafx.h"
#include "MdiSquares.h"
#include "TestView.h"


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CRichEditView)

CTestView::CTestView()
{

}

CTestView::~CTestView()
{
}

BEGIN_MESSAGE_MAP(CTestView, CRichEditView)
END_MESSAGE_MAP()


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestView 消息处理程序


void CTestView::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxMessageBox("Hello2");
	pDC->TextOutA(0, 0, _T("TestView"));
}


void CTestView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}
