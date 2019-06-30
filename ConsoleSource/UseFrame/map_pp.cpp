#include "_afxcoll.h"

CMapPtrToPtr::CAssoc* CMapPtrToPtr::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		CPlex *newBlock = CPlex::Create(m_pBlocks, m_nBlockSize, sizeof(CAssoc));
		CAssoc *pAssoc = (CAssoc*)newBlock->data();
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	CAssoc *pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	pAssoc->key = 0;
	pAssoc->value = 0;
	return pAssoc;
}

void CMapPtrToPtr::FreeAssoc(CAssoc* pAssoc)
{
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	if (m_nCount == 0)
	{
		RemoveAll();
	}
}

void CMapPtrToPtr::InitHashTable(UINT nHashSize, BOOL bAllocNow)
{
	if (m_pHashTable != NULL)
	{
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}
	if (bAllocNow)
	{
		m_pHashTable = new CAssoc*[nHashSize];
		memset(m_pHashTable, 0, sizeof(CAssoc*)*nHashSize);
	}
	m_nHashTableSize = nHashSize;
}

CMapPtrToPtr::CAssoc* CMapPtrToPtr::GetAssocAt(void *key, UINT &nHash) const
{
	nHash = HashKey(key) % m_nHashTableSize;
	if (m_pHashTable == NULL)
	{
		return NULL;
	}
	CAssoc *pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
		{
			return pAssoc;
		}
	}
	return NULL;
}

bool CMapPtrToPtr::Lookup(void *key, void *& rValue)
{
	UINT nHash;
	CAssoc *pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
	{
		return FALSE;
	}
	rValue = pAssoc->value;
	return TRUE;
}

void *&CMapPtrToPtr::operator[](void *key)
{
	UINT nHash;
	CAssoc *pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
		{
			InitHashTable(m_nHashTableSize);
		}
		pAssoc = NewAssoc();
		pAssoc->key = key;
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;
}

bool CMapPtrToPtr::RemoveKey(void *key)
{
	if (m_pHashTable == NULL)
	{
		return FALSE;
	}
	CAssoc** ppAssocPre;
	ppAssocPre = &m_pHashTable[HashKey(key) % m_nHashTableSize];
	CAssoc *pAssoc;
	for (pAssoc = *ppAssocPre; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
		{
			*ppAssocPre = pAssoc->pNext;
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPre = &pAssoc->pNext;
	}
	return FALSE;
}

CMapPtrToPtr::CMapPtrToPtr(int nBlockSize)
{
	m_pHashTable = NULL;
	m_nHashTableSize = 17;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
	m_pFreeList = NULL;
	m_nCount = 0;
}

CMapPtrToPtr::~CMapPtrToPtr()
{
	RemoveAll();
}

void CMapPtrToPtr::RemoveAll()
{
	if (m_pHashTable != NULL)
	{
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

