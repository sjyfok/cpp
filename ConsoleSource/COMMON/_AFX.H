///////////////////////////////////////////
// _AFX.H�ļ�


#ifndef __AFX_H__
#define __AFX_H__

#include <windows.h>


///////////////////////////////////////////////////
// ����֧��
#define AfxDebugBreak()   //_asm { int 3 }
#ifdef _DEBUG

void __cdecl AfxTrace(LPCTSTR lpszFormat, ...);
#define TRACE              ::AfxTrace
#define ASSERT(f) \
	if (!(f)) \
		AfxDebugBreak();
#define VERIFY(f)          ASSERT(f)

#else // _DEBUG

#define ASSERT(f)          ((void)0)   
#define VERIFY(f)          ((void)(f))
inline void __cdecl AfxTrace(LPCTSTR, ...) { }
#define TRACE              (void)0

#endif // _DEBUG

/////////////////////////////////////////////////////
// ����������Ϣ
class CObject;
struct CRuntimeClass
{
// ���ԣ�Attributes��
	LPCSTR m_lpszClassName;	// �������
	int m_nObjectSize;	// ��Ĵ�С
	UINT m_wSchema;		// ��İ汾��
	CObject* (__stdcall* m_pfnCreateObject)();	// ������ĺ�����ָ��
	CRuntimeClass* m_pBaseClass;			// �������CRuntimeClass�ṹ�ĵ�ַ

// ������operations��
	CObject* CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;

// �ڲ�ʵ�֣�Implementation��
	CRuntimeClass* m_pNextClass;  // ������CRuntimeClass�����ü���������һ��
};

//////////////////////////////////////////////////////
// CObject ��
class CObject
{
public:
	virtual CRuntimeClass* GetRuntimeClass() const;
	virtual ~CObject();

// ���ԣ�Attibutes��
public:
	BOOL IsKindOf(const CRuntimeClass* pClass) const;

// ʵ�֣�implementation��
public:
	static const CRuntimeClass classCObject; //   ��ʶ��ľ�̬��Ա
};
inline CObject::~CObject() { }

// �궨��

// RUNTIME_CLASS������ȡ��class_name����CRuntimeClass�ṹ�ĵ�ַ
#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)&class_name::class##class_name)

// ֧�ֶ�̬����ʶ��ĺ�

#define DECLARE_DYNAMIC(class_name) \
public: \
	static const CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; 

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); } \

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

// ֧�ֶ�̬�����ĺ�

#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* __stdcall CreateObject();

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* __stdcall class_name::CreateObject() \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)


#endif // __AFX_H__