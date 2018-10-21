#include <iostream>
#include "afxtls.h"
#include <process.h>

#define USING_TEMPLATE

using namespace std;

struct CMyThreadData
{
	CMyThreadData *pNext;
	int nSomeData;
};



int main(void)
{
	CMyThreadData *pData;
#ifdef USING_TEMPLATE
	CTypedSimpleList<CMyThreadData*>list;
#else
	CSimpleList list;
#endif
	list.Construct(offsetof(CMyThreadData, pNext));

	for (int i = 0; i < 10; i++)
	{
		pData = new CMyThreadData;
		pData->nSomeData = i;
		list.AddHead(pData);
	}

#ifdef USING_TEMPLATE
	pData = list;
#else
	pData = (CMyThreadData*)list.GetHead();
#endif
	while (pData != NULL)
	{
		CMyThreadData *pNextData = pData->pNext;
		printf("The value of nSomeData is : %d\n", pData->nSomeData);
		delete pData;
		pData = pNextData;
	}
	return 0;
}

