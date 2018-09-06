#ifndef TIC_TAC_MFC_H__
#define	TIC_TAC_MFC_H__

#include <afxwin.h>
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CWnd
{
public:
	CMainWindow();
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};



#endif
