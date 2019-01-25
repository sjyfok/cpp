///////////////////////////////////////////////////////
// AFXSTATE.CPP�ļ�



#include "_afx.h"
#include "_afxstat_.h"


//---------------�߳�״̬----------------------//

_AFX_THREAD_STATE* AfxGetThreadState()
{
	return _afxThreadState.GetData();
}
THREAD_LOCAL(_AFX_THREAD_STATE, _afxThreadState);

//---------------ģ��״̬----------------------//

AFX_MODULE_STATE _afxBaseModuleState;
AFX_MODULE_STATE* AfxGetAppModuleState()
{
	return &_afxBaseModuleState;
}

AFX_MODULE_STATE* AfxGetModuleState()
{
	_AFX_THREAD_STATE* pState = _afxThreadState.GetData();
	AFX_MODULE_STATE* pResult;
	if(pState->m_pModuleState != NULL)
		pResult = pState->m_pModuleState;
	else
		pResult = AfxGetAppModuleState();

	ASSERT(pResult != NULL);
	return pResult;
}

//---------------ģ���߳�״̬----------------------//

AFX_MODULE_THREAD_STATE* AfxGetModuleThreadState()
{
	return AfxGetModuleState()->m_thread.GetData();
}





/*

AFX_MODULE_THREAD_STATE* AfxGetModuleThreadState()
{
	return _afxModuleThreadState.GetData();
}
THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)

*/