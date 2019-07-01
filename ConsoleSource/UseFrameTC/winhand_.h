#pragma once
#include "_afxcoll.h"

class CCObject;
class CHandleMap
{
private:
	CMapPtrToPtr m_permanentMap;
public:
	CCObject *LookupPermanent(HANDLE h);
	void SetPermanent(HANDLE h, CCObject *permOb);
	void RemoveHandle(HANDLE h);
	CCObject *FromHandle(HANDLE h);
};

inline CCObject* CHandleMap::LookupPermanent(HANDLE h)
{
	return (CCObject*)m_permanentMap[h];
}

inline void CHandleMap::SetPermanent(HANDLE h, CCObject *permOb)
{
	m_permanentMap[h] = permOb;
}

inline void CHandleMap::RemoveHandle(HANDLE h)
{
	m_permanentMap.RemoveKey(h);
}

inline CCObject* CHandleMap::FromHandle(HANDLE h)
{
	return LookupPermanent(h);
}