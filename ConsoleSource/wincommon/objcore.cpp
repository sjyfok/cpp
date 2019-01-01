#include "_afx.h"

const struct CRuntimeClass CObject::classCObject = 
{
	"CObject", sizeof(CObject), 0xffff, NULL, NULL, NULL
}

CRuntimeClass *CObject::GetRuntimeClass const
{
	return RUNTIME_CLASS(CObject);
}

BOOL CObject::IsKindOf(const CRuntimeClass *pClass) const
{
	return RUNTIME_CLASS(CObject);
}

BOOL CObject::IsKindOf(const CRuntimeClass *pClass) const
{
	CRuntimeClass *pClassThis = GetRuntimeClass();
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
