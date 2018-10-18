#ifndef __AFXTLS_H__
#define __AFXTLS_H__

#include <Windows.h>

//step 1
class CSimpleList
{
public:
	CSimpleList(int nNextOffset = 0);
	void Construct(int nNextOffset);

	bool IsEmpty() const;
	void AddHead(void *p);
	void RemoveAll();
	void *GetHead() const;
	void *GetNext(void *p)const;
	bool Remove(void *p);

	void *m_pHead;
	size_t m_nNextOffset;
	void **GetNextPtr(void *p) const;
};
inline CSimpleList::CSimpleList(int nNextOffset)
{
	m_pHead = nullptr;
	m_nNextOffset = nNextOffset;
}

inline void CSimpleList::Construct(int nNextOffset)
{
	m_nNextOffset = nNextOffset;
}

inline bool CSimpleList::IsEmpty() const
{
	return m_pHead == nullptr;
}

inline void CSimpleList::RemoveAll()
{
	m_pHead = nullptr;
}

inline void *CSimpleList::GetHead() const
{
	return m_pHead;
}

inline void * CSimpleList::GetNext(void *preElement) const
{
	return *GetNextPtr(preElement);
}

inline void **CSimpleList::GetNextPtr(void *p) const
{
	return (void **)((unsigned char*)p + m_nNextOffset);
}


//step2
template <class TYPE>
class CTypedSimpleList : public CSimpleList
{
public :
	CTypedSimpleList(int nNextOffset = 0)
		:CSimpleList(nNextOffset) {}
	void AddHead(TYPE p)
	{
		CSimpleList::AddHead((void*)p);
	}
	TYPE GetHead()
	{
		return (TYPE)CSimpleList::GetHead();
	}
	TYPE GetNext(TYPE p)
	{
		return (TYPE)CSimpleList::GetNext(p);
	}
	bool Remove(TYPE p)
	{
		return CSimpleList::Remove(p);
	}
	operator TYPE()
	{
		return (TYPE)CSimpleList::GetHead();
	}
};

class CNoTrackObject
{
public:
	void *operator new(size_t nSize);
	void operator delete(void *);
	virtual ~CNoTrackObject() {}
};

struct CSlotData;
struct CThreadData;
class CThreadSlotData
{
public:
	CThreadSlotData();
	int AllocSlot();
	void FreeSlot(int nSlot);
	void *GetThreadValue(int nSlot);
	void SetValue(int nSlot, void *pValue);
	void DeleteValues(HINSTANCE hInst, bool bAll = false);

	DWORD m_tlsIndex;
	int m_nAlloc;
	int m_nRover;
	int m_nMax;
	CSlotData *m_pSlotData;
	CTypedSimpleList<CThreadData*>m_list;
	CRITICAL_SECTION m_cs;
	void *operator new(size_t, void *p)
	{
		return p;
	}
	void DeleteValues(CThreadData *pData, HINSTANCE hInst);
	~CThreadSlotData();
};

class CThreadLocalObject
{
public:
	CNoTrackObject * GetData(CNoTrackObject *(*pfnCreateObject)());
	CNoTrackObject * GetDataNA();
	DWORD m_nSlot;
	~CThreadLocalObject();
};

template <class TYPE>
class CThreadLocal : public CThreadLocalObject
{
public:
	TYPE * GetData()
	{
		TYPE *pData = (TYPE*)CThreadLocalObject::GetData(&CreateObject);
		return pData;
	}
	TYPE *GetDataNA()
	{
		TYPE* pData = (TYPE*)CThreadLocalObject::GetDataNA();
		return pData;
	}

	operator TYPE*()
	{
		return GetData();
	}
	TYPE * operator->()
	{
		return GetData();
	}
public:
	static CNoTrackObject* CreateObject()
	{
		return new TYPE;
	}
};

#define THREAD_LOCAL(class_name, ident_name) \
	CThreadLocal<class_name> ident_name;
#define EXTERN_THREAD_LOCAL(class_name, ident_name) \
	extern THREAD_LOCAL(class_name, ident_name)
#endif // !__AFXTLS_H__
