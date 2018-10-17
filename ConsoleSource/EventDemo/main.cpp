#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;

HANDLE g_hEvent;

UINT __stdcall	ChildFunc(LPVOID);

int main(int argc, char *argv[])
{
	UINT uId;
	HANDLE hChildThread;
	char a;
	g_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	hChildThread = (HANDLE)::_beginthreadex(NULL, 0, ChildFunc, NULL, 0, &uId);
	
	cout << "Please input a char to tell the child thread to work:\n";
	cin >> a;
	::SetEvent(g_hEvent);
	
	::WaitForSingleObject(hChildThread, INFINITE);
	cout << "All the work has been finished!\n";
	::CloseHandle(hChildThread);
	::CloseHandle(g_hEvent);

	return 0;
}

UINT __stdcall ChildFunc(LPVOID)
{
	::WaitForSingleObject(g_hEvent, INFINITE);
	cout << "Child thread is working....\n";
	::Sleep(5 * 1000);

	return 0;
}