#pragma once
#ifndef __AFXTLS_H__
#include "_afxtls.h"
#endif

class CWinThread;
class AFX_MODULE_THREAD_STATE : public CNoTrackObject
{
public:
	CWinThread *m_pCurrentWinThread;
};

EXTERN_THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState();


