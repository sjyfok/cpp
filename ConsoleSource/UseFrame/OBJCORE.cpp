#include "_afx.h"



CRuntimeClass *CObject::GetRuntimeClass() const
{
	return RUNTIME_CLASS(CObject);
}

const struct CRuntimeClass CObject::classCObject =
{ "CObject", sizeof(CObject), 0xffff, NULL, NULL, NULL };

BOOL CObject::IsKindOf(const CRuntimeClass *pClass) const
{
	CRuntimeClass *pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}


//////////////////////////////////////////////////////////////////////
//RuntimeClass


CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
	{
		return NULL;
	}
	return (*m_pfnCreateObject)();
}

BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass *pBaseClass) const
{
	const CRuntimeClass * pClassThis = this;
	while (pClassThis != NULL)
	{
		if (pClassThis == pBaseClass)
		{
			return TRUE;
		}
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}