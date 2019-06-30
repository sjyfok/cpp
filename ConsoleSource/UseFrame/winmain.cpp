#include "_afxwin.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	ASSERT(hPrevInstance = NULL);
	int nReturnCode = -1;
	CWinThread *pThread = AfxGetThread();
	CWinApp *pApp = AfxGetApp();
	if (!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
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