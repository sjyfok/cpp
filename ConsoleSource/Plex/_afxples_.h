#pragma once
#include "_afxwin.h"

struct CPlex
{
	CPlex *pNext;
	void *data() { return this + 1; }
	static CPlex *Create(CPlex *&pHead, UINT nMax, UINT cbElement);
	void FreeDataChain();
};

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
	while (p!= NULL)
	{
		BYTE *pBytes = (BYTE*)p;
		CPlex* pNext = p->pNext;
		delete[] pBytes;
		p = pNext;
	}
}