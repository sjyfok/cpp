///////////////////////////////////////////
// _AFXPLEX_.H�ļ�

#ifndef __AFXPLEX_H__
#define __AFXPLEX_H__

#include "_afxwin.h"

struct CPlex
{
	CPlex* pNext; // ��ÿ���ڲ�������ӵĶ�����Ϣ��ָ����һ���ڴ���׵�ַ��ָ��

	// ��������������������BYTE data[maxNum*elementSize];
	void* data() { return this + 1; }

	// ���������ڴ��ȫ�ֺ���������cbElement��С�Ŀռ�nMax��
	static CPlex* Create(CPlex*& pHead, UINT nMax, UINT cbElement);

	// �ͷ��Ե�ǰ����Ϊ�׵�ַ��thisָ�룩���ڴ����е������ڴ�
	void FreeDataChain();
};

#endif // __AFXPLEX_H__