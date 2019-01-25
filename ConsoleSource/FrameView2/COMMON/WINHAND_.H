////////////////////////////////////////////////
// WINHAND_.h�ļ�

#include "_afxcoll.h"	

class CObject;
class CHandleMap
{
// ʵ�֣�Implementation��
private:
	CMapPtrToPtr m_permanentMap;

// ������Operations��
public:
	CObject* LookupPermanent(HANDLE h);
	void SetPermanent(HANDLE h, CObject* permOb);
	void RemoveHandle(HANDLE h);

	CObject* FromHandle(HANDLE h);	
};

__inline CObject* CHandleMap::LookupPermanent(HANDLE h)
	{ return (CObject*)m_permanentMap[h]; }	
__inline void CHandleMap::SetPermanent(HANDLE h, CObject* permOb)
	{ m_permanentMap[h] = permOb; }
__inline void CHandleMap::RemoveHandle(HANDLE h)
	{ m_permanentMap.RemoveKey(h); }

__inline CObject* CHandleMap::FromHandle(HANDLE h)
	{ return LookupPermanent(h); }