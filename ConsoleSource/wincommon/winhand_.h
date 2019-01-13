#ifndef __WINHAND_H__
#define __WINHAND_H__
#include "_afxcoll.h"
#include <Windows.h>

class CObject;
class CHandleMap
{
private:
	CMapPtrToPtr m_permanentMap;
public:
	CObject * LookupPermanent(HANDLE h);
	void SetPermanent(HANDLE h, CObject *permOb);
	void RemoveHandle(HANDLE h);
	CObject *FromHandle(HANDLE h);
};

__inline CObject *CHandleMap::LookupPermanent(HANDLE h)
{
	return (CObject *)m_permanentMap[h];
}

__inline void CHandleMap::SetPermanent(HANDLE h, CObject *permOb)
{
	m_permanentMap[h] = permOb;
}

__inline void CHandleMap::RemoveHandle(HANDLE h)
{
	m_permanentMap.RemoveKey(h);
}

__inline CObject CHandleMap::FromHandle(HANDLE h)
{
	return LookupPermanent(h);
}

}




#endif // !__WINHAND_H__
