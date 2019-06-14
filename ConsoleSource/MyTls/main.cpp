#include <iostream>
#include "afxtls.h"
#include <process.h>

using namespace std;

struct CMyThreadData:public CNoTrackObject
{
	int nSomeData;
};

THREAD_LOCAL(CMyThreadData, g_myThreadData)   //g_myThreadData 是CThreadLocal类型的变量

void ShowData();

UINT __stdcall ThreadFunc(LPVOID lpParam)
{
	//此处是运算符重载  实际调用了GetData
	g_myThreadData->nSomeData = (int)lpParam;
	ShowData();
	return 0;
}

int main(void)
{
	HANDLE h[10];
	UINT uID;
	for (int i = 0; i < 1/*10*/; i++)
	{
		h[i] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, (void*)5, 0, &uID);
	//	Sleep(1);   //让渡处理器
	}
	::WaitForMultipleObjects(1/*10*/, h, true, INFINITE);
	for (int i = 0; i < 1/*10*/; i++)
		::CloseHandle(h[i]);
	return 0;
}

void ShowData()
{
	//int nData = (int)g_myThreadData.GetData();
	/*g_myThreadData*/
	int nData = g_myThreadData->nSomeData;
	printf("Thread ID:%-5d, nSomeData = %d\n", ::GetCurrentThreadId(), nData);

}