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





