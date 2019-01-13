#include "_afxtls.h"
#include "_afxwin.h"
#include <Windows.h>
#include "_afx.h"
#include "_afxstat.h"

BOOL AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
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
		pApp->m_lpCmdline = lpCmdLine;
		pApp->m_nCmdShow = nCmdShow;
	}
	return TRUE;
}
