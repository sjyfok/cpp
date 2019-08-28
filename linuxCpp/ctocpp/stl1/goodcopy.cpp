#include <iostream>
using namespace std;


template <class T>
struct GoodCopy {

	// �ڴ˴�������Ĵ���
public:
	void operator()(T *s, T *e, T *r)
	{
		T *ptr, *pi = s, *ptr_s;
		int len = e - s;
		ptr = new T[len];
		ptr_s = ptr;
		for (; pi < e; pi ++)
		{
			*ptr ++ = *pi;
		}

		pi = ptr_s;
		for (int i = 0; i < len; i ++, pi ++)
		{
			*r++ = *pi;
		}

		delete[] ptr_s;
	}	
};

int a[200];
int b[200];
string c[200];
string d[200];

template <class T>
void Print(T s, T e) {
	for (; s != e; ++s)
		cout << *s << ",";
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int m;
		cin >> m;
		for (int i = 0; i < m; ++i)
			cin >> a[i];
		GoodCopy<int>()(a, a + m, b);
		Print(b, b + m);
		GoodCopy<int>()(a, a + m, a + m / 2);
		Print(a + m / 2, a + m / 2 + m);

		for (int i = 0; i < m; ++i)
			cin >> c[i];
		GoodCopy<string>()(c, c + m, d);
		Print(c, c + m);
		GoodCopy<string>()(c, c + m, c + m / 2);
		Print(c + m / 2, c + m / 2 + m);
	}
	return 0;
}