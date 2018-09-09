#include <iostream>
using namespace std;


class Integer {
private:
	int _num;
	int getLength();
public:
	Integer(int num);
	int inversed();
};

Integer::Integer(int num) :_num(num)
{}

int Integer::getLength()
{
	if (_num == 1000000000)
		return 10;
	else if (_num >= 100000000)
		return 9;
	else if (_num >= 10000000)
		return 8;
	else if (_num >= 1000000)
		return 7;
	else if (_num >= 100000)
		return 6;
	else if (_num >= 10000)
		return 5;
	else if (_num >= 1000)
		return 4;
	else if (_num >= 100)
		return 3;
	else if (_num >= 10)
		return 2;
	else if (_num >= 1)
		return 1;
	return 0;
}

int Integer::inversed()
{
	int len = getLength();
	int num = _num;
	int rem, rsl, temp;
	
	rsl = 0;
	for (int i = 0; i < len; i++)
	{
		rem = num % 10;
		num /= 10;
		if (rem)
		{		
			temp = 1;
			for (int j = 0; j < len - i - 1; j++)
				temp *= 10;
			rsl += temp;
		}
	}
	return rsl;
}

 
int main() {
	int n;
	cin >> n;
	Integer integer(n);
	cout << integer.inversed() << endl;
	return 0;
}