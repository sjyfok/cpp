#include "_afx.h"
#include "_afxstat.h"



AFX_MODULE_THREAD_STATE * AfxGetModuleThreadState()
{
	return AfxGetModuleState()->m_thread.GetData();
//	return __afxModuleThreadState.GetData();
}

THREAD_LOCAL(AFX_MODULE_THREAD_STATE, __afxModuleThreadState)
THREAD_LOCAL(_AFX_THREAD_STATE, _afxThreadState);

_AFX_THREAD_STATE* AfxGetThreadState()
{
	return _afxThreadState.GetData();
}


AFX_MODULE_STATE _afxBaseModuleState;
AFX_MODULE_STATE *AfxGetAppModuleState()
{
	return &_afxBaseModuleState;
}

AFX_MODULE_STATE *AfxGetModuleState()
{
	_AFX_THREAD_STATE *pState = _afxThreadState.GetData();
	AFX_MODULE_STATE *pResult;
	if (pState->m_pModuleState != NULL)
		pResult = pState->m_pModuleState;
	else
		pResult = AfxGetAppModuleState();
	ASSERT(pResult != NULL);
	return pResult;
}

