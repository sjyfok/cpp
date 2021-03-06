
// HtmlClockView.h: CHtmlClockView 类的接口
//

#pragma once


class CHtmlClockView : public CHtmlView
{
protected: // 仅从序列化创建
	CHtmlClockView();
	DECLARE_DYNCREATE(CHtmlClockView)

// 特性
public:
	CHtmlClockDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CHtmlClockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // HtmlClockView.cpp 中的调试版本
inline CHtmlClockDoc* CHtmlClockView::GetDocument() const
   { return reinterpret_cast<CHtmlClockDoc*>(m_pDocument); }
#endif

