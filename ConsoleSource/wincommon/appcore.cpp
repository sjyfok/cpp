#include "_afxstat.h"
#include "_afx.h"
#include "_afxwin.h"
#include <Windows.h>



CWinApp::CWinApp()
{
	AFX_MODULE_STATE * pModuleState = AfxGetModuleState();
	AFX_MODULE_THREAD_STATE *pThreadState = pModuleState->m_thread;
	ASSERT(AfxGetThread() == NULL);
	pThreadState->m_pCurrentWinThread = this;
	ASSERT(AfxGetThread() == this);
	m_hThread = ::GetCurrentThread();
	m_nThreadID = ::GetCurrentThreadId();
	ASSERT(pModuleState->m_pCurrentWinApp == NULL);
	pModuleState->m_pCurrentWinApp = this;
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

//#define IMPLEMENT_DYNCREATE(class_name, base_class_name)\
//	CObject *__stdcall class_name::CreateObject()\
//		{return new class_name;}\
//	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF,\
//			class_name::CreateObject)
//
//#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew)\
//	const CRuntimeClass class_name::class##class_name = {\
//		#class_name, sizeof(class class_name), wSchema, pfnNew,\
//			RUNTIME_CLASS(base_class_name), NULL};\
//	CRuntimeClass* class_name::GetRuntimeClass() const\
//		{return RUNTIME_CLASS(class_name);}

//CObject *__stdcall CWinApp::CreateObject()
//{
//	return new CWinApp;
//}
//
////#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)&class_name::class##class_name)
//const CRuntimeClass CWinApp::classCWinApp = {
//	"CWinApp", sizeof(class CWinApp), 0xFFFF, CWinApp::CreateObject, ((CRuntimeClass*)&CWinThread::classCWinThread), NULL };
//
//CRuntimeClass * CWinApp::GetRuntimeClass() const
//{
//	return RUNTIME_CLASS(CWinApp);
//}


