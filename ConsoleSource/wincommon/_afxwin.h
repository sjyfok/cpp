#ifndef __AFXWIN_H__
#define __AFXWIN_H__

#include <Windows.h>

#include "_afxstat.h"
#include "_afxtls.h"
#include "_afx.h"

class CCmdTarget;
typedef void (CCmdTarget::*AFX_PMSG)(void);

struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;
	UINT nCode;
	UINT nID;
	UINT nLastID;
	UINT nSig;
	AFX_PMSG pfn;
};

struct AFX_MSGMAP
{
	const AFX_MSGMAP * pBaseMap;
	const AFX_MSGMAP_ENTRY *pEntries;
};

#define DECLARE_MESSAGE_MAP() \
private:\
	static const AFX_MSGMAP_ENTRY _messageEntries[];\
protected:\
	static const AFX_MSGMAP messageMap;\
	virtual const AFX_MSGMAP * GetMessageMap() const; \

#define BEGIN_MESSAGE_MAP(theClass, baseClass)\
	const AFX_MSGMAP* theClass::GetMessageMap() const \
		{return &theClass::messageMap;}\
	const AFX_MSGMAP theClass::messageMap=\
	{&baseClass::messageMap, &theClass::_messageEntries[0]};\
	const AFX_MSGMAP_ENTRY theClass::_messageEntries[]=\
	{\

#define END_MESSAGE_MAP()\
	{0,0,0,0,0,(AFX_PMSG)0}\
	};\
	

extern CThreadSlotData* _afxThreadData;

LPCTSTR AfxRegisterWndClass(UINT nClassStyle,
	HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
BOOL AfxRegisterClass(WNDCLASS *lpWndClass);
BOOL AfxEndDeferRegisterClass(LONG fToRegister);

class CCmdTarget :public CObject
{
	DECLARE_DYNCREATE(CCmdTarget)
public:
	CCmdTarget();
	DECLARE_MESSAGE_MAP()
};

class CWnd :public CCmdTarget
{
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd();
	virtual ~CWnd();
	HWND m_hWnd;
	operator HWND() const { return m_hWnd; }
	HWND GetSafeHwnd() { return this == NULL ? NULL : m_hWnd; }
	static CWnd *FromHandle(HWND hWnd);
	static CWnd *FromHandlePermanent(HWND hWnd);
	BOOL Attach(HWND hWndNew);
	HWND Detach();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	friend LRESULT AfxCallWndProc(CWnd*, HWND, UINT, WPARAM, LPARAM);
protected:
	WNDPROC m_pfnSuper;
	virtual WNDPROC *GetSuperWndProcAddr();
	LRESULT Default();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	friend LRESULT __stdcall _AfxCbtFilterHook(int, WPARAM, LPARAM);
public:
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT &rect,
		CWnd * pParentWnd, UINT nID,
		LPVOID lpParam = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 void OnPaint();
	 void OnClose();
	 void OnDestroy();
	 void OnNcDestroy();
	 void OnTimer(UINT nIDEvent);
protected:	
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
};

const AFX_MSGMAP_ENTRY *AfxFindMessageEntry(const AFX_MSGMAP_ENTRY *lpEntry,
	UINT nMsg, UINT nCode, UINT nID);

typedef void (CWnd::*AFX_PMSGW)(void);

typedef UINT(__cdecl* AFX_THREADPROC)(LPVOID);
class CWinThread : public CObject
{
//#define DECLARE_DYNCREATE(class_name)\
//	DECLARE_DYNAMIC(class_name)\
//	static CObject* __stdcall CreateObject();

	DECLARE_DYNCREATE(CWinThread)


public:
	CWnd * m_pMainWnd;	// Ö÷´°¿Ú
	CWinThread();
	BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
		LPSECURITY_ATTRIBUTES lpSecurtyAttrs = NULL);
	BOOL m_bAutoDelete;
	HANDLE m_hThread;
	operator HANDLE() const 
	{ return this == NULL?NULL:m_hThread; }
	DWORD m_nThreadID;
	int GetThreadPriority()
	{
		return ::GetThreadPriority(m_hThread);
	}
	BOOL SetThreadPriority(int nPriority)
	{
		return ::SetThreadPriority(m_hThread, nPriority);
	}
	DWORD SuspendThread()
	{
		return ::SuspendThread(m_hThread);
	}
	DWORD ResumeThread()
	{
		return ::ResumeThread(m_hThread);
	}
public:
	virtual ~CWinThread();
	virtual void Delete();
	void CommonConstruct();
public:
	CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);
	LPVOID m_pThreadParams;
	AFX_THREADPROC m_pfnThraedProc;
public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PumpMessage();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL IsIdleMessage(MSG* pMsg);
	virtual int ExitInstance();
	MSG m_msgCur;
};

CWinThread *AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority = THREAD_PRIORITY_ABOVE_NORMAL, UINT nStackSize = 0,
	DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

CWinThread *AfxGetThread();
void AfxEndThread(UINT nExitCode, BOOL bDelete = TRUE);

class CWinApp : public CWinThread
{
	DECLARE_DYNCREATE(CWinApp)
public:
	CWinApp();
	virtual ~CWinApp();
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPTSTR m_lpCmdLine;
	int m_nCmdShow;
public:
	HCURSOR LoadCursor(UINT nIDResource) const;
	HICON LoadIcon(UINT nIDResource) const;
public:
	virtual BOOL InitApplication();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
};

__inline HCURSOR CWinApp::LoadCursor(UINT nIDResource) const
{
	return::LoadCursor(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource);
}

__inline HICON CWinApp::LoadIcon(UINT nIDResource) const
{
	return ::LoadIcon(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource);
}

CWinApp *AfxGetApp();
__inline CWinApp *AfxGetApp()
{
	return AfxGetModuleState()->m_pCurrentWinApp;
}

BOOL AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

#endif // !__AFXTLS_H__
