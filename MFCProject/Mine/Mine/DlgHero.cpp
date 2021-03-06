// DlgHero.cpp: 实现文件
//

#include "stdafx.h"
#include "Mine.h"
#include "DlgHero.h"
#include "afxdialogex.h"
#include "MineDefs.h"


// CDlgHero 对话框

IMPLEMENT_DYNAMIC(CDlgHero, CDialog)

CDlgHero::CDlgHero(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_HERO, pParent)
	, m_szBHolder(_T(""))
	, m_szBRecord(_T(""))
	, m_szIRecord(_T(""))
	, m_szIHolder(_T(""))
	, m_szERecord(_T(""))
	, m_szEHolder(_T(""))
{

}

CDlgHero::~CDlgHero()
{
}

void CDlgHero::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_B_R, m_szBHolder);
	DDX_Text(pDX, IDC_B_H, m_szBHolder);
	DDX_Text(pDX, IDC_B_R, m_szBRecord);
	DDX_Text(pDX, IDC_I_R, m_szIRecord);
	DDX_Text(pDX, IDC_I_H, m_szIHolder);
	DDX_Text(pDX, IDC_E_R, m_szERecord);
	DDX_Text(pDX, IDC_E_H, m_szEHolder);
}


BEGIN_MESSAGE_MAP(CDlgHero, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgHero::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgHero 消息处理程序

void CDlgHero::SetBHolder(CString holder)
{
	m_szBHolder = holder;
}

void CDlgHero::SetBRecord(UINT record)
{
	m_szBRecord.Format(_T("%d秒"), record);
}

void CDlgHero::SetIHolder(CString holder)
{
	m_szIHolder = holder;
}

void CDlgHero::SetIRecord(UINT record)
{
	m_szIRecord.Format(_T("%d秒"), record);
}

void CDlgHero::SetEHolder(CString holder)
{
	m_szEHolder = holder;
}

void CDlgHero::SetERecord(UINT record)
{
	m_szERecord.Format(_T("%d秒"), record);
}



void CDlgHero::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMineWnd *pMine = (CMineWnd*)AfxGetMainWnd();
	pMine->ResetRecord();
	m_szBHolder = DEFAULT_HOLDER;
	m_szBRecord.Format(_T("%d秒"), DEFAULT_RECORD);
	m_szIHolder = DEFAULT_HOLDER;
	m_szIRecord.Format(_T("%d秒"), DEFAULT_RECORD);
	m_szEHolder = DEFAULT_HOLDER;
	m_szERecord.Format(_T("%d秒"), DEFAULT_RECORD);
	UpdateData(FALSE);
	CDialog::OnOK();
}
