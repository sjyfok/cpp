#include <iostream>
#include <windows.h>
#include <process.h>

#undef	USING_NONE
#undef	USING_CRITICAL_SECTION	
#define	USING_INTERLOCKED	

using namespace std;

int g_nCount1 = 0;
int g_nCount2 = 0;
#ifdef USING_CRITICAL_SECTION
CRITICAL_SECTION g_cs;
#endif

bool g_bContinue = true;
UINT __stdcall	ThreadFunc(LPVOID);

int main(void)
{
	UINT uId;
	HANDLE h[2];
#ifdef USING_CRITICAL_SECTION
	::InitializeCriticalSection(&g_cs);
#endif
	h[0] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId);
	h[1] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId);
	Sleep(1000);
	g_bContinue = false;
	::WaitForMultipleObjects(2, h, true, INFINITE);
	::CloseHandle(h[0]);
	::CloseHandle(h[1]);
#ifdef USING_CRITICAL_SECTION
	::DeleteCriticalSection(&g_cs);
#endif
	cout << "g_nCount1 = " << g_nCount1 << endl;
	cout << "g_nCount2 = " << g_nCount2 << endl;
	return 0;
}

UINT __stdcall ThreadFunc(LPVOID)
{
	while (g_bContinue)
	{
#ifdef USING_CRITICAL_SECTION
		::EnterCriticalSection(&g_cs);
		g_nCount1++;
		g_nCount2++;
#endif
#ifdef USING_NONE
		g_nCount1++;
		g_nCount2++;
#endif
#ifdef USING_CRITICAL_SECTION
		::LeaveCriticalSection(&g_cs);
#endif
#ifdef USING_INTERLOCKED
		::InterlockedIncrement((long*)&g_nCount1);
		::InterlockedIncrement((long*)&g_nCount2);
#endif // USING_INTERLOCKED

	}
	return 0;
}