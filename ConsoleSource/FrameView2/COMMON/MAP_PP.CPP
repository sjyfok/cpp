///////////////////////////////////////////////////////
// MAP_PP.CPP�ļ�


#include "_afxcoll.h"

CMapPtrToPtr::CMapPtrToPtr(int nBlockSize)
{
	m_pHashTable = NULL;
	m_nHashTableSize = 17;	// Ĭ�ϴ�С
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
	m_pFreeList = NULL;
	m_nCount = 0;
}

inline UINT CMapPtrToPtr::HashKey(void* key) const
{
	return ((UINT)(void*)(DWORD)key) >> 4;
}

void CMapPtrToPtr::InitHashTable(UINT nHashSize, BOOL bAllocNow)
{
	if(m_pHashTable != NULL)
	{
		// �ͷż����
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}

	if(bAllocNow)
	{
		// Ϊ���������ռ�
		m_pHashTable = new CAssoc*[nHashSize];
		memset(m_pHashTable, 0, sizeof(CAssoc*)*nHashSize);
	}
	m_nHashTableSize = nHashSize;
}

CMapPtrToPtr::CAssoc* CMapPtrToPtr::GetAssocAt(void* key, UINT& nHash) const
{
	// �������key�����ڱ��е�λ��
	nHash = HashKey(key)%m_nHashTableSize;
	if(m_pHashTable == NULL)
		return NULL;

	// ����m_pHashTable[nHash]Ϊͷָ��������в���
	CAssoc* pAssoc;
	for(pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if(pAssoc->key == key)
			return pAssoc;
	}
	return NULL;
}

BOOL CMapPtrToPtr::Lookup(void* key, void*& rValue)
{
	UINT nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if(pAssoc == NULL)
		return FALSE;	// û����ӳ����

	rValue = pAssoc->value;
	return TRUE;
}

void*& CMapPtrToPtr::operator [] (void* key)
{
	UINT nHash;
	CAssoc* pAssoc;
	if((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if(m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// ��Ȼӳ����û���û�ָ��������Ǿ�����һ���µĹ���
		pAssoc = NewAssoc();
		pAssoc->key = key;

		// ���µĹ������������У����ڱ�ͷ�����Ǳ�β��
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value; // ����value������
}

BOOL CMapPtrToPtr::RemoveKey(void* key)
{
	if(m_pHashTable == NULL) 
		return FALSE;	// ����ʲôҲû��

	CAssoc** ppAssocPre;	// ��¼Ҫɾ������ĵ�ַ�ı����ĵ�ַ��������ڵĻ������ǻ�ı�˵�ַ����ֵ��
	ppAssocPre = &m_pHashTable[HashKey(key)%m_nHashTableSize];

	CAssoc* pAssoc;
	for(pAssoc = *ppAssocPre; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if(pAssoc->key == key)
		{
			// �Ƴ�pAssocָ�����
			*ppAssocPre = pAssoc->pNext;  // �ӱ����Ƴ�
			FreeAssoc(pAssoc);	      // �ͷ��ڴ�
			return TRUE;
		}
		ppAssocPre = &pAssoc->pNext;
	}
	return FALSE; // û���ҵ�
}

CMapPtrToPtr::~CMapPtrToPtr()
{
	RemoveAll();
}

void CMapPtrToPtr::RemoveAll()
{
	if(m_pHashTable != NULL)
	{
		// �ͷż����
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

CMapPtrToPtr::CAssoc* CMapPtrToPtr::NewAssoc()
{
	// Ԥ���Ŀռ��Ѿ���ʹ����
	if(m_pFreeList == NULL)
	{
		// ��m_pBlocksָ�����������һ���µ��ڴ�顣m_nBlockSize��ֵ�������û�ָ��
		CPlex* newBlock = CPlex::Create(m_pBlocks, m_nBlockSize, sizeof(CAssoc));

		// �����ڴ���и�CAssoc�ṹ���ӵ�m_pFreeListָ������У���������
		CAssoc* pAssoc = (CAssoc*)newBlock->data();
		pAssoc += m_nBlockSize -1;	// ע�⣬��ʱpAssocָ���ڴ�������һ��CAssoc�ṹ	
		for(int i = m_nBlockSize -1; i >= 0; i--, pAssoc--)
		{
			// ��pAssoc��Ϊ�����׵�ַ���ӵ��������У��������෴��˳������������Ԫ�أ�
			pAssoc->pNext = m_pFreeList; 
			m_pFreeList = pAssoc;
		}
	}

	// �ӿ�������ȡ��һ��Ԫ��pAssoc
	CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext; 
	m_nCount++;				// �ֶ�ʹ����һ��CAssoc�ṹ

	// ��ʼ���¹�����ֵ
	pAssoc->key = 0;
	pAssoc->value = 0;
	return pAssoc;
}

void CMapPtrToPtr::FreeAssoc(CAssoc* pAssoc)
{
	// ��Ҫ�ͷŵĹ�����Ϊ�����׵�ַ���ӵ��������У����෴��˳��
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;				// �ͷ���һ��CAssoc�ṹ

	// ���ȫ���Ĺ�����û��ʹ�ã����ͷ����е��ڴ�ռ䣬����CPlex::Create����������ڴ��
	if(m_nCount == 0)
		RemoveAll();  // �˺������ͷ������ڴ�ռ䣬���������������
}








