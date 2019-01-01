#include <iostream>
#include   "../wincommon/_afx.h"
#include <process.h>
class CPerson :public CObject
{
public:
	virtual CRuntimeClass *GetRuntimeClass() const
	{
		return (GetRuntimeClass*)&classCPerson;
	}
	static const CRuntimeClass classCPerson;
};


const CRuntimeClass CPerson::classCPerson =
{
	"CPerson", sizeof(CPerson), 0xFFFF, NULL, (CRuntimeClass*)&CObject::classCObject, NULL
};



int main(void)
{
	CObject *pMyObject = new CPerson;
	if (pMyObject->IsKindOf(RUNTIME_CLASS(CPerson)))
	{
		CPerson *pMyPerson = (CPerson*)pMyPerson;
		cout << "a CPerson Object!\n";
		delete pMyPerson;
	}
	else
	{
		delete pMyObject;
	}

	
	return 0;
}

