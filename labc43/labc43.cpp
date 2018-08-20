#include <iostream>
#include<cmath>
#include <cstdio>
using namespace std;
class Equation {
private:
	int _a, _b, _c;
public:
	Equation(int a, int b, int c) {
		_a = a;
		_b = b;
		_c = c;
	}
	void solve();
};

void Equation::solve() {
	if (_a == 0) {
		if (_b == 0)
		{
			if (_c == 0) cout << "5" << endl;
			else cout << "4" << endl;
		}
		else {
			cout << "6" << endl;
			printf("%.2f\n", (float)-_c / _b);
		}
	}
	else {
		int theta;
		theta = _b * _b - 4 * _a*_c;
		if (theta >= 0) {
			if (theta > 0) {
				cout << "1" << endl;
				printf("%.2f %.2f\n", (-_b - sqrt(theta)) / 2.0 / _a, (-_b + sqrt(theta)) / 2.0 / _a);
			}
			else {
				cout << "2" << endl;
				printf("%.2f\n", -_b / 2.0 / _a);
			}
		}
		else cout << "3" << endl;
	}


}
int main() {
	while (1) {
		int a, b, c;
		cin >> a >> b >> c;
		Equation tmp(a, b, c);
		tmp.solve();
	}
	return 0;
}