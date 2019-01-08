#include <iostream>
#include   "../wincommon/_afx.h"
#include "../wincommon/_afxplex_.h"
#include <process.h>

using namespace std;

struct CMyData
{
	int nSomeData;
	int nSomeMoreData;
};



int main(void)
{
	CPlex *pBlocks = NULL;
	CPlex::Create(pBlocks, 10, sizeof(CMyData));
	CMyData *pData = (CMyData*)pBlocks->data();
	CPlex::Create(pBlocks, 10, sizeof(CMyData));
	pData = (CMyData*)pBlocks->data();
	pBlocks->FreeDataChain();

	system("pause");
	return 0;
}

