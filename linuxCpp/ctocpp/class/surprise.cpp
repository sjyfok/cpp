#include <iostream>
using namespace std;
class Sample {
public:
	int v;

	// 在此处补充你的代码
	Sample(int iv)
	{
		v = iv;
	}
	Sample(const Sample &s)
	{
		this->v = s.v+2;
	}
	Sample() {}
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	cout.flush();
	return 0;
}