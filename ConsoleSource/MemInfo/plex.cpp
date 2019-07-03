#include "_afxplex_.h"

CPlex* CPlex::Create(CPlex*& pHead, UINT nMax, UINT cbElement)
{
	CPlex *p = (CPlex*)new BYTE[sizeof(CPlex) + nMax * cbElement];
	p->pNext = pHead;
	pHead = p;
	return p;
}

void CPlex::FreeDataChain()
{
	CPlex *p = this;
	while (p != NULL)
	{
		BYTE *pBytes = (BYTE*)p;
		CPlex* pNext = p->pNext;
		delete[] pBytes;
		p = pNext;
	}
}