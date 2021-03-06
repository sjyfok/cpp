
// SketchView.cpp: CSketchView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Sketch.h"
#endif

#include "SketchDoc.h"
#include "SketchView.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchView

IMPLEMENT_DYNCREATE(CSketchView, CView)

BEGIN_MESSAGE_MAP(CSketchView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CSketchView 构造/析构

CSketchView::CSketchView()
{
	// TODO: 在此处添加构造代码
	m_hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CSketchView::~CSketchView()
{
}

BOOL CSketchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSketchView 绘图

void CSketchView::OnDraw(CDC* pDC)
{
	CSketchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect cliRect;
	GetClientRect(&cliRect);
	// TODO: 在此处为本机数据添加绘制代码
	if (pDoc->IsGridVisible())
	{
		for (int x = 25; x < cliRect.right; x+=25)
		{
			for (int y = 25; y < cliRect.bottom; y+=25)
			{
				pDC->SetPixel(x, y, RGB(128, 128, 128));
			}
		}
	}
	int nCount = pDoc->GetLineCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			pDoc->GetLine(i)->Draw(pDC);
		}
	}
}


// CSketchView 打印

BOOL CSketchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSketchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSketchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSketchView 诊断

#ifdef _DEBUG
void CSketchView::AssertValid() const
{
	CView::AssertValid();
}

void CSketchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketchDoc* CSketchView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchDoc)));
	return (CSketchDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchView 消息处理程序


BOOL CSketchView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SetCursor(m_hCursor);
	return TRUE;
	//return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CSketchView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pos = point;
	CClientDC dc(this);
	if (GetDocument()->IsGridVisible())
	{
		pos.x = ((pos.x + 12) / 25) * 25;
		pos.y = ((pos.y + 12) / 25) * 25;
	}
	m_ptFrom = pos;
	m_ptTo = pos;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);	
}


void CSketchView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetCapture() == this)
	{
		CPoint pos = point;
		CClientDC dc(this);

		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y + 12) / 25) * 25;
		}
		if (m_ptTo != pos)
		{
			InvertLine(&dc, m_ptFrom, m_ptTo);
			InvertLine(&dc, m_ptFrom, pos);
			m_ptTo = pos;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CSketchView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetCapture() == this)
	{
		::ReleaseCapture();
		CPoint pos = point;
		CClientDC dc(this);
		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y + 12) / 25) * 25;
		}
		InvertLine(&dc, m_ptFrom, m_ptTo);
		CSketchDoc *pDoc = GetDocument();
		CLine *pLine = pDoc->AddLine(m_ptFrom, m_ptTo);
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSketchView::InvertLine(CDC *pDc, POINT from, POINT to)
{
	int nOldMode = pDc->SetROP2(R2_NOP);
	pDc->MoveTo(from);
	pDc->LineTo(to);
	pDc->SetROP2(nOldMode);
}



void CSketchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (lHint == 0x7C)
	{
		CLine *pLine = (CLine*)pHint;
		ASSERT(pLine->IsKindOf(RUNTIME_CLASS(CLine)));
		CClientDC dc(this);
		pLine->Draw(&dc);
		return;
	}
	CView::OnUpdate(pSender, lHint, pHint);
}
