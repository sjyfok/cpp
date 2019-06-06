#include "stdafx.h"
#include "Boxman_EditerWnd.h"
#include "resource.h"

extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern int MAP_SMALL_SQUARE_SIZE;

#define MAP_BACKGROUP		(48)
#define MAP_WHITEWALL		(49)
#define MAP_BLUEWALL		(50)
#define MAP_BALL			(51)
#define MAP_YELLOWBOX		(52)
#define MAP_REDBOX			(53)
#define MAP_MANWALL			(54)
#define MAP_MANBALL			(55)

IMPLEMENT_DYNCREATE(CBoxman_EditerWnd, CFrameWnd)

CBoxman_EditerWnd::CBoxman_EditerWnd()
{
}


CBoxman_EditerWnd::~CBoxman_EditerWnd()
{
}

BOOL CBoxman_EditerWnd::CreateExToolBar(void)
{
	CImageList img;
	CString str;
	if (!m_wndToolBar.CreateEx(this))
	{
		return -1;
	}
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT | CBRS_TOOLTIPS |
		TBSTYLE_TRANSPARENT | TBBS_CHECKBOX);
	m_wndToolBar.SetButtons(NULL, 6);
	img.Create(28, 28, ILC_COLOR8 | ILC_MASK, 2, 2);
	img.SetBkColor(RGB(0, 0, 102));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_WALL));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_PATH));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_DISTINATION));
	img.Add(AfxGetApp()->LoadIconW(IDR_ICON_BOX));
	img.Add(AfxGetApp()->LoadIconW(IDR_ICON_MAN));
	img.Add(AfxGetApp()->LoadIconW(IDR_ICON_BACKGROUND));
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();
	
	m_wndToolBar.SetButtonInfo(0, ID_MENU_MAP_WHITEWALL, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, _T("围墙"));

	m_wndToolBar.SetButtonInfo(1, ID_MENU_MAP_BLUEWALL, TBSTYLE_BUTTON, 1);
	m_wndToolBar.SetButtonText(1, _T("通道"));

	m_wndToolBar.SetButtonInfo(2, ID_MENU_MAP_BALL, TBSTYLE_BUTTON, 2);
	m_wndToolBar.SetButtonText(2, _T("目的地"));

	m_wndToolBar.SetButtonInfo(3, ID_MENU_MAP_YELLOWBOX, TBSTYLE_BUTTON, 3);
	m_wndToolBar.SetButtonText(3, _T("箱子"));

	m_wndToolBar.SetButtonInfo(4, ID_MENU_MAP_MAN_WALL_BALL, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonText(4, _T("工人"));
	
	m_wndToolBar.SetButtonInfo(5, ID_MENU_MAP_BKGROUND, TBSTYLE_BUTTON, 5);
	m_wndToolBar.SetButtonText(5, _T("背景"));

	CRect rectToolBar;
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(26, 26));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	int x = GetSystemMetrics(SM_CXSCREEN) / 2 + 100;
	int y = GetSystemMetrics(SM_CYSCREEN) / 3 + 100;
	CPoint pt(x, y);
	FloatControlBar(&m_wndToolBar, pt);
	return TRUE;
}
BEGIN_MESSAGE_MAP(CBoxman_EditerWnd, CFrameWnd)
	ON_COMMAND(ID_MENU_MAP_BALL, &CBoxman_EditerWnd::OnMenuMapBall)
	ON_COMMAND(ID_MENU_MAP_BLUEWALL, &CBoxman_EditerWnd::OnMenuMapBluewall)
	ON_COMMAND(ID_MENU_MAP_MAN_WALL_BALL, &CBoxman_EditerWnd::OnMenuMapManWallBall)
	ON_COMMAND(ID_MENU_MAP_WHITEWALL, &CBoxman_EditerWnd::OnMenuMapWhitewall)
	ON_COMMAND(ID_MENU_MAP_YELLOWBOX, &CBoxman_EditerWnd::OnMenuMapYellowbox)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_SAVE_MAP, &CBoxman_EditerWnd::OnMenuSaveMap)
END_MESSAGE_MAP()


void CBoxman_EditerWnd::OnMenuMapBall()
{
	// TODO: 在此添加命令处理程序代码
	m_now_Select = MAP_BALL;
}


void CBoxman_EditerWnd::OnMenuMapBluewall()
{
	// TODO: 在此添加命令处理程序代码
	m_now_Select = MAP_BLUEWALL;
}


void CBoxman_EditerWnd::OnMenuMapManWallBall()
{
	// TODO: 在此添加命令处理程序代码
	m_now_Select = MAP_MANWALL;
}




void CBoxman_EditerWnd::OnMenuMapWhitewall()
{
	// TODO: 在此添加命令处理程序代码
	m_now_Select = MAP_WHITEWALL;
}


void CBoxman_EditerWnd::OnMenuMapYellowbox()
{
	// TODO: 在此添加命令处理程序代码
	m_now_Select = MAP_YELLOWBOX;
}


void CBoxman_EditerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x, y;

	m_bMouseDown = TRUE;
	x = point.x / MAP_SMALL_SQUARE_SIZE;
	y = point.y / MAP_SMALL_SQUARE_SIZE;

	m_boxManEdit.ChangeMap(x, y, m_now_Select);
	Invalidate(FALSE);
	CFrameWnd::OnLButtonDown(nFlags, point);
}


void CBoxman_EditerWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
	CDC dcMemory;

	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	if (!dc.IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right,
				m_rcClient.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				m_boxManEdit.DrawMap(&dcMemory);

				int x = m_mousePoint.x - MAP_SMALL_SQUARE_SIZE / 2;
				int y = m_mousePoint.y - MAP_SMALL_SQUARE_SIZE / 2;
				m_boxManEdit.DrawMouseCursor(x, y, m_now_Select, &dcMemory);
				dc.BitBlt(m_rcClient.left, m_rcClient.top,
					m_rcClient.right, m_rcClient.bottom, &dcMemory, 0, 0, SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}
}


void CBoxman_EditerWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bMouseDown = FALSE;

	CFrameWnd::OnLButtonUp(nFlags, point);
}


void CBoxman_EditerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseDown)
	{
		int x, y;
		x = point.x / MAP_SMALL_SQUARE_SIZE;
		y = point.y / MAP_SMALL_SQUARE_SIZE;
		m_boxManEdit.ChangeMap(x, y, m_now_Select);
		m_mousePoint = point;
	}
	Invalidate(FALSE);
	CFrameWnd::OnMouseMove(nFlags, point);
}


void CBoxman_EditerWnd::OnMenuSaveMap()
{
	// TODO: 在此添加命令处理程序代码
	m_boxManEdit.SaveMap();
}
