#include "afxstat.h"

AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState()
{
	return _afxModuleThreadState.GetData();
}

THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
