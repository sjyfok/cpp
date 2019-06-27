#include <iostream>
#include <process.h>
#include   "_afx.h"

using namespace std;

class CPerson :public CObject
{
public:	

	//代替下面两个定义
	
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
	
	//::OutputDebugString("在调试器窗口， 你看到我了吗?\n");
	AfxTrace("%s", "在调试器窗口， 你看到我了吗?\n");
	//ASSERT(0);
	system("pause");
	return 0;
}

