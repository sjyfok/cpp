#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
int main()
{
	double a[] = { 1.2,3.4,9.8,7.3,2.6 };
	list<double> lst(a, a + 5);
	lst.sort(

		// �ڴ˴�������Ĵ���
		greater<double>()
	);

	for (list<double>::iterator i = lst.begin(); i != lst.end(); ++i)
		cout << *i << ",";
	cout.flush();
	return 0;
}