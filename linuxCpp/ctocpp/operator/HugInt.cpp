#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110;
class CHugeInt {

	// 在此处补充你的代码
private:
	char sNum[220];
public:
	void Rev()
	{
		int len = strlen(sNum);
		int i = 0, j = len-1;
		while (i < j)
		{
			char tch = sNum[i];
			sNum[i] = sNum[j];
			sNum[j] = tch;
			i++;
			j--;
		}	
	}

	CHugeInt(char *s)
	{
		memset(sNum, 0, sizeof(sNum));
		if (s != NULL)
		{
			strcpy(sNum, s);
		}
		Rev();
	}
	CHugeInt(int n)
	{
		memset(sNum, 0, sizeof(sNum));
		sprintf(sNum, "%d", n);
		Rev();
	}

	CHugeInt operator+(int a)
	{
		return *this + CHugeInt(a);
	}

	CHugeInt operator+(const CHugeInt &a)
	{
		CHugeInt tmp(0);
		int carry = 0;
		int len1, len2, len, i;
		len1 = strlen(sNum);
		len2 = strlen(a.sNum);
		if (len1 > len2)
			len = len1;
		else len = len2;
		i = 0;
		while (i < len)
		{
			int k = sNum[i] - 0x30 + a.sNum[i] - 0x30 + carry;
			if (k >= 10)
			{
				carry = 1;
				tmp.sNum[i] = k - 10 + 0x30;
			}
			else
			{
				carry = 0;
				tmp.sNum[i] = k + 0x30;
			}
			i++;			
		}
		if (carry)
		{
			tmp.sNum[i] = carry + 0x30;
		}
		tmp.Rev();
		return tmp;
	}

	friend CHugeInt operator+(int n, const CHugeInt & a)
	{
		
	}

	friend ostream& operator<<(ostream &os, const CHugeInt &a)
	{
		int len = strlen(a.sNum);
		for (int i = 0; i < len; i++)
		{
			os << a.sNum[i];
		}
		return os;
	}

	CHugeInt& operator+=(int n)
	{

		return *this;
	}

	CHugeInt& operator++()
	{
		return *this;
	}

	CHugeInt  operator++(int)
	{
		
	}	
};


int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}