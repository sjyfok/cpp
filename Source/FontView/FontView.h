#ifndef FONTVIEW_MFC_H__
#define	FONTVIEW_MFC_H__

#include <afxwin.h>
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
private:

};

class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};



#endif
