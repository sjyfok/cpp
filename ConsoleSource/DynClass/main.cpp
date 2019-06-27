#include <iostream>
#include <process.h>
#include   "_afx.h"

using namespace std;

class CPerson :public CObject
{
public:	

	//代替下面两个定义
	DECLARE_DYNAMIC(CPerson)
	//static const CRuntimeClass classCPerson;
	//virtual CRuntimeClass *GetRuntimeClass() const
	//{
	//	return (CRuntimeClass*)&classCPerson;
	//}
};

IMPLEMENT_DYNAMIC(CPerson, CObject)
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
	CObject *pMyObject = new CPerson;
	if (pMyObject != NULL && pMyObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		cout << "显示创建" << endl;
	}
	delete pMyObject;
	//CRuntimeClass *pRuntimeclass = RUNTIME_CLASS(CPerson);
	//CObject *pObject = pRuntimeclass->CreateObject();
	/*if (pObject != NULL && pObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		cout << "创建成功!\n";
		delete pObject;
	}*/

	


	system("pause");
	return 0;
}

