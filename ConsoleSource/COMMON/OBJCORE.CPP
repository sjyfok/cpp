///////////////////////////////////////////////////////
// OBJCORE.CPP�ļ�


#include "_afx.h"



CObject* CRuntimeClass::CreateObject()
{
	if(m_pfnCreateObject == NULL)
		return NULL;
	return (*m_pfnCreateObject)(); // ���ô�����ĺ���
}

BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass* pBaseClass) const
{
	const CRuntimeClass* pClassThis = this;
	while(pClassThis != NULL)
	{
		if(pClassThis == pBaseClass) // �жϱ�ʶ���CRuntimeClass���׵�ַ�Ƿ���ͬ
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE; // ���ҵ��˼̳нṹ�Ķ��㣬û��һ��ƥ��
}

const struct CRuntimeClass CObject::classCObject = 
	{ "CObject"/*����*/, sizeof(CObject)/*��С*/, 0xffff/*�ް汾��*/, 
					NULL/*��֧�ֶ�̬����*/, NULL/*û�л���*/, NULL};

CRuntimeClass* CObject::GetRuntimeClass() const
{
	// ��������չ������ǡ�return ((CRuntimeClass*)&(CObject::classCObject));��
	return RUNTIME_CLASS(CObject);
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	CRuntimeClass* pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}