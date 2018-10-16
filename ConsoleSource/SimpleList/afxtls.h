#ifndef __AFXTLS_H__
#define __AFXTLS_H__

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

#endif // !__AFXTLS_H__
