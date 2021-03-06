
// ScrollTestView.cpp: CScrollTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ScrollTest.h"
#endif

#include "ScrollTestDoc.h"
#include "ScrollTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScrollTestView

IMPLEMENT_DYNCREATE(CScrollTestView, CScrollView)

BEGIN_MESSAGE_MAP(CScrollTestView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CScrollTestView 构造/析构

CScrollTestView::CScrollTestView()
{
	// TODO: 在此处添加构造代码

}

CScrollTestView::~CScrollTestView()
{
}

BOOL CScrollTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CScrollTestView 绘图

void CScrollTestView::OnDraw(CDC* pDC)
{
	CScrollTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CSize size = GetTotalSize();
	CPen pen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen *oldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < 99; i++)
	{
		int y = (i*m_nCellHeight) + m_nCellHeight;
		pDC->MoveTo(0, y);
		pDC->LineTo(size.cx, y);
	}
	for (int j = 0; j < 26; j++)
	{
		int x = (j*m_nCellWidth) + m_nRibbonWidth;
		pDC->MoveTo(x, 0);
		pDC->LineTo(x, size.cy);
	}
	pDC->SelectObject(oldPen);

	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);
	CRect rcTop(0, 0, size.cx, m_nCellHeight);
	pDC->FillRect(rcTop, &brush);
	CRect rcLeft(0, 0, m_nRibbonWidth, size.cy);
	pDC->FillRect(rcLeft, &brush);

	pDC->MoveTo(0, m_nCellHeight);
	pDC->LineTo(size.cx, m_nCellHeight);
	pDC->MoveTo(m_nRibbonWidth, 0);
	pDC->LineTo(m_nRibbonWidth, size.cy);

	pDC->SetBkMode(TRANSPARENT);

	for (int i = 0; i < 99; i++)
	{
		int y = (i*m_nCellHeight) + m_nCellHeight;
		pDC->MoveTo(0, y);
		pDC->LineTo(m_nRibbonWidth, y);
		CString string;
		string.Format(_T("%d"), i + 1);
		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHeight);
		pDC->DrawText(string, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		rect.top++;
		pDC->Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}
	for (int j = 0; j < 26; j++)
	{
		int x = (j*m_nCellWidth) + m_nRibbonWidth;
		pDC->MoveTo(x, 0);
		pDC->LineTo(x, m_nCellHeight);
		CString string;
		string.Format(_T("%c"), j + 'A');
		CRect rect(x, 0, x + m_nCellWidth, m_nCellHeight);
		pDC->DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		rect.left++;
		pDC->Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}
	CRect rect;
	pDC->GetClipBox(&rect);
	int nStartRow = max(0, (rect.top - m_nCellHeight) / m_nCellHeight);
	int nEndRow = min(98, (rect.bottom - 1) / m_nCellHeight);
	int nStartCol = max(0, (rect.left - m_nRibbonWidth) / m_nCellWidth);
	int nEndCol = min(25, ((rect.right + m_nCellWidth - 1) - m_nRibbonWidth) / m_nCellWidth);

	for (int i = nStartRow; i < nEndRow; i++)
		for (int j = nStartCol; j < nEndCol; j++)
		
			DrawAddress(pDC, i, j);
	DrawPointer(pDC, m_nCurrentRow, m_nCurrentCol, TRUE);
}

void CScrollTestView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_nCurrentRow = 0;
	m_nCurrentCol = 0;
	m_bSmooth = FALSE;
	CClientDC dc(this);
	m_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY) / 4;
	m_nRibbonWidth = m_nCellWidth / 2;

	int nWidth = (26 * m_nCellWidth) + m_nRibbonWidth;
	int nHeight = m_nCellWidth * 100;


	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = nWidth;// sizeTotal.cy = 100;
	sizeTotal.cy = nHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CScrollTestView 打印

BOOL CScrollTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CScrollTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CScrollTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CScrollTestView 诊断

#ifdef _DEBUG
void CScrollTestView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScrollTestView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScrollTestDoc* CScrollTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollTestDoc)));
	return (CScrollTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CScrollTestView 消息处理程序
void CScrollTestView::DrawPointer(CDC *pDC, int row, int col, BOOL bHightlight)
{
	CRect rect;
	GetCellRect(row, col, &rect);
	CBrush brush(bHightlight ? RGB(0, 255, 255) : ::GetSysColor(COLOR_WINDOW));

	pDC->FillRect(rect, &brush);
	DrawAddress(pDC, row, col);
}

void CScrollTestView::DrawAddress(CDC *pDC, int row, int col)
{
	CRect rect;
	GetCellRect(row, col, &rect);
	CString string;
	string.Format(_T("%c %d"), col + _T('A'), row + 1);
	pDC->SetBkMode(TRANSPARENT);
	CFont *pOldPen = pDC->SelectObject(&m_font);
	pDC->DrawText(string, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pOldPen);
}

void CScrollTestView::GetCellRect(int row, int col, LPRECT pRect)
{
	pRect->left = m_nRibbonWidth + (col*m_nCellWidth) + 1;
	pRect->top = m_nCellHeight + (row*m_nCellHeight) + 1;
	pRect->right = pRect->left + m_nCellWidth-1;
	pRect->bottom = pRect->top + m_nCellHeight-1;
}

void CScrollTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CScrollView::OnLButtonDown(nFlags, point);
	CPoint pos = point;
	CClientDC dc(this);
	dc.DPtoLP(&pos);
	CSize size = GetTotalSize();
	if (pos.x>m_nRibbonWidth&&pos.x<size.cx&&pos.y>m_nCellHeight&&pos.y<size.cy)
	{
		int row = (pos.y - m_nCellHeight) / m_nCellHeight;
		int col = (pos.x - m_nRibbonWidth) / m_nCellWidth;
		ASSERT(row >= 0 && row <= 98 && col >= 0 && col <= 26);
		DrawPointer(&dc, m_nCurrentRow, m_nCurrentCol, FALSE);
		m_nCurrentRow = row;
		m_nCurrentCol = col;
		DrawPointer(&dc, m_nCurrentRow, m_nCurrentCol, TRUE);
	}
}
