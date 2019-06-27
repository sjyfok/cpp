#include <iostream>
#include <process.h>
#include   "_afx.h"

using namespace std;

class CPerson :public CObject
{
public:
	virtual CRuntimeClass *GetRuntimeClass() const	
	{
		return (CRuntimeClass*)&classCPerson;
	}
	
	static CObject* __stdcall CreateObject()
	{
		return new CPerson;
	}

	static const CRuntimeClass classCPerson;
};


const CRuntimeClass CPerson::classCPerson =
{
	"CPerson", sizeof(CPerson), 0xFFFF, &CPerson::CreateObject, (CRuntimeClass*)&CObject::classCObject, NULL
};



int main(void)
{
	CObject *pMyObject = new CPerson;
	//CRuntimeClass *pRuntimeclass = RUNTIME_CLASS(CPerson);
	//CObject *pObject = pRuntimeclass->CreateObject();
	//if (pObject != NULL && pObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	//{
	//	cout << "创建成功!\n";
	//	delete pObject;
	//}
	if (pMyObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		CPerson *pMyPerson = (CPerson*)pMyObject;
		cout << "a CPerson Object!\n";
		delete pMyPerson;
	}
	else
	{
		delete pMyObject;
	}

	system("pause");
	return 0;
}

