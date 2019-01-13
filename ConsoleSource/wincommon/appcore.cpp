#include "_afxwin.h"
#include "_afxstat.h"
#include "_afx.h"
#include <Windows.h>

CWinApp::CWinApp()
{
	AFX_MODULE_STATE * pMoudleState = AfxGetModuleState();
	AFX_MODULE_THREAD_STATE *pThreadState = pModuleState.m_thread;
	ASSERT(AfxGetThrad() == NULL);
	m_hThread = ::GetCurrentThread();
	m_nThreadID = ::GetCurrentThreadId();
	ASSERT(pModuleState->m_pCurrentWinApp == NULL);
	pMoudleState->m_pCurrentWinApp = this;
	ASSERT(AfxGetApp() == this);
	m_hInstance = NULL;
}

CWinApp::~CWinApp()
{
	AFX_MODULE_STATE *pModuleState = AfxGetModuleState();
	if (pModuleState->m_pCurrentWinApp == this)
	{
		pModuleState->m_pCurrentWinApp = NULL;
	}
}

BOOL CWinApp::InitApplication()
{
	return TRUE;
}

BOOL CWinApp::InitInstance()
{
	return TRUE;
}

int CWinApp::Run()
{
	return CWinThread::Run();
}

int CWinApp::ExitInstance()
{
	return m_msgCur.wParam;
}

IMPLEMENT_DYNCREATE(CWinApp, CWinThread)