#include "_afxstat_.h"

AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState()
{
	return AfxGetModuleThreadState.GetData();
}

THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)