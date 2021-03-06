
// ChildView.h: CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();
	//变量
protected:
	int m_nShape;
	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShapesCircle();
	afx_msg void OnShapesSquare();
	afx_msg void OnShapesTriangle();
	afx_msg void OnUpdateShapesCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapesSquare(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapesTriangle(CCmdUI *pCmdUI);
};

