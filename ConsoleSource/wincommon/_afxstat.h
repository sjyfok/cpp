#ifndef __AFXSTAT_H__
#define __AFXSTAT_H__

#ifndef __AFXTLS_H__
#include "_afxtls.h"
#endif // !__AFXTLS_H__

class AFX_MODULE_THREAD_STATE : public CNoTrackObject
{
public:
	CWinThread * m_pCurrentWinThread;
};

EXTERN_THREAD_LOCAL(AFX_MODULE_THREAD_STATE, __afxModuleThreadState)
AFX_MODULE_THREAD_STATE * AfxGetModuleThreadState();



#endif // !__AFXSTAT_H__
