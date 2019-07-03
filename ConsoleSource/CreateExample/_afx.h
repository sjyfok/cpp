#pragma once
#include <Windows.h>

#define AfxDebugBreak() __debugbreak()
#ifdef _DEBUG
void __cdecl AfxTrace(LPCTSTR lpszFormat, ...);
#define TRACE ::AfxTrace
#define ASSERT(f) \
	if (!(f))\
		AfxDebugBreak();
#define	VERIFY(f) ASSERT(f)
#else
inline void __cdecl AfxTrace(LPCTSTR, ...) {}
#define	ASSERT(f) ((void)0)
#define	VERIFY(f)((void)(f))
#define TRACE		(void)0
#endif // _DEBUG



//��̬��������
#define	DECLARE_DYNAMIC(class_name) \
public:\
	static const CRuntimeClass class##class_name;\
	virtual CRuntimeClass *GetRuntimeClass() const;
//��̬����ʵ��
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
		RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
	{return RUNTIME_CLASS(class_name);}
#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)  //��֧�ֶ�̬���� ��Ϊ��̬����������NULL

//const CRuntimeClass CPerson::classCPerson =
//{
//	"CPerson", sizeof(CPerson), 0xFFFF, &CPerson::CreateObject, (CRuntimeClass*)&CObject::classCObject, NULL
//};

//CRuntimeClass *CObject::GetRuntimeClass() const
//{
//	return RUNTIME_CLASS(CObject);
//}

//��̬���ʹ���  ����  //��ԭ���Ļ���������һ����̬����
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject *__stdcall CreateObject();
#define IMPLEMENT_DYNCREATE(class_name, base_class_name)  \
	CObject *__stdcall class_name::CreateObject() \
		{return new class_name;} \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, class_name::CreateObject)

//static CObject* __stdcall CreateObject()
//{
//	return new CPerson;
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
	//��̬��Ա����	
	virtual CRuntimeClass *GetRuntimeClass()const;
	static const CRuntimeClass classCObject;
};

inline CObject::~CObject()
{
}

#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)&class_name::class##class_name)
