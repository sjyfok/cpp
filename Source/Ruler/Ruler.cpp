#include <afxwin.h>
#include <tchar.h>
#include "Ruler.h"


CMyApp myApp;

#define SEGMENTS	(500)
#define PI			(3.1415926)
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("Ruler"));
}

void CMainWindow::OnPaint()
{
	//CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	//CPaintDC dc(this);
	//CPen *oldpen = dc.SelectObject(&pen);
	//CRect Rect;
	//GetClientRect(&Rect);
	//int nWidth = Rect.Width();
	//int nHeight = Rect.Height();
	//CPoint aPoint[SEGMENTS];
	//for (int i = 0; i < SEGMENTS; i++)
	//{
	//	aPoint[i].x = (i*nWidth) / SEGMENTS;
	//	aPoint[i].y = (int)((nHeight / 2)*(1 - (sin((2 * PI*i) / SEGMENTS))));
	//}
	//dc.Polyline(aPoint, SEGMENTS);
	//CRect rect(0, 0, 200, 100);
	//CPoint point1(0, -500);
	//CPoint point2(-500, 0);
	//
	//dc.Rectangle(&rect);
	//dc.Arc(rect, point2, point1);
	////dc.ArcTo(&rect, point1, point2);
	//POINT bPoint[4] = { 120, 100, 120, 200, 250, 150, 500, 40 };
	//POINT cPoint[4] = { 120, 100, 50, 350, 250, 200, 500, 40 };
	//dc.PolyBezier(bPoint, 4);
	//dc.PolyBezier(cPoint, 4);
	//////
	//int nRevenues[4] = { 125, 376, 252, 184 };
	//dc.SetViewportOrg(Rect.Width() / 2, Rect.Height() / 2);

	//int nTotal = 0;

	//for (int i = 0; i < 4; i++)
	//	nTotal += nRevenues[i];
	//
	//int x1 = 0;
	//int y1 = -1000;
	//int nSum = 0;

	//for (int i = 0; i < 4; i++)
	//{
	//	nSum += nRevenues[i];
	//	double rad = ((double)(nSum * 2 * PI) / (double)nTotal) + PI;
	//	int x2 = (int)(sin(rad) * 1000);
	//	int y2 = (int)(cos(rad) * 1000 * 3) / 4;
	//	dc.Pie(-200, -150, 200, 150, x1, y1, x2, y2);
	//	x1 = x2;
	//	y1 = y2;
	//}
	//dc.SelectObject(oldpen);

	//LOGBRUSH lb;
	//lb.lbStyle = BS_SOLID;
	//lb.lbColor = RGB(0, 255, 0);
	//CPen pen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 16, &lb);

	//dc.BeginPath();
	//dc.MoveTo(0, 0);
	//dc.LineTo(100, 200);
	//dc.LineTo(200, 100);
	//dc.CloseFigure();
	//dc.EndPath();
	//dc.StrokePath();

	//阴影效果
	/*CRect rect;
	GetClientRect(&rect);
	CFont font;
	font.CreatePointFont(720, _T("Arial"));

	CPaintDC dc(this);
	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	CString string = _T("Hello, MFC");
	
	rect.OffsetRect(16, 16);
	dc.SetTextColor(RGB(192, 192, 192));
	dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	rect.OffsetRect(-16, -16);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
	//旋转文本
	/*CRect rect;
	GetClientRect(&rect);
	CPaintDC dc(this);
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	dc.SetBkMode(TRANSPARENT);
	
	for (int i = 0; i < 3600; i += 150)
	{
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = 160; 
		lf.lfWeight = FW_BOLD;
		lf.lfEscapement = i;
		lf.lfOrientation = i;
		::lstrcpy(lf.lfFaceName, _T("Arial"));

		CFont font;
		font.CreatePointFontIndirect(&lf);

		CFont *pOldFont = dc.SelectObject(&font);
		dc.TextOut(0, 0, CString(_T("Hello, MFC")));
		dc.SelectObject(pOldFont);
	}*/
	CPaintDC dc(this);
	dc.SetMapMode(MM_LOENGLISH);
	dc.SetTextAlign(TA_CENTER | TA_BOTTOM);
	dc.SetBkMode(TRANSPARENT);

	CBrush brush(RGB(255, 255, 0));
	CBrush *pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(100, -100, 1300, -200);
	dc.SelectObject(pOldBrush);
	
	for (int i = 125; i < 1300; i += 25)
	{
		dc.MoveTo(i, -192);
		dc.LineTo(i, -200);
	}

	for (int i = 150; i < 1300; i += 50)
	{
		dc.MoveTo(i, -184);
		dc.LineTo(i, -200);
	}

	for (int i = 200; i < 1300; i += 100)
	{
		dc.MoveTo(i, -175);
		dc.LineTo(i, -200);
		CString string;
		string.Format(_T("%d"), (i / 100) - 1);
		dc.TextOut(i, -175, string);
	}

}