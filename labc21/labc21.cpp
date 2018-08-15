#include <iostream>
using namespace std;

int main(void)
{
	int n;
	int buf[100];
	int sum, mine, maxe;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> buf[i];
	}
	sum = mine = maxe = buf[0];
	for (int i = 1; i < n; i++)
	{
		if (buf[i] < mine)
			mine = buf[i];
		if (buf[i] > maxe)
			maxe = buf[i];
		sum += buf[i];
	}
	cout << sum << ' ' << mine << ' ' << maxe << endl;
	return 0;
}