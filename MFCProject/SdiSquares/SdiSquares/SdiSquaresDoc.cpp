
// SdiSquaresDoc.cpp: CSdiSquaresDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SdiSquares.h"
#endif

#include "SdiSquaresDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSdiSquaresDoc

IMPLEMENT_DYNCREATE(CSdiSquaresDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdiSquaresDoc, CDocument)
	ON_COMMAND(ID_COLOR_RED, &CSdiSquaresDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnColorYellow)
	ON_COMMAND(ID_COLOR_GREEN, &CSdiSquaresDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_CYAN, &CSdiSquaresDoc::OnColorCyan)
	ON_COMMAND(ID_COLOR_BLUE, &CSdiSquaresDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_WHITE, &CSdiSquaresDoc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSdiSquaresDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSdiSquaresDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CSdiSquaresDoc::OnUpdateColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSdiSquaresDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CSdiSquaresDoc::OnUpdateColorWhite)
END_MESSAGE_MAP()


// CSdiSquaresDoc 构造/析构

CSdiSquaresDoc::CSdiSquaresDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSdiSquaresDoc::~CSdiSquaresDoc()
{
}

BOOL CSdiSquaresDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_clrCurrentColor = RGB(255, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_clrGrid[i][j] = RGB(255, 255, 255 );
		}
	}
	return TRUE;
}




// CSdiSquaresDoc 序列化

void CSdiSquaresDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar << m_clrGrid[i][j];
			}			
		}
		ar << m_clrCurrentColor;
	}
	else
	{
		// TODO: 在此添加加载代码
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar >> m_clrGrid[i][j];
			}
		}
		ar >> m_clrCurrentColor;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSdiSquaresDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSdiSquaresDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSdiSquaresDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSdiSquaresDoc 诊断

#ifdef _DEBUG
void CSdiSquaresDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdiSquaresDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSdiSquaresDoc 命令


COLORREF CSdiSquaresDoc::GetCurrentColor()
{
	// TODO: 在此处添加实现代码.
	return m_clrCurrentColor;
}


COLORREF CSdiSquaresDoc::GetSquare(int row, int col)
{
	// TODO: 在此处添加实现代码.
	return m_clrGrid[row][col];
}

COLORREF CSdiSquaresDoc::SetSquare(int row, int col, COLORREF clr)
{
	m_clrGrid[row][col] = clr;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
	return clr;
}


void CSdiSquaresDoc::OnColorRed()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(255, 0, 0);
}


void CSdiSquaresDoc::OnColorYellow()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(255, 255, 0);
}


void CSdiSquaresDoc::OnColorGreen()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(0, 255, 0);
}


void CSdiSquaresDoc::OnColorCyan()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(0, 255, 255);
}


void CSdiSquaresDoc::OnColorBlue()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(0, 0, 255);
}


void CSdiSquaresDoc::OnColorWhite()
{
	// TODO: 在此添加命令处理程序代码
	m_clrCurrentColor = RGB(255, 255, 255);
}


void CSdiSquaresDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 0, 0));
}


void CSdiSquaresDoc::OnUpdateColorYellow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorCyan(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 255));
}


void CSdiSquaresDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 0, 255));
}


void CSdiSquaresDoc::OnUpdateColorWhite(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 255));
}
