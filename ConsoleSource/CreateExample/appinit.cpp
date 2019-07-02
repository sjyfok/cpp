#include "_afxwin.h"

BOOL AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	ASSERT(hPrevInstance == NULL);
	AFX_MODULE_STATE *pModuleState = AfxGetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	pModuleState->m_hCurrentResourceHandle = hInstance;

	CWinApp *pApp = AfxGetApp();
	if (pApp != NULL)
	{
		pApp->m_hInstance = hInstance;
		pApp->m_hPrevInstance = hInstance;
		pApp->m_lpCmdLine = lpCmdLine;
		pApp->m_nCmdShow = nCmdShow;
	}
	return TRUE;
}