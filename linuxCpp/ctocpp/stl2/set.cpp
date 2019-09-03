#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
int main()
{
	multiset<int> mset;
	set<int>rset;
	int nCmd, num;
	string cmd;
	char szcmd[20];
	cin >> nCmd;

	for (int i = 0; i < nCmd; i++)
	{
		scanf("%s", szcmd);
		cmd = szcmd;
		if (cmd.compare("add") == 0)
		{
			scanf("%d", &num);
			mset.insert(num);
			rset.insert(num);
			cout << mset.count(num) << endl;
		}
		else if (cmd.compare("ask") == 0)
		{
			scanf("%d", &num);
			set<int>::iterator p = rset.find(num);
			if (p != rset.end())
				cout << "1 ";
			else
				cout << "0 ";
			cout << mset.count(num) << endl;
		}
		else if (cmd.compare("del") == 0)
		{
			scanf("%d", &num);
			cout << mset.count(num) << endl;
			mset.erase(num);		
		}	
		
	}

	return 0;
}