// LoadMapDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "my_BoxMan.h"
#include "LoadMapDlg.h"
#include "afxdialogex.h"


// CLoadMapDlg 对话框

IMPLEMENT_DYNAMIC(CLoadMapDlg, CDialog)

CLoadMapDlg::CLoadMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_iMisslionLev(0)
{

}

CLoadMapDlg::~CLoadMapDlg()
{
}

void CLoadMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iMisslionLev);
}


BEGIN_MESSAGE_MAP(CLoadMapDlg, CDialog)
END_MESSAGE_MAP()


// CLoadMapDlg 消息处理程序
