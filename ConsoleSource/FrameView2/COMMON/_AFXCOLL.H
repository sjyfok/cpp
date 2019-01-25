///////////////////////////////////////////
// _AFXCOLL.H�ļ�

#ifndef __AFXCOLL_H__
#define __AFXCOLL_H__

#include "_afxwin.h"
#include "_afxplex_.h"

class CMapPtrToPtr
{
protected:
	// ������Association��
	struct CAssoc
	{
		CAssoc* pNext;	// ָ����һ��CAssoc�ṹ
		void* key;	// ������
		void* value;	// ֵ����
	};

public:
// ���캯����Construction��
	CMapPtrToPtr(int nBlockSize = 10);

// ���Գ�Ա��Attributes��
	// Ԫ�صĸ���
	int GetCount() const;
	BOOL IsEmpty() const;
	// ��ӳ���в���key����Ӧ��rValue
	BOOL Lookup(void* key, void*& rValue);

// ������Operations��
	// ���һ���������key��Ӧ��value
	void*& operator[](void* key);
	// ����һ���µģ�key, vaule����
	void SetAt(void* key, void* newValue);

	// �Ƴ�һ�����ڵģ�key, ?����
	BOOL RemoveKey(void* key);
	void RemoveAll();

	UINT GetHashTableSize() const;
	void InitHashTable(UINT nHashSize, BOOL bAllocNow = TRUE);
	UINT HashKey(void* key) const;

// ʵ�֣�Implementation��
protected:
	CAssoc** m_pHashTable;
	int m_nHashTableSize;

	struct CPlex* m_pBlocks;	// ������CPlex::Create����������ڴ����׵�ַ
	int m_nBlockSize;		// ָ��ÿ���ڴ��������ɶ��ٸ�CAssoc�ṹ
	CAssoc* m_pFreeList;		// Ԥ���ռ���û�б�ʹ�õ�CAssoc�ṹ��ɵ����е�һ��������ָ��
	int m_nCount;			// ��¼�˳���һ��ʹ���˶��ٸ�CAssoc�ṹ���������ĸ���

	// Ϊһ���µ�CAssoc�ṹ�ṩ�ռ䣬�൱��ʹ��new������
	CAssoc* NewAssoc();
	// �ͷ�һ��CAssoc�ṹռ�õĿռ䣬�൱��ʹ��delete������
	void FreeAssoc(CAssoc* pAssoc);
	// Ѱ�Ҽ�key���ڵĹ���
	CAssoc* GetAssocAt(void* key, UINT& nHash) const;
public:
	~CMapPtrToPtr();
};

inline int CMapPtrToPtr::GetCount() const
{ return m_nCount; }
inline BOOL CMapPtrToPtr::IsEmpty() const
{ return m_nCount == 0; }
inline void CMapPtrToPtr::SetAt(void* key, void* newValue)
{ (*this)[key] = newValue; }
inline UINT CMapPtrToPtr::GetHashTableSize() const
{ return m_nHashTableSize; }	

#endif // __AFXCOLL_H__