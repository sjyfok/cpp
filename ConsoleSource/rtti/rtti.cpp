#include <iostream>
#include "rtti.h"

using namespace std;

const	int CGirl::classCGirl = 1;

int main(void)
{
	CBoy student;
	if (student.GetRunTimeClass() == &CGirl::classCGirl)
		cout << "a girl\n";
	else if (student.GetRunTimeClass() == &CBoy::classCBoy)
			cout << "a boy\n";
	else
		cout << "nuknown\n";
	system("pause");
	return 0;
}
