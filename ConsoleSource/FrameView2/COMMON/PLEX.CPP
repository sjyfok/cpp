///////////////////////////////////////////////////////
// PLEX.CPP�ļ�



#include "_afxplex_.h"

CPlex* CPlex::Create(CPlex*& pHead, UINT nMax, UINT cbElement)
{
	CPlex* p = (CPlex*)new BYTE[sizeof(CPlex) + nMax*cbElement];

	// �������ӵ��ڴ�����ӵ����У��������ַ��Ϊ�׵�ַ
	p->pNext = pHead;
	pHead = p;		// ���෴��������������ķ�ʽ�������˳������
	return p;
}

void CPlex::FreeDataChain()
{
	// �Ե�ǰ�ڴ��ĵ�ַΪ�׵�ַ
	CPlex* p = this;
	// �ͷ����������ڴ��ռ�õ��ڴ�
	while(p != NULL)
	{
		BYTE* pBytes = (BYTE*)p;
		CPlex* pNext = p->pNext;
		delete[] pBytes;
		p = pNext;
	}
}