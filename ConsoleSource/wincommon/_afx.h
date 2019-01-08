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
#define DECLARE_DYNAMIC(class_name)\
public:\
	static const CRuntimeClass class##class_name;\
	virtual CRuntimeClass *GetRuntimeClass() const;
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew)\
	const CRuntimeClass class_name::class##class_name = {\
		#class_name, sizeof(class class_name), wSchema, pfnNew,\
			RUNTIME_CLASS(base_class_name), NULL};\
	CRuntimeClass* class_name::GetRuntimeClass() const\
		{return RUNTIME_CLASS(class_name);}
#define IMPLEMENT_DYNAMIC(class_name, base_class_name)\
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

#define DECLARE_DYNCREATE(class_name)\
	DECLARE_DYNAMIC(class_name)\
	static CObject* __stdcall CreateObject();
#define IMPLEMENT_DYNCREATE(class_name, base_class_name)\
	CObject *__stdcall class_name::CreateObject()\
		{return new class_name;}\
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF,\
			class_name::CreateObject)

#ifdef _DEBUG
#define	AfxDebugBreak() DebugBreak()//_asm{int 3}
void __cdecl AfxTrace(LPCTSTR lpszFormat, ...);
#define ASSERT(f)\
	if(!(f)) AfxDebugBreak();
#define TRACE	::AfxTrace
#define VERIFY(f) ASSERT(f)
#else
#define ASSERT(f) ((void)0)
#define VERIFY(f) ((void)(f))
inline void __cdecl AfxTrace(LPCTSTR, ...) {}
#define	TRACE	(void)0
#endif // _DEBUG

#endif // !__AFX_H__
