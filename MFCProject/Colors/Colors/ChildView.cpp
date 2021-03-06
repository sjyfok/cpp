
// ChildView.cpp: CChildView 类的实现
//

#include "stdafx.h"
#include "Colors.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_nColor = 0;
	m_nShape = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_SHAPE_CIRCLE, &CChildView::OnShapeCircle)
	ON_COMMAND(ID_SHAPE_SQUARE, &CChildView::OnShapeSquare)
	ON_COMMAND(ID_SHAPE_TRIANGLE, &CChildView::OnShapeTriangle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_CIRCLE, &CChildView::OnUpdateShapeCircle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_SQUARE, &CChildView::OnUpdateShapeSquare)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_TRIANGLE, &CChildView::OnUpdateShapeTriangle)
	ON_COMMAND_RANGE(ID_COLOR_RED, ID_COLOR_BLUE, &CChildView::OnColor)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLOR_RED, ID_COLOR_BLUE, &CChildView::OnUpdateCOlor)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

const COLORREF CChildView::m_clrColors[5] = {
	RGB(255, 0, 0),
	RGB(255, 255, 0),
	RGB(0, 255, 0),
	RGB(0, 255, 255),
	RGB(0, 0, 255),
};

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

	CBrush brush(m_clrColors[m_nColor]);
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



void CChildView::OnShapeCircle()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 0;
	Invalidate();
}


void CChildView::OnShapeSquare()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 2;
	Invalidate();
}


void CChildView::OnShapeTriangle()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 1;
	Invalidate();
}


void CChildView::OnUpdateShapeCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 0);
}


void CChildView::OnUpdateShapeSquare(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 2);
}


void CChildView::OnUpdateShapeTriangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 1);
}

void CChildView::OnUpdateCOlor(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_COLOR_RED == m_nColor);
}

void CChildView::OnColor(UINT nID)
{
	m_nColor = nID - ID_COLOR_RED;
	Invalidate();
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width() / 2;
	int cy = rcClient.Height() / 2;
	CRect rcShape(cx - 45, cy - 45, cx + 45, cy + 45);
	CPoint pos = point;
	ScreenToClient(&pos);

	CPoint points[3];
	BOOL bShapeClicked = FALSE;
	int dx, dy;
	switch (m_nShape)
	{
	case 0://circle
		dx = pos.x - cx;
		dy = pos.y - cy;
		if ((dx*dx) + (dy*dy) <= (45 * 45))
			bShapeClicked = TRUE;
		break;
	case 1:
		if (rcShape.PtInRect(pos))
		{
			dx = min(pos.x - rcShape.left, rcShape.right - pos.x);
			if ((rcShape.bottom - pos.y) < (2 * dx))
				bShapeClicked = TRUE;
		}
		break;
	case 2:
		if (rcShape.PtInRect(pos))
			bShapeClicked = TRUE;
		break;
	default:
		break;
	}
	if (bShapeClicked)
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu *pContextMenu = menu.GetSubMenu(0);

		for (int i = 0; i < 5; i++)
		{
			pContextMenu->ModifyMenuW(ID_COLOR_RED + i,
				MF_BYCOMMAND | MF_OWNERDRAW, ID_COLOR_RED + i);
		}
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
			TPM_RIGHTALIGN, point.x, point.y, AfxGetMainWnd());
		return;
	}
	CWnd::OnContextMenu(pWnd, point);
}
