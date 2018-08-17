#include <iostream>
using namespace std;

int fbnx(int num);
int main(void)
{
	int n;
	cin >> n;
	cout << fbnx(n) << endl;
	return 0;
}

int fbnx(int num)
{
	if (num <= 1)
		return 1;
	else
	{
		return (fbnx(num - 1) + fbnx(num - 2));
	}
}