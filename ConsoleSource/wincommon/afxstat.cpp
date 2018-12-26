#include "_afxwin.h"
#include "_afxstat.h"

AFX_MODULE_THREAD_STATE * AfxGetModuleThreadState()
{
	return __afxModuleThreadState.GetData();
}

THREAD_LOCAL(AFX_MODULE_THREAD_STATE, __afxModuleThreadState)


