#include <iostream>
#include   "../wincommon/_afx.h"
#include <process.h>

using namespace std;

class CPerson :public CObject
{
	DECLARE_DYNCREATE(CPerson)
};

IMPLEMENT_DYNCREATE(CPerson, CObject)



int main(void)
{
	CRuntimeClass *pRuntimeclass = RUNTIME_CLASS(CPerson);
	CObject *pObject = pRuntimeclass->CreateObject();
	ASSERT(pObject);
	if (pObject != NULL && pObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		cout << "创建成功!\n";
		delete pObject;
	}
	/*if (pMyObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		CPerson *pMyPerson = (CPerson*)pMyObject;
		cout << "a CPerson Object!\n";
		delete pMyPerson;
	}
	else
	{
		delete pMyObject;
	}*/

	system("pause");
	return 0;
}

