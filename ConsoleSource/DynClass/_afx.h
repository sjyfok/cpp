#pragma once
#include <Windows.h>

//静态变量声明
#define	DECLARE_DYNAMIC(class_name) \
public:\
	static const CRuntimeClass class##class_name;\
	virtual CRuntimeClass *GetRuntimeClass() const;
//静态变量实现
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
		RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
	{return RUNTIME_CLASS(class_name);}
#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)  //不支持动态创建 因为动态创建函数是NULL


//const CRuntimeClass CPerson::classCPerson =
//{
//	"CPerson", sizeof(CPerson), 0xFFFF, &CPerson::CreateObject, (CRuntimeClass*)&CObject::classCObject, NULL
//};

//CRuntimeClass *CObject::GetRuntimeClass() const
//{
//	return RUNTIME_CLASS(CObject);
//}


class CObject;
struct CRuntimeClass
{
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;
	CObject *(__stdcall* m_pfnCreateObject)();
	CRuntimeClass* m_pBaseClass;
	CObject *CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass *pBaseClass)const;
	CRuntimeClass *m_pNextClass;
};

class CObject
{
public:
	
	virtual	~CObject();

public:
	BOOL IsKindOf(const CRuntimeClass *pClass) const;
public:
	//静态成员变量	
	virtual CRuntimeClass *GetRuntimeClass()const;
	static const CRuntimeClass classCObject;
};

inline CObject::~CObject()
{
}

#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)&class_name::class##class_name)
