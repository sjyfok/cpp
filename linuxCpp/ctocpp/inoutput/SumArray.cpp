#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(

	// �ڴ˴�������Ĵ���
	T *beg, T *end)
{
	T *pT;

	T sum = *beg;
	pT = beg + 1;
	while (pT != end)
	{
		sum += *pT;
		pT++;
	}

	return sum;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John" };
	cout << SumArray(array, array + 4) << endl;
	int a[4] = { 1, 2, 3, 4 };  //��ʾ��1+2+3+4 = 10
	cout << SumArray(a, a + 4) << endl;
	return 0;
}