#include <iostream> 
using namespace std;
class Point {
private:
	int x;
	int y;
public:
	Point() { };

	// �ڴ˴�������Ĵ���
	friend istream& operator>>(istream& is, Point& pt)
	{
		is >> pt.x >> pt.y;
		return is;
	}

	friend ostream& operator<<(ostream& os, Point pt)
	{
		os << pt.x << "," << pt.y;
		return os;
	}
};

int main()
{
	Point p;
	while (cin >> p) {
		cout << p << endl;
	}
	return 0;
}