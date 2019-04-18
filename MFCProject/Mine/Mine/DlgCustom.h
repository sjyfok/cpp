#pragma once


// CDlgCustom 对话框

class CDlgCustom : public CDialog
{
	DECLARE_DYNAMIC(CDlgCustom)

public:
	void InitData(UINT xNum, UINT yNum, UINT mNum);
	CDlgCustom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgCustom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CUSTOM };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit2();
	UINT m_uHeight;
	UINT m_uWidth;
	UINT m_uNumber;
	afx_msg void OnBnClickedOk();
};
