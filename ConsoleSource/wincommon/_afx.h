#ifndef __AFX_H__
#define __AFX_H__

#include <Windows.h>

class CObject;

struct CRuntimeClass
{
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;
	CObject *(__stdcall *m_pfnCreateObject)();
	CRuntimeClass *m_pBaseClass;
	CObject *CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass *pBaseClass) const;
	CRuntimeClass * m_pNextClass;
};

class CObject
{
public:
	virtual CRuntimeClass *GetRuntimeClass() const;
	virtual ~CObject();
public:
	BOOL IsKindOf(const CRuntimeClass *pClass) const;
public:
	static const CRuntimeClass classCObject;
};

inline CObject::~CObject() {}

#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)&class_name::class##class_name)
#endif // !__AFX_H__
