#include "_afxwin.h"
#include <Windows.h>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	ASSERT(hPreInstance == NULL);
	int nReturnCode = -1;
	CWinThread *pThread = AfxGetThread();
	CWinApp *pApp = AfxGetApp();
	if (!AfxWinInit(hInstance, hPreInstance, lpCmdLine, nCmdShow))
	{
		goto InitFailure;
	}
	if (pApp != NULL && !pApp->InitApplication())
	{
		goto InitFailure;
	}
	if (!pThread->InitInstance())
	{
		nReturnCode = pThread->ExitInstance();
		goto InitFailure;
	}
	nReturnCode = pThread->Run();
InitFailure:
	return nReturnCode;
}
