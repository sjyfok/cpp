#include "UseFrame.h"

CMyApp theApp;




BOOL CMyApp::InitInstance()
{
	::MessageBox(NULL, "主线程开始执行!", "CMyApp::InitInstance", 0);
	return FALSE;
}

int CMyApp::ExitInstance()
{
	::MessageBox(NULL, "主线程将要退出!", "CMyApp::ExitInstance", MB_OK);
	return 0;
}