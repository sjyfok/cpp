#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
	double r, i;
public:
	void Print() {
		cout << r << "+" << i << "i" << endl;
	}

	// 在此处补充你的代码
	Complex& operator=(string str)
	{
		int pos, pos2;
		string tempStr;
		pos = str.find('+');
		tempStr = str.substr(0, pos);
		r = atof(tempStr.c_str());
		pos2 = str.find('i');
		tempStr = str.substr(pos + 1, pos2);
		i = atof(tempStr.c_str());

		return *this;
	}
};
int main() {
	Complex a;
	a = "3+4i"; a.Print();
	a = "5+6i"; a.Print();
	cout.flush();
	return 0;
}