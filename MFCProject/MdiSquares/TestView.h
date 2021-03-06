#pragma once


// CTestView 视图

class CTestView : public  CRichEditView
{
	DECLARE_DYNCREATE(CTestView)

protected:
	CTestView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	virtual void OnInitialUpdate();
};


