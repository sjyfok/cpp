#pragma once

#include "_afxwin.h"
#include "_afxplex_.h"

class CMapPtrToPtr
{
protected:
	struct CAssoc
	{
		CAssoc* pNext;
		void *key;
		void *value;
	};
public:
	CMapPtrToPtr(int nBlockSize = 10);
	int GetCount() const;
	BOOL IsEmpty() const;
	BOOL Lookup(void* key, void *&rValue);
	void *& operator[](void *key);
	void SetAt(void* key, void *newValue);
	BOOL RemoveKey(void *key);
	void RemoveAll();
	UINT GetHashTableSize() const;
	void InitHashTable(UINT nHashSize, BOOL bAllocNow = TRUE);
	UINT HashKey(void *key) const;
	~CMapPtrToPtr();
protected:
	CAssoc * *m_pHashTable;
	int m_nHashTableSize;
	struct CPlex *m_pBlocks;
	int m_nBlockSize;
	CAssoc *m_pFreeList;
	int m_nCount;
	CAssoc *NewAssoc();
	void FreeAssoc(CAssoc *pAssoc);
	CAssoc* GetAssocAt(void *key, UINT &nHash) const;
};

inline int CMapPtrToPtr::GetCount() const
{
	return m_nCount;
}

inline BOOL CMapPtrToPtr::IsEmpty() const
{
	return m_nCount == 0;
}

inline void CMapPtrToPtr::SetAt(void *key, void *newValue)
{
	(*this)[key] = newValue;
}

inline UINT CMapPtrToPtr::GetHashTableSize() const
{
	return m_nHashTableSize;
}

inline UINT CMapPtrToPtr::HashKey(void *key) const
{
	return ((UINT)(void*)(DWORD)key) >> 4;
}

