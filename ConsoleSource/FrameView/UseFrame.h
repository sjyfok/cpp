#include "../wincommon/_afxwin.h"

class CMyApp :public CWinApp
{
public: 
	virtual BOOL InitInstance();
};

class CMyWnd :public CWnd
{
public:
	CMyWnd();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};