///////////////////////////////////////////////////////
// THRDCORE.CPP�ļ�

#include "_afxwin.h"
#include "_afxtls_.h"
#include <process.h>


//--------------------------------------------------


struct _AFX_THREAD_STARTUP
{
	CWinThread* pThread;	// �������̵߳�CWinThread�����ָ��
	HANDLE hEvent;		// ���¼����̳߳�ʼ����Ϻ󽫱�����
	HANDLE hEvent2;		// ���¼��ڴ����̴߳�CreateThread��������ʱ��������
	
	BOOL bError;		// ָʾ�߳��Ƿ��ʼ���ɹ�
};

UINT __stdcall _AfxThreadEntry(void* pParam)
{
	_AFX_THREAD_STARTUP* pStartup = (_AFX_THREAD_STARTUP*)pParam;
	CWinThread* pThread = pStartup->pThread;
	try
	{	
		// �������̵߳�״̬
		AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
		pState->m_pCurrentWinThread = pThread;
	}
	catch(...)
	{
		// ���try�����쳣�׳����˴��Ĵ��뽫��ִ��
		pStartup->bError = TRUE;
		::SetEvent(pStartup->hEvent);
		AfxEndThread((UINT)-1, FALSE);
	}

	// ���������SetEvent������pStartup��ָ����ڴ�ռ���п��ܱ����߳����٣�
	// ����Ҫ����hEvent2��ֵ
	HANDLE hEvent2 = pStartup->hEvent2;

	// �������̴߳�CWinThread::CreateThread��������
	::SetEvent(pStartup->hEvent);

	// �ȴ����߳���CWinThread::CreateThread�����Ĵ���ִ�����
	::WaitForSingleObject(hEvent2, INFINITE);
	::CloseHandle(hEvent2);

	// �����û�ָ�����̺߳���
	DWORD nResult = 0;
	if(pThread->m_pfnThreadProc)
		nResult = (*pThread->m_pfnThreadProc)(pThread->m_pThreadParams);

	// �����߳�
	AfxEndThread(nResult);
	return 0;
}


CWinThread* AfxGetThread()
{
	// ���ص�ǰ�߳�CWinThread�����ָ��
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	return pState->m_pCurrentWinThread;
}

void AfxEndThread(UINT nExitCode, BOOL bDelete)
{
	// �ͷŵ�ǰCWinThread����ռ�õ��ڴ�
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	CWinThread* pThread = pState->m_pCurrentWinThread;
	if (pThread != NULL)
	{
		if (bDelete)
			pThread->Delete();
		pState->m_pCurrentWinThread = NULL;
	}

	// �ͷ��ֲ߳̾��洢ռ�õ��ڴ�
	if (_afxThreadData != NULL)
		_afxThreadData->DeleteValues(NULL, FALSE);

	// �������̵߳�����
	_endthreadex(nExitCode);
}

CWinThread* AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority, UINT nStackSize, DWORD dwCreateFlags,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	// Ϊ���̴߳���һ��CWinThead��Ķ���
	CWinThread* pThread = new CWinThread(pfnThreadProc, pParam);

	// �����̣߳�������
	if (!pThread->CreateThread(dwCreateFlags|CREATE_SUSPENDED, nStackSize,
		lpSecurityAttrs))
	{
		pThread->Delete();
		return NULL;
	}

	// �������̵߳����ȼ�
	pThread->SetThreadPriority(nPriority);

	// ���û��ָ��CREATE_SUSPENDED��ǣ������߳�
	if (!(dwCreateFlags & CREATE_SUSPENDED))
		pThread->ResumeThread();

	return pThread;
}

//----------------- CWinThread��--------------------//

void CWinThread::CommonConstruct ()
{
	m_hThread = NULL;
	m_nThreadID = 0;
	m_bAutoDelete = TRUE;
	m_pMainWnd = NULL;	
}

CWinThread::CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam)
{
	m_pfnThreadProc = pfnThreadProc;
	m_pThreadParams = pParam;

	CommonConstruct();
}

CWinThread::CWinThread()
{
	m_pThreadParams = NULL;
	m_pfnThreadProc = NULL;

	CommonConstruct();
}

CWinThread::~CWinThread()
{
	// �ͷ��߳��ں˶�����
	if (m_hThread != NULL)
		CloseHandle(m_hThread);

	// ����̵߳�״̬
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	if (pState->m_pCurrentWinThread == this)
		pState->m_pCurrentWinThread = NULL;
}

BOOL CWinThread::CreateThread(DWORD dwCreateFlags, UINT nStackSize,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	// Ϊ�̵߳ĳ�ʼ���������startup
	_AFX_THREAD_STARTUP startup; memset(&startup, 0, sizeof(startup));
	startup.pThread = this;
	startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	// ����һ����ʼ״̬Ϊ���ɵ��ȵ��̣߳�����
	m_hThread = (HANDLE)_beginthreadex(lpSecurityAttrs, nStackSize,
		&_AfxThreadEntry, &startup, dwCreateFlags | CREATE_SUSPENDED, (UINT*)&m_nThreadID);
	if (m_hThread == NULL)
		return FALSE;

	// �ָ��̵߳�ִ�У����ȴ��̳߳�ʼ�����
	ResumeThread();
	::WaitForSingleObject(startup.hEvent, INFINITE);
	::CloseHandle(startup.hEvent);

	// ����û���������һ��������̣߳����Ǿ���ͣ�̵߳�����
	if (dwCreateFlags & CREATE_SUSPENDED)
		::SuspendThread(m_hThread);

	// ����߳��ڳ�ʼ��ʱ�������ͷ�������Դ
	if (startup.bError)
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		::CloseHandle(startup.hEvent2);
		return FALSE;
	}

	// ֪ͨ�̼߳�������
	::SetEvent(startup.hEvent2);

	return TRUE;
}

void CWinThread::Delete()
{
	// ���ָ�����Զ�����Ļ���ɾ��thisָ��
	if (m_bAutoDelete)
		delete this;
}

/////////////////////////////////
//�麯��

int CWinThread::Run()
{
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	for(;;)
	{
		while(bIdle && !::PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!OnIdle(lIdleCount++))
				bIdle = FALSE;
		}

		do
		{
			if(!PumpMessage())
				return ExitInstance();
			
			if(IsIdleMessage(&m_msgCur))
			{
				bIdle = TRUE;
				lIdleCount = 0;
			}
		}while(::PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE));
	}
	ASSERT(FALSE);
}

// ����Ϣ�͸�Windows��TranslateMessage��DispatchMessage֮ǰ������Ϣ����
BOOL CWinThread::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
}

BOOL CWinThread::PumpMessage()
{
	if (!::GetMessage(&m_msgCur, NULL, NULL, NULL))
		return FALSE;

	if(!PreTranslateMessage(&m_msgCur)) // û����ɷ���
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

BOOL CWinThread::IsIdleMessage(MSG* pMsg)
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

IMPLEMENT_DYNCREATE(CWinThread, CCmdTarget)







/*


//--------------------------------------------------


struct _AFX_THREAD_STARTUP
{
	CWinThread* pThread;	// �������̵߳�CWinThread�����ָ��
	HANDLE hEvent;		// ���¼����̳߳�ʼ����Ϻ󽫱�����
	HANDLE hEvent2;		// ���¼��ڴ����̴߳�CreateThread��������ʱ��������
	
	BOOL bError;		// ָʾ�߳��Ƿ��ʼ���ɹ�
};

UINT __stdcall _AfxThreadEntry(void* pParam)
{
	_AFX_THREAD_STARTUP* pStartup = (_AFX_THREAD_STARTUP*)pParam;
	CWinThread* pThread = pStartup->pThread;
	try
	{	
		// �������̵߳�״̬
		AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
		pState->m_pCurrentWinThread = pThread;
	}
	catch(...)
	{
		// ���try�����쳣�׳����˴��Ĵ��뽫��ִ��
		pStartup->bError = TRUE;
		::SetEvent(pStartup->hEvent);
		AfxEndThread((UINT)-1, FALSE);
	}

	// ���������SetEvent������pStartup��ָ����ڴ�ռ���п��ܱ����߳����٣�
	// ����Ҫ����hEvent2��ֵ
	HANDLE hEvent2 = pStartup->hEvent2;

	// �������̴߳�CWinThread::CreateThread��������
	::SetEvent(pStartup->hEvent);

	// �ȴ����߳���CWinThread::CreateThread�����Ĵ���ִ�����
	::WaitForSingleObject(hEvent2, INFINITE);
	::CloseHandle(hEvent2);

	// �����û�ָ�����̺߳���
	DWORD nResult = 0;
	if(pThread->m_pfnThreadProc)
		nResult = (*pThread->m_pfnThreadProc)(pThread->m_pThreadParams);

	// �����߳�
	AfxEndThread(nResult);
	return 0;
}


CWinThread* AfxGetThread()
{
	// ���ص�ǰ�߳�CWinThread�����ָ��
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	return pState->m_pCurrentWinThread;
}

void AfxEndThread(UINT nExitCode, BOOL bDelete)
{
	// �ͷŵ�ǰCWinThread����ռ�õ��ڴ�
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	CWinThread* pThread = pState->m_pCurrentWinThread;
	if (pThread != NULL)
	{
		if (bDelete)
			pThread->Delete();
		pState->m_pCurrentWinThread = NULL;
	}

	// �ͷ��ֲ߳̾��洢ռ�õ��ڴ�
	if (_afxThreadData != NULL)
		_afxThreadData->DeleteValues(NULL, FALSE);

	// �������̵߳�����
	_endthreadex(nExitCode);
}

CWinThread* AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority, UINT nStackSize, DWORD dwCreateFlags,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	// Ϊ���̴߳���һ��CWinThead��Ķ���
	CWinThread* pThread = new CWinThread(pfnThreadProc, pParam);

	// �����̣߳�������
	if (!pThread->CreateThread(dwCreateFlags|CREATE_SUSPENDED, nStackSize,
		lpSecurityAttrs))
	{
		pThread->Delete();
		return NULL;
	}

	// �������̵߳����ȼ�
	pThread->SetThreadPriority(nPriority);

	// ���û��ָ��CREATE_SUSPENDED��ǣ������߳�
	if (!(dwCreateFlags & CREATE_SUSPENDED))
		pThread->ResumeThread();

	return pThread;
}

//----------------- CWinThread��--------------------//

void CWinThread::CommonConstruct ()
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
	m_pThreadParams = NULL;
	m_pfnThreadProc = NULL;

	CommonConstruct();
}

CWinThread::~CWinThread()
{
	// �ͷ��߳��ں˶�����
	if (m_hThread != NULL)
		CloseHandle(m_hThread);

	// ����̵߳�״̬
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	if (pState->m_pCurrentWinThread == this)
		pState->m_pCurrentWinThread = NULL;
}

BOOL CWinThread::CreateThread(DWORD dwCreateFlags, UINT nStackSize,
	LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	// Ϊ�̵߳ĳ�ʼ���������startup
	_AFX_THREAD_STARTUP startup; memset(&startup, 0, sizeof(startup));
	startup.pThread = this;
	startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	// ����һ����ʼ״̬Ϊ���ɵ��ȵ��̣߳�����
	m_hThread = (HANDLE)_beginthreadex(lpSecurityAttrs, nStackSize,
		&_AfxThreadEntry, &startup, dwCreateFlags | CREATE_SUSPENDED, (UINT*)&m_nThreadID);
	if (m_hThread == NULL)
		return FALSE;

	// �ָ��̵߳�ִ�У����ȴ��̳߳�ʼ�����
	ResumeThread();
	::WaitForSingleObject(startup.hEvent, INFINITE);
	::CloseHandle(startup.hEvent);

	// ����û���������һ��������̣߳����Ǿ���ͣ�̵߳�����
	if (dwCreateFlags & CREATE_SUSPENDED)
		::SuspendThread(m_hThread);

	// ����߳��ڳ�ʼ��ʱ�������ͷ�������Դ
	if (startup.bError)
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		::CloseHandle(startup.hEvent2);
		return FALSE;
	}

	// ֪ͨ�̼߳�������
	::SetEvent(startup.hEvent2);

	return TRUE;
}

void CWinThread::Delete()
{
	// ���ָ�����Զ�����Ļ���ɾ��thisָ��
	if (m_bAutoDelete)
		delete this;
}





  */