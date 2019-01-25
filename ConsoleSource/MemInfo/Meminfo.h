#include "../wincommon/_afxwin.h"

class CMyApp :public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

class CMainWindow :public CWnd
{
public:
	CMainWindow();
protected:
	char m_szText[1024];
	RECT m_rcInfo;
protected:
	virtual void PostNcDestroy();
	BOOL OnCreate(LPCREATESTRUCT);
	void OnPaint();
	void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};



