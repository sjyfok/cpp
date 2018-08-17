#include <iostream>
using namespace std;
class Integer {
private:
	int _num;
public:
	//构造函数
	Integer(int num);
	//计算当前Integer 和 b之间的最大公约数
	int gcd(Integer b);
};

Integer::Integer(int num) : _num(num)
{}

int Integer::gcd(Integer b)
{
	int sum, d;
	sum = this->_num+ b._num;
	for (int i = 1; i < sum; i++)
	{
		if (this->_num%i == 0 && b._num%i == 0)
			d = i;
	}
	return d;
}

int main() {
	int a, b;
	cin >> a >> b;
	Integer A(a);
	Integer B(b);
	cout << A.gcd(B) << endl;
	return 0;
}