#include <cstdio>
#include <iostream>
#include <map>
using namespace std;


typedef multimap<int, int> MAP_MEMBER;

int main()
{
	MAP_MEMBER map_member;	
	int nCount, id, force, diff;
	MAP_MEMBER::iterator hit_p, rec_p;

	map_member.insert(make_pair(1000000000, 1));
	cin >> nCount;



	for (int i = 0; i < nCount; i++)
	{
		
		cin >> id >> force;
		map_member.insert(make_pair(force, id));
		rec_p = map_member.lower_bound(force);
		MAP_MEMBER::iterator p = rec_p;
		if (p != map_member.begin())
		{
			p--;
			diff = abs(p->first - force);
			hit_p = p;
			while (p != map_member.begin())
			{
				p--;
				if (diff == abs(p->first - force))
				{
					if (p->second < hit_p->second)
					{
						hit_p = p;
					}
				}
				else
					break;
			}
			p = rec_p;
			while (p != map_member.end())
			{
				p++;
				if (diff > abs(p->first-force))
				{
					hit_p = p;
				}
				else if (diff == abs(p->first-force))
				{
					if (p->second < hit_p->second)
					{
						hit_p = p;
					}
				}
				else
				{
					break;
				}
			}
			
		}
		else
		{
			p++;
			diff = abs(p->first - force);
			hit_p = p;
			while (p != map_member.end())
			{
				p++;
				if (diff == abs(p->first - force))
				{
					if (p->second < hit_p->second)
					{
						hit_p = p;
					}
				}
				else
					break;
			}
		}


		cout << id << " " << hit_p->second << endl;		
	}

	return 0;
}