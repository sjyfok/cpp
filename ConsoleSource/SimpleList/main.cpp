#include <iostream>
#include "afxtls.h"

#undef	USING_SIMPLELIST
#define  USING_SIMPLELIST_TEMPLATE
#undef  USING_MYMALLOC


using namespace std;

#ifndef USING_MYMALLOC
struct CThreadData
{
	CThreadData *pNext;
	int nSomeData;
};
#else
struct CThreadData : public CNoTrackObject
{
	CThreadData *pNext;
	int nCount;
	LPVOID pData;
};
#endif

int main(void)
{
	CThreadData *pData;
#ifdef USING_SIMPLELIST	
	CSimpleList list;
	list.Construct(offsetof(MyThreadData, pNext));
	for (int i = 0; i < 10; i++)
	{
		pData = new MyThreadData;
		pData->nSomeData = i;
		list.AddHead(pData);
	}

	pData = (MyThreadData*)list.GetHead();
	while (pData != nullptr)
	{
		MyThreadData *pNextData = pData->pNext;
		cout << "The value of nSomeData is " << pData->nSomeData << endl;
		delete pData;
		pData = pNextData;
	}
	cout << "\n" << endl;
#endif
	//Ê¹ÓÃÄ£°å
#ifdef  USING_SIMPLELIST_TEMPLATE
	CTypedSimpleList<CThreadData*>tlist;
	tlist.Construct(offsetof(CThreadData, pNext));
	for (int i = 0; i < 10; i++)
	{
		pData = new CThreadData;
		pData->nSomeData = i;
		tlist.AddHead(pData);
	}
	pData = tlist;
	while (pData != nullptr)
	{
		CThreadData *pNextData = pData->pNext;
		cout << "The value of nSomeData is " << pData->nSomeData << endl;
		delete pData;
		pData = pNextData;
	}
#endif
	return 0;
}