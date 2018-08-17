#include <iostream>
using namespace std;

bool isRightangle(int a, int b, int c);

int main(void)
{
	int a, b, c;
	int i;
	
	cin >> a >> b >> c;
	

	if (isRightangle(a, b, c))
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}
	
	
	return 0;
}

bool isRightangle(int a, int b, int c)
{
	if (a*a + b * b == c * c)
		return true;
	else if (a*a + c * c == b * b)
		return true;
	else if (b*b + c * c == a * a)
		return true;
	else return false;
}