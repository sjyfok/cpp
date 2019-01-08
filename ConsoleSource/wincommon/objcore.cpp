#include "_afx.h"
#include <iostream>

using namespace std;

const struct CRuntimeClass CObject::classCObject =
{
	"CObject", sizeof(CObject), 0xffff, NULL, NULL, NULL
};

CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
		return NULL;
	return (*m_pfnCreateObject)(); // 调用创建类的函数
}

CRuntimeClass *CObject::GetRuntimeClass() const
{
	return RUNTIME_CLASS(CObject);
}


BOOL CObject::IsKindOf(const CRuntimeClass *pClass) const
{
	CRuntimeClass *pClassThis = GetRuntimeClass();
	cout << pClassThis->m_lpszClassName << endl;
	cout << pClassThis->m_nObjectSize << endl;
	return pClassThis->IsDerivedFrom(pClass);
}

BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass *pBaseClass) const
{
	const CRuntimeClass *pClassThis = this;
	while (pClassThis != NULL)
	{
		if (pClassThis == pBaseClass)
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}
