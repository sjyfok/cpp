#include <iostream>
#include "afxtls.h"
#include <process.h>

using namespace std;

struct CMyThreadData:public CNoTrackObject
{
	int nSomeData;
};

THREAD_LOCAL(CMyThreadData, g_myThreadData)
/*class CThreadLocalObject
{
public:
	CNoTrackObject * GetData(CNoTrackObject *(*pfnCreateObject)());
	CNoTrackObject * GetDataNA();
	DWORD m_nSlot;
	~CThreadLocalObject();
};*/
/*CThreadLocal<CMyThreadData> g_myThreadData;
class CThreadLocal : public CThreadLocalObject
public:
	CMyThreadData * GetData()
	{
		CMyThreadData *pData = (CMyThreadData*)CThreadLocalObject::GetData(&CreateObject);
		return pData;
	}
	CMyThreadData *GetDataNA()
	{
		CMyThreadData* pData = (TYPE*)CThreadLocalObject::GetDataNA();
		return pData;
	}

	operator CMyThreadData*()
	{
		return GetData();
	}
	TYPE * operator->()
	{
		return GetData();
	}
public:
	static CNoTrackObject* CreateObject()
	{
		return new CMyThreadData;
	}
};
*/
void ShowData();

UINT __stdcall ThreadFunc(LPVOID lpParam)
{
	g_myThreadData->nSomeData = (int)lpParam;
	ShowData();
	return 0;
}

int main(void)
{
	HANDLE h[10];
	UINT uID;
	for (int i = 0; i < 10; i++)
	{
		h[i] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, (void*)i, 0, &uID);
		Sleep(1);   //ÈÃ¶É´¦ÀíÆ÷
	}
	::WaitForMultipleObjects(10, h, true, INFINITE);
	for (int i = 0; i < 10; i++)
		::CloseHandle(h[i]);
	return 0;
}

void ShowData()
{
	int nData = g_myThreadData->nSomeData;
	printf("Thread ID:%-5d, nSomeData = %d\n", ::GetCurrentThreadId(), nData);

}