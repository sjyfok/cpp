#include "_afxstat.h"

AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState()
{
	return _afxModuleThreadState.GetData();
}

//�߳����ݶ���
THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
