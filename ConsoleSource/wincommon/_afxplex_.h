#ifndef __AFXPLEX__H__
#define __AFXPLEX__H__

#include "_afxwin.h"

struct CPlex
{
	CPlex *pNext;
	void *data() { return this + 1; }
	static CPlex *Create(CPlex *&pHead, UINT nMax, UINT cbElement);
	void FreeDataChain();
};



#endif // !__AFXPLEX__H__
