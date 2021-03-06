#pragma once
#include <Windows.h>
#include "_afx.h"
#include "_afxtls_.h"
#include "_afxstat_.h"

extern CThreadSlotData* _afxThreadData;

typedef UINT(__cdecl *AFX_THREADPROC) (LPVOID);
class CWinThread :public CObject
{
	DECLARE_DYNCREATE(CWinThread)
public:
	//����
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
