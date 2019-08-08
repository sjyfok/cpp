#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s)
{
	int i = 0;
	for (; s[i]; ++i);
	return i;
}
void strcpy(char * d, const char * s)
{
	int i = 0;
	for (i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;

}
int strcmp(const char * s1, const char * s2)
{
	for (int i = 0; s1[i] && s2[i]; ++i) {
		if (s1[i] < s2[i])
			return -1;
		else if (s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d, const char * s)
{
	int len = strlen(d);
	strcpy(d + len, s);
}
class MyString
{

	// 在此处补充你的代码
private:
	char *sbuf;
public:
	MyString(char *s)
	{
		if (s)
		{
			int len = strlen(s);
			sbuf = new char[len + 1];
			strcpy(sbuf, s);
		}
		else
		{
			sbuf = NULL;
		}
	}
	MyString()
	{
		sbuf = NULL;
	}
	MyString(const MyString &str)
	{
		if (str.sbuf)
		{
			int len = strlen(str.sbuf);
			sbuf = new char[len + 1];
			strcpy(sbuf, str.sbuf);
		}
		else
		{
			sbuf = NULL;
		}
	}

	~MyString()
	{
		if (sbuf)
		{
			delete[] sbuf;
		}
		sbuf = NULL;
	}

	friend ostream & operator<<(ostream &os, MyString str)
	{
		if (str.sbuf)
		{
			os << str.sbuf;
		}
		
		return os;
	}

	MyString & operator=(const MyString str)
	{
		if (str.sbuf)
		{
			int len = strlen(str.sbuf);
			sbuf = new char[len + 1];
			strcpy(sbuf, str.sbuf);
		}
		else
		{
			sbuf = NULL;
		}
		return *this;
	}
	friend MyString operator+(const MyString str1, const MyString str2)
	{
		MyString rStr;
		int len = strlen(str1.sbuf) + strlen(str2.sbuf);
		if (len)
		{
			rStr.sbuf = new char[len + 1];
			strcpy(rStr.sbuf, str1.sbuf);
			strcat(rStr.sbuf, str2.sbuf);
		}
		else
		{
			rStr.sbuf = NULL;
		}

		return rStr;
	}

	char& operator[](int idx)
	{
		return sbuf[idx];
	}

	MyString &operator+=(char *s)
	{
		if (s)
		{
			int len = strlen(s) + strlen(sbuf);
			char *buf = new char[len + 1];
			strcpy(buf, sbuf);
			strcat(buf, s);
			delete[] sbuf;
			sbuf = buf;
		}
		return *this;
	}

	bool operator<(const MyString &str)
	{
		return (strcmp(sbuf, str.sbuf) < 0);
	}

	bool operator==(const MyString &str)
	{
		return (strcmp(sbuf, str.sbuf) == 0);
	}

	bool operator>(const MyString &str)
	{
		return strcmp(sbuf, str.sbuf) > 0;
	}

	MyString operator()(int start, int len)
	{
		MyString tmp;
		int i;
		tmp.sbuf = new char[len + 1];
		while (i < len)
		{
			tmp.sbuf[i] = sbuf[start + i];
			i++;
		}
		tmp.sbuf[i] = 0;
		return tmp;
	}
};


int CompareString(const void * e1, const void * e2)
{
	MyString * s1 = (MyString *)e1;
	MyString * s2 = (MyString *)e2;
	if (*s1 < *s2)
		return -1;
	else if (*s1 == *s2)
		return 0;
	else if (*s1 > *s2)
		return 1;
}

int main()
{
	MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
	MyString SArray[4] = { "big","me","about","take" };
	cout << "1. " << s1 << s2 << s3 << s4 << endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A';
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray, 4, sizeof(MyString), CompareString);
	for (int i = 0; i < 4; i++)
		cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0, 4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5, 10) << endl;
	cout.flush();
	return 0;
}