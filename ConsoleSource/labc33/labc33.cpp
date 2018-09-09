#include <iostream>
using namespace std;

bool uglynum(int num);
int main(void)
{
	int num;
	cin >> num;
	if (uglynum(num))
		cout << "True" << endl;
	else
		cout << "False" << endl;
	return 0;
}

bool uglynum(int num)
{
	if (num % 2 == 0)
	{
		num /= 2;
		if (num == 1)
			return true;
		else 
			return uglynum(num);
	}
	else if (num % 3 == 0)
	{
		num /= 3;
		if (num == 1)
			return true;
		else return uglynum(num);
	}
	else if (num % 5 == 0)
	{
		num /= 5;
		if (num == 1)
			return true;
		else return uglynum(num);

	}
	return false;
}