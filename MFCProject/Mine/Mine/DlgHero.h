#pragma once


// CDlgHero 对话框

class CDlgHero : public CDialog
{
	DECLARE_DYNAMIC(CDlgHero)

public:
	void SetBHolder(CString holder);
	void SetBRecord(UINT record);
	void SetIHolder(CString holder);
	void SetIRecord(UINT record);
	void SetEHolder(CString holder);
	void SetERecord(UINT record);
	CDlgHero(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgHero();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HERO };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_szBHolder;
	CString m_szBRecord;
	CString m_szIRecord;
	CString m_szIHolder;
	CString m_szERecord;
	CString m_szEHolder;
};
