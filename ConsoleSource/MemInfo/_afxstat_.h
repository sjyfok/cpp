#pragma once
#ifndef __AFXTLS_H__
#include "_afxtls_.h"
#endif

class CWinThread;

class CHandleMap;
class AFX_MODULE_THREAD_STATE : public CNoTrackObject
{
public:
	CWinThread *m_pCurrentWinThread;
	CHandleMap *m_pmapHWND;
	CHandleMap *m_pmapHDC;
};

EXTERN_THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState();

struct CRuntimeClass;
class CWinApp;
class AFX_MODULE_STATE : public CNoTrackObject
{
public:
	CTypedSimpleList<CRuntimeClass*> m_listClass;
	CWinApp *m_pCurrentWinApp;
	HINSTANCE m_hCurrentInstanceHandle;
	HINSTANCE m_hCurrentResourceHandle;
	THREAD_LOCAL(AFX_MODULE_THREAD_STATE, m_thread)
};

AFX_MODULE_STATE *AfxGetAppModuleState();
AFX_MODULE_STATE *AfxGetModuleState();

class CWnd;
class _AFX_THREAD_STATE :public CNoTrackObject
{
public:
	AFX_MODULE_STATE *m_pModuleState;
	TCHAR m_szTempClassName[96];
	CWnd *m_pWndInit;
	HHOOK m_hHookOldCbtFilter;
	MSG m_lastSendMsg;
};

EXTERN_THREAD_LOCAL(_AFX_THREAD_STATE, _afxThreadState);
_AFX_THREAD_STATE *AfxGetThreadState();