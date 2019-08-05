#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;

	}
	~MyString() { if (p) delete[] p; }

	// 在此处补充你的代码
	MyString(const MyString& str)
	{
		if (str.p)
		{
			p = new char[strlen(str.p) + 1];
			strcpy(p, str.p);
		}
		else	p = NULL;

	}
	int Copy(char *s)
	{
		int len = strlen(s);
		if (p != NULL && strlen(p) >= len)
		{
			strcpy(p, s);
		}
		else
		{
			delete[] p;
			p = new char[len + 1];
			strcpy(p, s);
		}
	}

	friend ostream& operator<<(ostream& os, MyString str)
	{
		os << str.p;
		return os;
	}

	MyString& operator=(MyString str)
	{
		int len = strlen(str.p);
		if (p && strlen(p) >= len)
		{
			strcpy(p, str.p);
		}
		else
		{
			delete[] p;
			p = new char[len + 1];
			strcpy(p, str.p);
		}
	}

	MyString& operator=(char *s)
	{
		int len = strlen(s);
		if (p && strlen(p) >= len)
		{
			strcpy(p, s);
		}
		else
		{
			delete[] p;
			p = new char[len + 1];
			strcpy(p, s);
		}
	}
};
int main()
{
	char w1[200], w2[100];
	while (cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
	return 0;
}