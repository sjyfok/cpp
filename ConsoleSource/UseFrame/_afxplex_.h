#pragma once
#include "_afxwin.h"

struct CPlex
{
	CPlex *pNext;
	void *data() { return this + 1; }   //�˴�����Ǻ�create��صģ�Create����ռ�ʱ ��һ��CPlex�ռ�+ָ��������*Ԫ�ش�С�ռ�
										//this +1 ��������CPlex�ռ䣬ָ������������ݵĿռ�
	static CPlex *Create(CPlex *&pHead, UINT nMax, UINT cbElement);
	void FreeDataChain();
};

