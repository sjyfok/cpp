///////////////////////////////////////////////////////
// _AFXTLS_.H�ļ�



#ifndef __AFXTLS_H__  // _AFXTLS_.H �ļ�
#define __AFXTLS_H__

#include <windows.h>
#include <stddef.h>


class CNoTrackObject;

////////////////////////////////////////////////
// CSimpleList

class CSimpleList
{
public:
	CSimpleList(int nNextOffset = 0);
	void Construct(int nNextOffset);

// �ṩ���û��Ľӿں�����Operations�����������ӡ�ɾ���ͱ����ڵ�
	BOOL IsEmpty() const;
	void AddHead(void* p);
	void RemoveAll();
	void* GetHead() const;
	void* GetNext(void* p) const;
	BOOL Remove(void* p);

// Ϊʵ�ֽӿں�������ĳ�Ա��Implementation��
	void* m_pHead;		// �����е�һ��Ԫ�صĵ�ַ
	size_t m_nNextOffset;	// ���ݽṹ��pNext��Ա��ƫ����
	void** GetNextPtr(void* p) const;
};

// �����������
inline CSimpleList::CSimpleList(int nNextOffset)
{ m_pHead = NULL; m_nNextOffset = nNextOffset; }
inline void CSimpleList::Construct(int nNextOffset)
{ m_nNextOffset = nNextOffset; }
inline BOOL CSimpleList::IsEmpty() const
{ return m_pHead == NULL; }
inline void CSimpleList::RemoveAll()
{ m_pHead = NULL; }
inline void* CSimpleList::GetHead() const
{ return m_pHead; }
inline void* CSimpleList::GetNext(void* preElement) const
{ return *GetNextPtr(preElement); }
inline void** CSimpleList::GetNextPtr(void* p) const
{ return (void**)((BYTE*)p + m_nNextOffset); }


template<class TYPE>
class CTypedSimpleList : public CSimpleList
{
public:
	CTypedSimpleList(int nNextOffset = 0) 
		: CSimpleList(nNextOffset) { }
	void AddHead(TYPE p) 
		{ CSimpleList::AddHead((void*)p); }
	TYPE GetHead()
		{ return (TYPE)CSimpleList::GetHead(); }
	TYPE GetNext(TYPE p)
		{ return (TYPE)CSimpleList::GetNext(p); }
	BOOL Remove(TYPE p)
		{ return CSimpleList::Remove(p); }
	operator TYPE()
		{ return (TYPE)CSimpleList::GetHead(); }
};


////////////////////////////////////////////////
// CNoTrackObject
class CNoTrackObject
{
public:
	void* operator new(size_t nSize);
	void operator delete(void*);
	virtual ~CNoTrackObject() { }
};

/////////////////////////////////////////////////
// CThreadSlotData - ���������Լ����ֲ߳̾��洢

// warning C4291: no matching operator delete found
#pragma warning(disable : 4291) 

struct CSlotData;
struct CThreadData;

class CThreadSlotData
{
public:
	CThreadSlotData();

// �ṩ���û��Ľӿں�����Operations��
	int AllocSlot();	
	void FreeSlot(int nSlot); 
	void* GetThreadValue(int nSlot); 
	void SetValue(int nSlot, void* pValue);
	void DeleteValues(HINSTANCE hInst, BOOL bAll = FALSE);

// ���ʵ�ִ��루Implementations��
	DWORD m_tlsIndex;	// ��������ϵͳ�ṩ���ֲ߳̾��洢

	int m_nAlloc;		//  m_pSlotData��ָ������Ĵ�С
	int m_nRover;		// Ϊ�˿����ҵ�һ�����еĲ۶��趨��ֵ
	int m_nMax;		// CThreadData�ṹ��pDataָ�������Ĵ�С
	CSlotData* m_pSlotData;	// ��ʶÿ����״̬��ȫ��������׵�ַ
	CTypedSimpleList<CThreadData*> m_list;	// CThreadData�ṹ���б�
	CRITICAL_SECTION m_cs;

	void* operator new(size_t, void* p)
			{ return p; }
	void DeleteValues(CThreadData* pData, HINSTANCE hInst);
	~CThreadSlotData();
};


///////////////////////////////////////////////

class CThreadLocalObject
{
public:
// ���Գ�Ա(Attributes)������ȡ�ñ������ֲ߳̾��ı����е�ָ��
	CNoTrackObject* GetData(CNoTrackObject* (*pfnCreateObject)());
	CNoTrackObject* GetDataNA();

// ����ʵ��(Implementation)
	DWORD m_nSlot;
	~CThreadLocalObject();
};


template<class TYPE>
class CThreadLocal : public CThreadLocalObject
{
// ���Գ�Ա��Attributes��
public:
	TYPE* GetData()
	{
		TYPE* pData = (TYPE*)CThreadLocalObject::GetData(&CreateObject);
		return pData;
	}
	TYPE* GetDataNA()
	{
		TYPE* pData = (TYPE*)CThreadLocalObject::GetDataNA();
		return pData;
	}
	operator TYPE*()
		{ return GetData(); }
	TYPE* operator->()
		{ return GetData(); }

// ����ʵ�֣�Implementation��
public:
	static CNoTrackObject* CreateObject()
		{ return new TYPE; }
};


#define THREAD_LOCAL(class_name, ident_name) \
	CThreadLocal<class_name> ident_name;
#define EXTERN_THREAD_LOCAL(class_name, ident_name) \
	extern THREAD_LOCAL(class_name, ident_name)


#endif // __AFXTLS_H__


/*


2.2.4 


#ifndef __AFXTLS_H__  // _AFXTLS_.H �ļ�
#define __AFXTLS_H__

#include <windows.h>

class CThreadLocalObject
{
public:
	CThreadLocalObject();

// ���Գ�Ա(Attributes)������ȡ�ñ������ֲ߳̾��ı����е�ָ��
	LPVOID GetData(LPVOID (*pfnCreateObject)());
	LPVOID GetDataNA();

// ִ����(Implementation)��ʵ����ӿ�����ĳ�Ա
	DWORD m_tlsIndex;
	~CThreadLocalObject();	
};

#endif // __AFXTLS_H__










 */