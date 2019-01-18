#include "_afxwin.h"
#include "_afxtls.h"
#include "_afxstat.h"
#include <process.h>
#include "_afx.h"

IMPLEMENT_DYNCREATE(CWinThread, CObject)

struct _AFX_THREAD_STARTUP
{
	CWinThread *pThread;
	HANDLE hEvent;
	HANDLE hEvent2;
	BOOL bError;
};

UINT __stdcall _AfxThreadEntry(void *pParam)
{
	_AFX_THREAD_STARTUP *pStartup = (_AFX_THREAD_STARTUP *)pParam;
	CWinThread *pThread = pStartup->pThread;
	try
	{
		AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
		pState->m_pCurrentWinThread = pThread;
	}
	catch (...)
	{
		pStartup->bError = TRUE;
		::SetEvent(pStartup->hEvent);
		AfxEndThread((UINT)-1, FALSE);
	}
	HANDLE hEvent2 = pStartup->hEvent2;
	::SetEvent(pStartup->hEvent);
	::WaitForSingleObject(hEvent2, INFINITE);
	::CloseHandle(hEvent2);
	DWORD nResult = (*pThread->m_pfnThraedProc)(pThread->m_pThreadParams);
	AfxEndThread(nResult);
	return 0;
}

CWinThread * AfxGetThread()
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

BOOL CWinThread::CreateThread(DWORD dwCreateFlags, UINT nStackSize, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	_AFX_THREAD_STARTUP startup;
	memset(&startup, 0, sizeof(startup));
	startup.pThread = this;
	startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	m_hThread = (HANDLE)_beginthreadex(lpSecurityAttrs, nStackSize,
		&_AfxThreadEntry, &startup, dwCreateFlags | CREATE_SUSPENDED, (UINT*)&m_nThreadID);
	if (m_hThread == NULL)
		return FALSE;
	ResumeThread();
	::WaitForSingleObject(startup.hEvent, INFINITE);
	::CloseHandle(startup.hEvent);
	if (dwCreateFlags & CREATE_SUSPENDED)
		::SuspendThread(m_hThread);
	if (startup.bError)
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		::CloseHandle(startup.hEvent2);
		return FALSE;
	}
	::SetEvent(startup.hEvent2);
	return TRUE;
}

CWinThread *AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority, UINT nStackSize, DWORD dwCreateFlags,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	CWinThread *pThread = new CWinThread(pfnThreadProc, pParam);

	if (!pThread->CreateThread(dwCreateFlags | CREATE_SUSPENDED, nStackSize,
		lpSecurityAttrs))
	{
		pThread->Delete();
		return NULL;
	}
	pThread->SetThreadPriority(nPriority);
	if (!(dwCreateFlags&CREATE_SUSPENDED))
		pThread->ResumeThread();
	return pThread;
}

void CWinThread::CommonConstruct()
{
	m_hThread = NULL;
	m_nThreadID = 0;
	m_bAutoDelete = TRUE;
}

CWinThread::CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam)
{
	m_pfnThraedProc = pfnThreadProc;
	m_pThreadParams = pParam;
	CommonConstruct();
}

CWinThread::CWinThread()
{
	m_pThreadParams = NULL;
	m_pfnThraedProc = NULL;
	CommonConstruct();
}

CWinThread::~CWinThread()
{
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
	}
	AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
	if (pState->m_pCurrentWinThread == this)
		pState->m_pCurrentWinThread = NULL;
}

void CWinThread::Delete()
{
	if (m_bAutoDelete)
		delete this;
}

int CWinThread::Run()
{
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	for (;;)
	{
		while (bIdle && !::PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!OnIdle(lIdleCount++))
			{
				bIdle = FALSE;
			}
		}
		do
		{
			if (!PumpMessage())
			{
				return ExitInstance();
			}
			if (IsIdleMessage(&m_msgCur))
			{
				bIdle = TRUE;
				lIdleCount = 0;
			}
		} while (::PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE));
	}
	ASSERT(FALSE);
}

BOOL CWinThread::PreTranslateMessage(MSG *pMsg)
{
	return FALSE;
}

BOOL CWinThread::PumpMessage()
{
	if (!::GetMessage(&m_msgCur, NULL, NULL, NULL))
	{
		return FALSE;
	}
	if (!PreTranslateMessage(&m_msgCur))
	{
		::TranslateMessage(&m_msgCur);
		::DispatchMessage(&m_msgCur);
	}
	return TRUE;
}

BOOL CWinThread::OnIdle(LONG lCount)
{
	return lCount < 0;
}

BOOL CWinThread::IsIdleMessage(MSG *pMsg)
{
	return TRUE;
}

BOOL CWinThread::InitInstance()
{
	return FALSE;
}

int CWinThread::ExitInstance()
{
	int nResult = m_msgCur.lParam;
	return nResult;
}

