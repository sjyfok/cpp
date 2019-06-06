// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MdiSquares.h"
#include "SquaresDoc.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "TestView.h"
#include "TestScroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_WINDOW_NEW, &CMainFrame::OnWindowNew)
//ON_COMMAND(AFX_ID_PREVIEW_CLOSE, &CMainFrame::OnAfxIdPreviewClose)
ON_COMMAND(ID_WINDOW_NEW, &CMainFrame::OnWindowNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



//void CMainFrame::OnWindowNew()
//{
//	// TODO: 在此添加命令处理程序代码
//}


//void CMainFrame::OnAfxIdPreviewClose()
//{
//	// TODO: 在此添加命令处理程序代码
//}

extern CMultiDocTemplate* pDocTemplate;
void CMainFrame::OnWindowNew()
{
	// TODO: 在此添加命令处理程序代码
	
	//static CMultiDocTemplate* pDocTemple;
	//static BOOL bChildCreated = FALSE;
	//if (FALSE == bChildCreated)
	//{
	//	AfxMessageBox("Hello1");
	//	pDocTemple = new CMultiDocTemplate(
	//		IDR_MDISQUTYPE,
	//		RUNTIME_CLASS(CSquaresDoc),
	//		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	//		RUNTIME_CLASS(CTestScroll));
	//		if (!pDocTemple)
	//	{
	//		AfxMessageBox(_T("Can't Create new MultiDocTemplate!\n"));
	//		return;
	//	}
	//	AfxGetApp()->AddDocTemplate(pDocTemple);

		CMDIChildWnd* pChildActive = MDIGetActive();
		CSquaresDoc* pDoc = (CSquaresDoc*)pChildActive->GetActiveDocument();
		CMDIChildWnd* pColorChild = (CMDIChildWnd*)pDocTemplate->CreateNewFrame(
			pDoc, NULL);
		if (!pColorChild)
		{
			AfxMessageBox(_T("Can't Create new Child Frame!\n"));
			return;
		}
		pDocTemplate->InitialUpdateFrame(pColorChild, pDoc);
		MDITile(MDITILE_ZORDER);
	/*}*/

}
