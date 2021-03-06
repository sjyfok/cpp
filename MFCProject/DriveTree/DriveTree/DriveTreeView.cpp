
// DriveTreeView.cpp: CDriveTreeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DriveTree.h"
#endif

#include "DriveTreeDoc.h"
#include "DriveTreeView.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ILI_HARD_DISK		(0)
#define ILI_FLOPPY	(1)
#define ILI_CD_ROM	(2)
#define ILI_NET_DRIVE	(3)
#define ILI_CLOSED_FLODER	(4)
#define ILI_OPEN_FLODER		(5)

// CDriveTreeView

IMPLEMENT_DYNCREATE(CDriveTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CDriveTreeView, CTreeView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDriveTreeView 构造/析构

CDriveTreeView::CDriveTreeView()
{
	// TODO: 在此处添加构造代码

}

CDriveTreeView::~CDriveTreeView()
{
}

BOOL CDriveTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}


void CDriveTreeView::OnDraw(CDC* /*pDC*/)
{
	CDriveTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CDriveTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_ilDrives.Create(IDB_DRIVEIMAGE, 16, 1, RGB(255, 0, 255));
	GetTreeCtrl().SetImageList(&m_ilDrives, TVSIL_NORMAL);

	AddDrives();
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(sizeof(szPath) / sizeof(TCHAR), szPath);
	CString strPath = szPath;
	strPath = strPath.Left(3);

	HTREEITEM hItem = GetTreeCtrl().GetNextItem(NULL, TVGN_ROOT);	
	while (hItem != NULL)
	{
		if (GetTreeCtrl().GetItemText(hItem) == strPath)
		{
			break;
		}
		hItem = GetTreeCtrl().GetNextSiblingItem(hItem);
	}
	if (hItem != NULL)
	{
		GetTreeCtrl().Expand(hItem, TVE_EXPAND);
		GetTreeCtrl().Select(hItem, TVGN_CARET);
	}
}


// CDriveTreeView 打印

BOOL CDriveTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDriveTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDriveTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDriveTreeView 诊断

#ifdef _DEBUG
void CDriveTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDriveTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDriveTreeDoc* CDriveTreeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDriveTreeDoc)));
	return (CDriveTreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CDriveTreeView 消息处理程序

int CDriveTreeView::AddDrives()
{
	int nPos = 0;
	int nDriveAdded = 0;
	CString string = _T("?:\\");
	DWORD dwDriveList = ::GetLogicalDrives();

	while (dwDriveList)
	{
		if (dwDriveList & 1)
		{
			string.SetAt(0, _T('A') + nPos);
			if (AddDriveItem(string))
			{
				nDriveAdded++;
			}
		}		
		dwDriveList >>= 1;
		nPos++;
	}
	return nDriveAdded;
}

BOOL CDriveTreeView::AddDriveItem(LPCTSTR pszDrive)
{
	CString string;
	HTREEITEM hItem;

	UINT nType = ::GetDriveType(pszDrive);
	switch (nType)
	{
	default:
		break;
	case DRIVE_REMOVABLE:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_FLOPPY, ILI_FLOPPY);
		GetTreeCtrl().InsertItem(_T(" "), ILI_CLOSED_FLODER, ILI_CLOSED_FLODER, hItem);
		break;
	case DRIVE_FIXED:
	case DRIVE_RAMDISK:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_HARD_DISK, ILI_HARD_DISK);
		SetButtonState(hItem, pszDrive);
		break;
	case DRIVE_REMOTE:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_NET_DRIVE, ILI_NET_DRIVE);
		SetButtonState(hItem, pszDrive);
		break;
	case DRIVE_CDROM:
		hItem = GetTreeCtrl().InsertItem(pszDrive, ILI_CD_ROM, ILI_CD_ROM);
		GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FLODER, ILI_CLOSED_FLODER, hItem);
		break;
	}
	return TRUE;
}

BOOL CDriveTreeView::SetButtonState(HTREEITEM hItem, LPCTSTR pszPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	BOOL bResult = FALSE;

	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");
	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE)
	{
		return bResult;
	}
	do
	{
		if (fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			CString strComp = (LPCTSTR)&fd.cFileName;
			if ((strComp != _T("."))&&(strComp != _T("..")))
			{
				GetTreeCtrl().InsertItem(_T(""), ILI_CLOSED_FLODER, ILI_CLOSED_FLODER, hItem);
				bResult = TRUE;
				break;
			}
		}
	} while (::FindNextFile(hFind, &fd));
	::FindClose(hFind);
	return bResult;
}