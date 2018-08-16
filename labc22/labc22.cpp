#include <iostream>
#include <string.h>
using namespace std;
#define	 C_BUFSIZE	(11)

int pow2(int exp);

int main(void)
{
	char binBuf[C_BUFSIZE];
	int rsl, tmp;

	cin >> binBuf;

//	cout << binBuf << endl;

	int len = strlen(binBuf);
	rsl = 0;
	for (int i = 0; i < len; i++)
	{
		tmp = binBuf[i]-0x30;
		if (tmp)
			tmp = pow2(len - i-1);
		rsl += tmp;
	}
	cout << rsl;
	return 0;
}

//计算2的exp次方
int pow2(int exp)
{
	int rsl = 1;
	for (int i = 0; i < exp;  i++)
	{
		rsl *= 2;
	}
	return rsl;
}