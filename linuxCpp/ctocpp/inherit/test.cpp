#include <iostream>

#include <string.h>

using namespace std;


class baseA
{
public:

};

class baseB;
class B;
class A : public baseA
{
public:
	A()
	{
		pB = 0;
		memset(name, 0, sizeof(name));
		strcpy(name, "A");
		pB = new B;
	}
	B * pB;
	char name[10];
};

class baseB
{
public:

};

class B
{
public:
	B()
	{
		pA = 0;
		memset(name, 0, sizeof(name));
		strcpy(name, "B");
		pA = new A;
	}
	A * pA;
	char name[10];
};

int main()
{
	A a;
	B b;

	cout << b.name << a.name << endl;
	cout << b.pA->name << a.pB->name << endl;
}