#pragma once
#include <Windows.h>
#include "afxtls.h"

extern CThreadSlotData* _afxThreadData;

typedef UINT(__cdecl *AFX_THREADPROC) (LPVOID);
class CWinThread
{
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
};



CWinThread *AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID nParam,
	int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
	DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
CWinThread *AfxGetThread();
void AfxEndThread(UINT nExitCode, BOOL bDelete = TRUE);