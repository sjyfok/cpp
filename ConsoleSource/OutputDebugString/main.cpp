#include <iostream>
#include <process.h>
#include   "_afx.h"

using namespace std;

class CPerson :public CObject
{
public:	

	//����������������
	
	DECLARE_DYNCREATE(CPerson)
	//static CObject* __stdcall CreateObject()
	//{
	//	return new CPerson;
	//}
	//static const CRuntimeClass classCPerson;
	//virtual CRuntimeClass *GetRuntimeClass() const
	//{
	//	return (CRuntimeClass*)&classCPerson;
	//}
};

IMPLEMENT_DYNCREATE(CPerson, CObject)
//const CRuntimeClass CPerson::classCPerson =
//{
//	"CPerson", sizeof(CPerson), 0xFFFF, &CPerson::CreateObject, (CRuntimeClass*)&CObject::classCObject, NULL
//};
//virtual CRuntimeClass *GetRuntimeClass() const
//{
//	return (CRuntimeClass*)&classCPerson;
//}



int main(void)
{
	
	//::OutputDebugString("�ڵ��������ڣ� �㿴��������?\n");
	AfxTrace("%s", "�ڵ��������ڣ� �㿴��������?\n");
	//ASSERT(0);
	system("pause");
	return 0;
}

