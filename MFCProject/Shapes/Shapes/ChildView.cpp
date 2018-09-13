
// ChildView.cpp: CChildView 类的实现
//

#include "stdafx.h"
#include "Shapes.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_nShape = 1;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	CPoint points[3];
	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width() / 2;
	int cy = rcClient.Height() / 2;
	CRect rcShape(cx - 45, cy - 45, cx + 45, cy + 45);

	CBrush brush(RGB(255, 0, 0));
	CBrush *pOldBrush = dc.SelectObject(&brush);

	switch (m_nShape)
	{
	case 0:
		dc.Ellipse(rcShape);
		break;
	case 1:
		points[0].x = cx - 45;
		points[0].y = cy + 45;
		points[1].x = cx;
		points[1].y = cy - 45;
		points[2].x = cx + 45;
		points[2].y = cy + 45;
		dc.Polygon(points, 3);
		break;
	case 2:
		dc.Rectangle(rcShape);
		break;
	}
	dc.SelectObject(pOldBrush);
	// 不要为绘制消息而调用 CWnd::OnPaint()
}

