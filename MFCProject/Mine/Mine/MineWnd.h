
#include <afxwin.h>
class CMineWnd :
	public CWnd
{
public:
	CMineWnd();
	~CMineWnd();
	void SizeWindow();
protected:
	UINT m_uXNum;
	UINT m_uYNum;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuPrimary();
};
