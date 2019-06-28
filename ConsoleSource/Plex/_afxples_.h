#pragma once
#include "_afxwin.h"

struct CPlex
{
	CPlex *pNext;
	void *data() { return this + 1; }   //此处设计是和create相关的，Create分配空间时 是一个CPlex空间+指定的数量*元素大小空间
										//this +1 正好跳过CPlex空间，指向真正存放数据的空间
	static CPlex *Create(CPlex *&pHead, UINT nMax, UINT cbElement);
	void FreeDataChain();
};

