#include "afxtls.h"
#include <Windows.h>

void CSimpleList::AddHead(void *p)
{
	*GetNextPtr(p) = m_pHead;
	m_pHead = p;
}

bool CSimpleList::Remove(void *p)
{
	if (p == nullptr)
	{
		return false;
	}
	bool bResult = false;
	if (p == m_pHead)
	{
		m_pHead = *GetNextPtr(p);
		bResult = true;
	}
	else
	{
		void *pTest = m_pHead;
		while (pTest != nullptr && *GetNextPtr(pTest) != p)
			pTest = *GetNextPtr(pTest);

		if (pTest != nullptr)
		{
			*GetNextPtr(pTest) = *GetNextPtr(p);
			bResult = true;
		}
	}
	return bResult;
}

//CNoTrackObject
void *CNoTrackObject::operator new(size_t nSize)
{
	void *p = ::GlobalAlloc(GPTR, nSize);

	return p;
}

void CNoTrackObject::operator delete(void *p)
{
	if (p != NULL)
		::GlobalFree(p);
}


//CThreadSoltData
BYTE __afxThreadData[sizeof(CThreadSlotData)];
CThreadSlotData *afxThreadData;
struct CSlotData
{
	DWORD dwFlags;
	HINSTANCE hInst;
};

struct CThreadData : public CNoTrackObject
{
	CThreadData *pNext;
	int nCount;
	LPVOID *pData;
};

#define SLOT_USED	0x01

CThreadSlotData::CThreadSlotData()
{
	m_list.Construct(offsetof(CThreadData, pNext));
	m_nMax = 0;
	m_nAlloc = 0;
	m_nRover = 1;
	m_pSlotData = NULL;
	m_tlsIndex = ::TlsAlloc();
	::InitializeCriticalSection(&m_cs);
}