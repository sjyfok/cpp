#pragma once
#include <Windows.h>
#include "_afx.h"
#include "_afxtls_.h"
#include "_afxstat_.h"

class CCmdTarget :public CObject
{
	DECLARE_DYNCREATE(CCmdTarget)
public:
	CCmdTarget();
};

class CWnd : public CCmdTarget
{
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd();
	virtual ~CWnd();
	HWND m_hWnd;
	operator HWND() const { return m_hWnd;}
	HWND GetSafeHwnd() { return this == NULL ? NULL : m_hWnd; }

	static CWnd* FromHandle(HWND hWnd);
	static CWnd* FromHandlePermanent(HWND hWnd);
	BOOL Attach(HWND hWndNew);
	HWND Detach();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	friend LRESULT AfxCallWndProc(CWnd*, HWND, UINT, WPARAM, LPARAM);
protected:
	WNDPROC m_pfnSuper;
	virtual WNDPROC* GetSuperWndProcAddr();
	LRESULT Default();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID);
	friend LRESULT __stdcall _AfxCbtFilterHook(int, WPARAM, LPARAM);
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT &rect, CWnd *pParentWnd, UINT nID,
		LPVOID lpParam = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDOrHMenu,
		LPVOID lpParam = NULL);
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
};

LRESULT __stdcall AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
LRESULT AfxCallWndProc(CWnd *pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

extern CThreadSlotData* _afxThreadData;

typedef UINT(__cdecl *AFX_THREADPROC) (LPVOID);
class CWinThread :public CObject
{
	DECLARE_DYNCREATE(CWinThread)
public:
	//Ьиад
	BOOL m_bAutoDelete;
	HANDLE m_hThread;
	DWORD m_nThreadID;
	LPVOID m_pThreadParams;
	AFX_THREADPROC m_pfnThreadProc;

public:
	CWinThread();	
	BOOL CreateThread(DWORD dwCreateFLags = 0, UINT nStackSize = 0,
		LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
	operator HANDLE() const {
		return this == NULL ? NULL: m_hThread; }
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
public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PumpMessage();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL IsIdleMessage(MSG *pMsg);
	virtual int ExitInstance();
	MSG m_msgCur;
};



CWinThread *AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID nParam,
	int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
	DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
CWinThread *AfxGetThread();
void AfxEndThread(UINT nExitCode, BOOL bDelete = TRUE);

class CWinApp :public CWinThread
{
	DECLARE_DYNCREATE(CWinApp)
public:
	CWinApp();
	virtual ~CWinApp();

	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPTSTR m_lpCmdLine;
	int m_nCmdShow;
	CWnd* m_pMainWnd;
public:
	HCURSOR LoadCursor(UINT nIDResource) const;
	HICON LoadIcon(UINT nIDResource) const;
public:
	virtual BOOL InitApplication();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
};


inline HCURSOR CWinApp::LoadCursor(UINT nIDResource) const
{
	return ::LoadCursor(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource);
}

inline HICON CWinApp::LoadIcon(UINT nIDResource) const
{
	return ::LoadIcon(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource);
}
CWinApp* AfxGetApp();
inline CWinApp* AfxGetApp()
{
	return AfxGetModuleState()->m_pCurrentWinApp;
}

BOOL AfxWinInit(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow);

LPCTSTR AfxRegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
BOOL AfxEndDeferRegisterClass(LONG fToRegister);
BOOL AfxRegisterClass(WNDCLASS *lpWndClass);
LRESULT __stdcall _AfxCbtFilterHook(int code, WPARAM wParam, LPARAM lParam);
void AfxHookWindowCreate(CWnd *pWnd);
BOOL AfxUnhookWindowCreate();
