#include <iostream>
using namespace std;
class A {
public:
	int i;
	A(int x) { i = x; }

	// �ڴ˴�������Ĵ���
	~A() { cout << i << endl; }
};
int main()
{
	A a(1);
	A * pa = new A(2);
	delete pa;
	cout.flush();
	return 0;
}