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
	CHugeInt(char *s)
	{
		if (s != NULL)
		{
			strcpy(sNum, s);
		}
	}
	CHugeInt(int n)
	{
		sprintf(sNum, "%d", n);
	}

	char * operator+(CHugeInt a)
	{
		int len1, len2, len;
		len1 = strlen(sNum);
		len2 = strlen(a.sNum);
		if (len1 > len2)
		{
			len = len2;
		}
		else
		{
			len = len1;
		}
		for (int i = 0; i < len; i++)
		{

		}
	}
};

char *test()
{
	
	char *str = "hello";
	return str;
	
}

int  main()
{
	char s[210];
	int n;

	cout << test();

	/*while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}*/
	cout.flush();
	return 0;
}