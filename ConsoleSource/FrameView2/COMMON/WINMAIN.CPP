////////////////////////////////////////////////
// WINMAIN.CPP�ļ�

#include "_afxwin.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	ASSERT(hPrevInstance == NULL);

	int nReturnCode = -1;
	CWinThread* pThread = AfxGetThread();
	CWinApp* pApp = AfxGetApp();

	// ������ڲ��ĳ�ʼ��
	if(!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
		goto InitFailure;

	// Ӧ�ó����ȫ�ֳ�ʼ��
	if(pApp != NULL && !pApp->InitApplication())
		goto InitFailure;

	// ���̵߳ĳ�ʼ��
	if(!pThread->InitInstance())
	{
		nReturnCode = pThread->ExitInstance();
		goto InitFailure;
	}

	// ��ʼ���û�����
	nReturnCode = pThread->Run();

InitFailure:
	return nReturnCode;
}