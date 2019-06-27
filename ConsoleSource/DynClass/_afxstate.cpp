#include "_afxstat.h"

AFX_MODULE_THREAD_STATE *AfxGetModuleThreadState()
{
	return _afxModuleThreadState.GetData();
}

//线程数据定义
THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
