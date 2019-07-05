#include "afxwin.h"

#define IDC_BUTTON		(10)
#define IDC_RADIO		(11)
#define IDC_CHECKBOX	(12)
#define IDC_STATIC		(13)
#define IDC_EDITTEXT	(14)

class CMyApp : public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

class CMainWindow :public CWnd
{
public:
	CMainWindow();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};
