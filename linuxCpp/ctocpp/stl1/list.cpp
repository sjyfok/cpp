#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
int main()
{
	list<int> lst[10000];
	int nCmd, id1, id2, num;
	string cmd;
	char szcmd[20];
	cin >> nCmd;

	for (int i = 0; i < nCmd; i++)
	{
		scanf("%s", szcmd);
		cmd = szcmd;
		if (cmd.compare("new") == 0)
		{
			scanf("%d", &id1);
		}
		else if (cmd.compare("add") == 0)
		{
			scanf("%d %d", &id1, &num);
			lst[id1].push_back(num);
		}
		else if (cmd.compare("merge") == 0)
		{
			scanf("%d %d", &id1, &id2);
			lst[id1].merge(lst[id2]);
		}
		else if (cmd.compare("unique") == 0)
		{
			scanf("%d", &id1);
			lst[id1].sort();
			lst[id1].unique();
		}
		else if (cmd.compare("out") == 0)
		{
			scanf("%d", &id1);
			lst[id1].sort();
			for (list<int>::iterator i = lst[id1].begin(); i != lst[id1].end(); ++i)
				cout << *i << " ";
			cout << endl;
		}
		
	}

	return 0;
}