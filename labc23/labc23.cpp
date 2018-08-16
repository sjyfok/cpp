#include <iostream>
#include <iomanip>
using namespace std;


int main(void)
{
	int n, i, j, L;
	int gap;
	cin >> n;

//	cout << binBuf << endl;
	L = 1;
	for (i = 0; i < n; i++)
	{
		gap = n - i;

		cout << std::setw(gap);

		for (j = 0; j < L; j++)
		{
			cout << '*';
		}
		
		cout << endl;
		L += 2;
	}
	L -= 2;
	for (i = 0; i < n - 1; i++)
	{
		gap =  i+2;
		cout << std::setw(gap);
		L -= 2;
		for (j = 0; j < L; j++)
		{
			cout << '*';
		}
		cout << endl;
	}
	return 0;
}

