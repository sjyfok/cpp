#include "UseFrame.h"

CMyApp theApp;




BOOL CMyApp::InitInstance()
{
	::MessageBox(NULL, "���߳̿�ʼִ��!", "CMyApp::InitInstance", 0);
	return FALSE;
}

int CMyApp::ExitInstance()
{
	::MessageBox(NULL, "���߳̽�Ҫ�˳�!", "CMyApp::ExitInstance", MB_OK);
	return 0;
}