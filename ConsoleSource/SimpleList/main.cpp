#include <iostream>
#include "afxtls.h"

using namespace std;

struct MyThreadData
{
	MyThreadData *pNext;
	int nSomeData;
};

int main(void)
{
	MyThreadData *pData;
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
	//Ê¹ÓÃÄ£°å
	MyThreadData *pTData;
	CTypedSimpleList<MyThreadData*>tlist;
	tlist.Construct(offsetof(MyThreadData, pNext));
	for (int i = 0; i < 10; i++)
	{
		pData = new MyThreadData;
		pData->nSomeData = i;
		tlist.AddHead(pData);
	}
	pData = tlist;
	while (pData != nullptr)
	{
		MyThreadData *pNextData = pData->pNext;
		cout << "The value of nSomeData is " << pData->nSomeData << endl;
		delete pData;
		pData = pNextData;
	}
	return 0;
}