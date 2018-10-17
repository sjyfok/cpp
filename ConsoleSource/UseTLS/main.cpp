#include <iostream>
#include <Windows.h>
#include <process.h>

using namespace std;

DWORD g_tlsUsedTime;
void InitStartTime();
DWORD GetUsedTime();

UINT __stdcall ThreadFunc(LPVOID)
{
	int i;
	DWORD id, usedtime;
	InitStartTime();
	i = 10000 * 10000;
	while (i--)
	{
	}
	id = ::GetCurrentThreadId();
	usedtime = ::GetUsedTime();
	printf("This thread is coming to end. Thread ID: %d Used Time %d\n", id, usedtime);
	

	return 0;
}

int main(void)
{
	UINT uId;
	int i;
	HANDLE h[10];

	g_tlsUsedTime = ::TlsAlloc();
	for (i = 0; i < 10; i++)
	{
		h[i] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId);
	}
	for (i = 0; i < 10; i++)
	{
		::WaitForSingleObject(h[i], INFINITE);
		::CloseHandle(h[i]);
	}
	::TlsFree(g_tlsUsedTime);

	return 0;
}

void InitStartTime(void)
{
	DWORD dwStart = ::GetTickCount();
	::TlsSetValue(g_tlsUsedTime, (LPVOID)dwStart);
}

DWORD GetUsedTime(void)
{
	DWORD dwElapsed = ::GetTickCount();
	dwElapsed = dwElapsed - (DWORD)::TlsGetValue(g_tlsUsedTime);

	return dwElapsed;
}
