///////////////////////////////////////////////////////
// AFXTLS.CPP�ļ�



#include "_AFXTLS_.H"


//---------------------------------------

void CSimpleList::AddHead(void* p)
{
	*GetNextPtr(p) = m_pHead;
	m_pHead = p;
}

BOOL CSimpleList::Remove(void* p)
{
	if(p == NULL)	// ������
		return FALSE;
	
	BOOL bResult = FALSE; // �����Ƴ�ʧ��
	if(p == m_pHead)
	{
	// Ҫ�Ƴ�ͷԪ��
		m_pHead = *GetNextPtr(p);
		bResult = TRUE;
	}
	else
	{
		// ��ͼ�ڱ��в���Ҫ�Ƴ���Ԫ��
		void* pTest = m_pHead;
		while(pTest != NULL && *GetNextPtr(pTest) != p)
			pTest = *GetNextPtr(pTest);

		// ����ҵ����ͽ�Ԫ���Ƴ�
		if(pTest != NULL)
		{
			*GetNextPtr(pTest) = *GetNextPtr(p);
			bResult = TRUE;
		}
	}
	return bResult;
}

//-------------------CThreadSlotData��----------------------//
BYTE __afxThreadData[sizeof(CThreadSlotData)];	// Ϊ�����_afxThreadData�����ṩ�ڴ�
CThreadSlotData* _afxThreadData; // ����ȫ�ֱ���_afxThreadData��Ϊȫ�ֱ�������ռ�

struct CSlotData
{
	DWORD dwFlags;	// �۵�ʹ�ñ�־��������/δ�����䣩
	HINSTANCE hInst;// ռ�ô˲۵�ģ����
};

struct CThreadData : public CNoTrackObject
{
	CThreadData* pNext; // CSimpleList��Ҫʹ�ô˳�Ա
	int nCount;	    // ����Ԫ�صĸ���
	LPVOID* pData;      // ������׵�ַ
};

#define SLOT_USED 0x01		// CSlotData�ṹ��dwFlags��Ա��ֵΪ0x01ʱ��ʾ�ò��ѱ�ʹ��

CThreadSlotData::CThreadSlotData()
{
	m_list.Construct(offsetof(CThreadData, pNext)); // ��ʼ��CTypedSimpleList����

	m_nMax = 0;
	m_nAlloc = 0;
	m_nRover = 1;	// ���Ǽٶ�Slot1��δ�����䣨��һ���ۣ�Slot0�����Ǳ�����������ʹ�ã�
	m_pSlotData = NULL;

	m_tlsIndex = ::TlsAlloc();	// ʹ��ϵͳ��TLS����һ������
	::InitializeCriticalSection(&m_cs);	// ��ʼ���ؼ��α���
}

int CThreadSlotData::AllocSlot()
{
	::EnterCriticalSection(&m_cs);	// �����ٽ�����Ҳ�йؼ��Σ�
	int nAlloc = m_nAlloc;
	int nSlot = m_nRover;

	if(nSlot >= nAlloc || m_pSlotData[nSlot].dwFlags & SLOT_USED)
	{
		// ����m_pSlotData�����ҿղۣ�SLOT��
		for(nSlot = 1; nSlot < nAlloc && m_pSlotData[nSlot].dwFlags & SLOT_USED; nSlot ++) ;

		// ��������ڿղۣ��������Ŀռ�
		if(nSlot >= nAlloc)
		{
			// ����ȫ������Ĵ�С��������ٷ����ڴ��Դ����²�
			int nNewAlloc = nAlloc + 32;

			HGLOBAL hSlotData;
			if(m_pSlotData == NULL)	// ��һ��ʹ��
			{
				hSlotData = ::GlobalAlloc(GMEM_MOVEABLE, nNewAlloc*sizeof(CSlotData));
			}
			else
			{
				hSlotData = ::GlobalHandle(m_pSlotData);
				::GlobalUnlock(hSlotData);
				hSlotData = ::GlobalReAlloc(hSlotData, 
					nNewAlloc*sizeof(CSlotData), GMEM_MOVEABLE);
			}
			CSlotData* pSlotData = (CSlotData*)::GlobalLock(hSlotData);
	
			// ��������Ŀռ��ʼ��Ϊ0
			memset(pSlotData + m_nAlloc, 0, (nNewAlloc - nAlloc)*sizeof(CSlotData));
			m_nAlloc = nNewAlloc;
			m_pSlotData = pSlotData;
		}
	}

	// ����m_nMax��ֵ���Ա�Ϊ���̵߳�˽�����ݷ����ڴ�
	if(nSlot >= m_nMax)
		m_nMax = nSlot + 1;

	m_pSlotData[nSlot].dwFlags |= SLOT_USED;
	// ����m_nRover��ֵ(���Ǽ�����һ����δ��ʹ��)
	m_nRover = nSlot + 1;

	::LeaveCriticalSection(&m_cs);
	return nSlot; // ���صĲۺſ��Ա�FreeSlot, GetThreadValue, SetValue����ʹ����
}

void CThreadSlotData::FreeSlot(int nSlot)
{
	::EnterCriticalSection(&m_cs);	

	// ɾ�������߳��е�����
	CThreadData* pData = m_list;
	while(pData != NULL)
	{
		if(nSlot < pData->nCount)
		{
			delete (CNoTrackObject*)pData->pData[nSlot];
			pData->pData[nSlot] = NULL;
		}
		pData = pData->pNext;
	}

	// ���˲ۺű�ʶΪδ��ʹ��
	m_pSlotData[nSlot].dwFlags &= ~SLOT_USED;
	::LeaveCriticalSection(&m_cs);
}

inline void* CThreadSlotData::GetThreadValue(int nSlot)
{
	CThreadData* pData = (CThreadData*)::TlsGetValue(m_tlsIndex);
	if(pData == NULL || nSlot >= pData->nCount)
		return NULL;
	return pData->pData[nSlot];
}

void CThreadSlotData::SetValue(int nSlot, void* pValue)
{
	// ͨ��TLS�����õ�����Ϊ�̰߳��ŵ�˽�д洢�ռ�
	CThreadData* pData = (CThreadData*)::TlsGetValue(m_tlsIndex);

	// Ϊ�߳�˽�����������ڴ�ռ�
	if((pData == NULL || nSlot >= pData->nCount) && pValue != NULL)
	{
		// pData��ֵΪ�գ���ʾ���̵߳�һ�η����߳�˽������
		if(pData == NULL)
		{
			pData = new CThreadData;
			pData->nCount = 0;
			pData->pData = NULL;

			// ����������ڴ�ĵ�ַ���ӵ�ȫ���б���
			::EnterCriticalSection(&m_cs);
			m_list.AddHead(pData);
			::LeaveCriticalSection(&m_cs);
		}

		// pData->pDataָ���������߳�˽�����ݣ�����Ĵ��뽫˽������ռ�õĿռ�������m_nMaxָ���Ĵ�С
		if(pData->pData == NULL)
			pData->pData = (void**)::GlobalAlloc(LMEM_FIXED, m_nMax*sizeof(LPVOID));
		else
			pData->pData = (void**)::GlobalReAlloc(pData->pData, m_nMax*sizeof(LPVOID), LMEM_MOVEABLE);
		
		// ����������ڴ��ʼ��Ϊ0
		memset(pData->pData + pData->nCount, 0, 
			(m_nMax - pData->nCount) * sizeof(LPVOID));
		pData->nCount = m_nMax;
		::TlsSetValue(m_tlsIndex, pData);
	}

	// �����߳�˽�����ݵ�ֵ
	pData->pData[nSlot] = pValue;
}

void CThreadSlotData::DeleteValues(HINSTANCE hInst, BOOL bAll)
{
	::EnterCriticalSection(&m_cs);
	if(!bAll)
	{
		// ����ɾ����ǰ�̵߳��ֲ߳̾��洢ռ�õĿռ�
		CThreadData* pData = (CThreadData*)::TlsGetValue(m_tlsIndex);
		if(pData != NULL)
			DeleteValues(pData, hInst);
	}
	else
	{
		// ɾ�������̵߳��ֲ߳̾��洢ռ�õĿռ�
		CThreadData* pData = m_list.GetHead();
		while(pData != NULL)
		{
			CThreadData* pNextData = pData->pNext;
			DeleteValues(pData, hInst);
			pData = pNextData;
		}
	}
	::LeaveCriticalSection(&m_cs);
}

void CThreadSlotData::DeleteValues(CThreadData* pData, HINSTANCE hInst)
{
	// �ͷű��е�ÿһ��Ԫ��
	BOOL bDelete = TRUE;
	for(int i=1; i<pData->nCount; i++)
	{
		if(hInst == NULL || m_pSlotData[i].hInst == hInst)
		{
			// hInstƥ�䣬ɾ������
			delete (CNoTrackObject*)pData->pData[i];
			pData->pData[i] = NULL;
		}
		else
		{
			// ��������ģ����ʹ�ã���Ҫɾ������
			if(pData->pData[i] != NULL)
			bDelete = FALSE;
		}
	}

	if(bDelete)
	{
		// ���б����Ƴ�
		::EnterCriticalSection(&m_cs);
		m_list.Remove(pData);
		::LeaveCriticalSection(&m_cs);
		::LocalFree(pData->pData);
		delete pData;

		// ���TLS��������ֹ����
		::TlsSetValue(m_tlsIndex, NULL);
	}
}

CThreadSlotData::~CThreadSlotData()
{
	CThreadData *pData = m_list;
	while(pData != NULL)
	{
		CThreadData* pDataNext = pData->pNext;
		DeleteValues(pData, NULL);
		pData = pData->pNext;
	}

	if(m_tlsIndex != (DWORD)-1)
		::TlsFree(m_tlsIndex);

	if(m_pSlotData != NULL)
	{
		HGLOBAL hSlotData = ::GlobalHandle(m_pSlotData);
		::GlobalUnlock(hSlotData);
		::GlobalFree(m_pSlotData);
	}

	::DeleteCriticalSection(&m_cs);
}

//---------------------------------------

void* CNoTrackObject::operator new(size_t nSize)
{
	// ����һ�����GMEM_FIXED��GMEM_ZEROINIT��־���ڴ�
	void* p = ::GlobalAlloc(GPTR, nSize);
	return p;
}

void CNoTrackObject::operator delete(void* p)
{
	if(p != NULL)
		::GlobalFree(p);
}

//----------------------------CThreadLocalObject ��--------------------------------//

CNoTrackObject* CThreadLocalObject::GetData(CNoTrackObject* (*pfnCreateObject)())
{
	if(m_nSlot == 0)
	{
		if(_afxThreadData == NULL)
			_afxThreadData = new(__afxThreadData) CThreadSlotData;
		m_nSlot = _afxThreadData->AllocSlot();
	}
 
	CNoTrackObject* pValue = (CNoTrackObject*)_afxThreadData->GetThreadValue(m_nSlot);
	if(pValue == NULL)
	{
		// ����һ��������
		pValue = (*pfnCreateObject)();

		// ʹ���߳�˽�����ݱ����´����Ķ���
		_afxThreadData->SetValue(m_nSlot, pValue);	
	}
	
	return pValue;
}

CNoTrackObject* CThreadLocalObject::GetDataNA()
{
	if(m_nSlot == 0 || _afxThreadData == 0)
		return NULL;
	return (CNoTrackObject*)_afxThreadData->GetThreadValue(m_nSlot);
}

CThreadLocalObject::~CThreadLocalObject()
{
	if(m_nSlot != 0 && _afxThreadData != NULL)
		_afxThreadData->FreeSlot(m_nSlot);
	m_nSlot = 0;
}

//------------------------------------------