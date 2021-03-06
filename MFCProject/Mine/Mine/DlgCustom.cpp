// DlgCustom.cpp: 实现文件
//

#include "stdafx.h"
#include "Mine.h"
#include "DlgCustom.h"
#include "afxdialogex.h"


// CDlgCustom 对话框

IMPLEMENT_DYNAMIC(CDlgCustom, CDialog)

CDlgCustom::CDlgCustom(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_CUSTOM, pParent)
	, m_uHeight(0)
	, m_uWidth(0)
	, m_uNumber(0)
{

}

CDlgCustom::~CDlgCustom()
{
}

void CDlgCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HEIGHT, m_uHeight);
	DDV_MinMaxUInt(pDX, m_uHeight, 9, 16);
	DDX_Text(pDX, IDC_WIDTH, m_uWidth);
	DDV_MinMaxUInt(pDX, m_uWidth, 9, 30);
	DDX_Text(pDX, IDC_NUMBER, m_uNumber);
	DDV_MinMaxUInt(pDX, m_uNumber, 9, 99);
}


BEGIN_MESSAGE_MAP(CDlgCustom, CDialog)
//	ON_EN_CHANGE(IDC_EDIT2, &CDlgCustom::OnEnChangeEdit2)
ON_BN_CLICKED(IDOK, &CDlgCustom::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCustom 消息处理程序


//void CDlgCustom::OnEnChangeEdit2()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialog::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}

void CDlgCustom::InitData(UINT xNum, UINT yNum, UINT mNum)
{
	m_uWidth = xNum;
	m_uHeight = yNum;
	m_uNumber = mNum;
}

void CDlgCustom::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_uWidth < 9)
	{
		m_uWidth = 9;
	}
	if (m_uWidth > 30)
	{
		m_uWidth = 30;
	}
	if (m_uHeight < 9)
	{
		m_uHeight = 9;
	}
	if (m_uHeight > 24)
	{
		m_uHeight = 24;
	}
	if (m_uNumber < 10)
	{
		m_uNumber = 10;
	}
	if (m_uNumber > m_uWidth*m_uHeight)
	{
		m_uNumber = m_uWidth * m_uHeight - 1;
	}

	CMineWnd *pMine = (CMineWnd*)AfxGetMainWnd();
	pMine->SetCustom(m_uWidth, m_uHeight, m_uNumber);
	CDialog::OnOK();
}
