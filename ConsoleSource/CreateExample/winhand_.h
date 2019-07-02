#pragma once
#include "_afxcoll.h"

class CObject;
class CHandleMap
{
private:
	CMapPtrToPtr m_permanentMap;
public:
	CObject *LookupPermanent(HANDLE h);
	void SetPermanent(HANDLE h, CObject *permOb);
	void RemoveHandle(HANDLE h);
	CObject *FromHandle(HANDLE h);
};

inline CObject* CHandleMap::LookupPermanent(HANDLE h)
{
	return (CObject*)m_permanentMap[h];
}

inline void CHandleMap::SetPermanent(HANDLE h, CObject *permOb)
{
	m_permanentMap[h] = permOb;
}

inline void CHandleMap::RemoveHandle(HANDLE h)
{
	m_permanentMap.RemoveKey(h);
}

inline CObject* CHandleMap::FromHandle(HANDLE h)
{
	return LookupPermanent(h);
}