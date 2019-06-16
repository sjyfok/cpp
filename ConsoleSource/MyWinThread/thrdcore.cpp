#include "afxwin.h"
#include "afxstat.h"
#include <process.h>

struct AFX_THREAD_STARTUP
{
	CWinThread *pThread;
	HANDLE hEvent;
	HANDLE hEvent2;
	BOOL bError;
};

UINT __stdcall _AfxThreadEntry(void *pParam)
{
	AFX_THREAD_STARTUP *pStartup = (AFX_THREAD_STARTUP*)pParam;
	CWinThread *pThread = pStartup->pThread;
	try
	{
		//线程类和线程状态类结合到一起
		AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
		pState->m_pCurrentWinThread = pThread;
	}
	catch (...)
	{
		//在线程执行时发送了失败  设置通知父线程的标志 并通知父线程
		pStartup->bError = TRUE;
		::SetEvent(pStartup->hEvent);
		AfxEndThread((UINT)-1, FALSE);
	}
	//正常执行时 通知父线程 
	HANDLE hEvent2 = pStartup->hEvent2;
	::SetEvent(pStartup->hEvent);
	//等待父线程给信号后再执行
	::WaitForSingleObject(hEvent2, INFINITE);
	::CloseHandle(hEvent2);
	//执行用户程序制定的代码
	DWORD nResult = (*pThread->m_pfnThreadProc)(pThread->m_pThreadParams);
	AfxEndThread(nResult);
	return 0;
}



CWinThread* AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority, UINT nStackSize, DWORD dwCreateFlags,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	//引入线程类
	CWinThread *pThread = new CWinThread(pfnThreadProc, pParam);
	if (!pThread->CreateThread(dwCreateFlags|CREATE_SUSPENDED,nStackSize,lpSecurityAttrs))
	{
		pThread->Delete();
		return NULL;
	}
	pThread->SetThreadPriority(nPriority);
	if (!(dwCreateFlags&CREATE_SUSPENDED))
		pThread->ResumeThread();
	return pThread;
}

CWinThread *AfxGetThread()
{
	AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
	return pState->m_pCurrentWinThread;
}

void AfxEndThread(UINT nExitCode, BOOL bDelete)
{
	AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
	CWinThread *pThread = pState->m_pCurrentWinThread;
	if (pThread != NULL)
	{
		if (bDelete)
			pThread->Delete();
		pState->m_pCurrentWinThread = NULL;
	}
	if (_afxThreadData != NULL)
	{
		_afxThreadData->DeleteValues(NULL);
	}
	_endthreadex(nExitCode);
}



void CWinThread::CommonConstruct()
{
	m_hThread = NULL;
	m_nThreadID = 0;
	m_bAutoDelete = TRUE;
}

CWinThread::CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam)
{
	m_pfnThreadProc = pfnThreadProc;
	m_pThreadParams = pParam;
	CommonConstruct();
}

CWinThread::CWinThread()
{
	m_pfnThreadProc = NULL;
	m_pThreadParams = NULL;
	CommonConstruct();
}

CWinThread::~CWinThread()
{
	if (m_hThread != NULL)
		CloseHandle(m_hThread);
	AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
	if (pState->m_pCurrentWinThread == this)
		pState->m_pCurrentWinThread = NULL;
}

void CWinThread::Delete()
{
	if (m_bAutoDelete)
		delete this;
}

BOOL CWinThread::CreateThread(DWORD dwCreateFlags,
	UINT nStackSize, LPSECURITY_ATTRIBUTES lpSecurity_Attrs)
{
	AFX_THREAD_STARTUP startup;
	memset(&startup, 0, sizeof(startup));
	startup.pThread = this;
	//创建初始状态是不置位的事件
	startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	//真正创建线程的时候 创建时要挂起
	m_hThread = (HANDLE)_beginthreadex(lpSecurity_Attrs, nStackSize,
		&_AfxThreadEntry, &startup, dwCreateFlags | CREATE_SUSPENDED, (UINT*)&m_nThreadID);
	if (m_hThread == NULL)
	{
		return FALSE;
	}
	ResumeThread();//恢复子线程执行
	::WaitForSingleObject(startup.hEvent, INFINITE);
	::CloseHandle(startup.hEvent);
	if (dwCreateFlags & CREATE_SUSPENDED)
	{
		::SuspendThread(m_hThread);
	}
	if (startup.bError)
	{
		//有错误发送
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		::CloseHandle(startup.hEvent2);
		return FALSE;
	}
	//无故障时 通知子线程执行
	::SetEvent(startup.hEvent2);
	return TRUE;
}