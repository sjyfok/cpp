#include <cstdio>
#include <iostream>
#include <map>
#include <set>

using namespace std;


typedef multimap<int, set<int>> MAP_MEMBER;

int main()
{
	MAP_MEMBER map_member;	
	set<int> setid;

	int nCount, id, force, diff;
	MAP_MEMBER::iterator hit_p, rec_p;
	setid.insert(1);
	map_member.insert(make_pair(1000000000, setid));
	cin >> nCount;



	for (int i = 0; i < nCount; i++)
	{
		cin >> id >> force;
		MAP_MEMBER::iterator p = map_member.find(force);
		if (p == map_member.end())
		{
			set<int> sid;
			sid.insert(id);
			map_member.insert(make_pair(force, sid));
		}
		else
		{
			p->second.insert(id);
		}
		rec_p = map_member.lower_bound(force);
		p = rec_p;
		if (p != map_member.begin())
		{
			p--;
			diff = abs(p->first - force);
			hit_p = p;
			p = rec_p;
			p++;
			if (diff > abs(p->first-force))
			{
				hit_p = p;
			}
			else if (diff == abs(p->first - force))
			{
				if (true)
				{

				}
			}
		}
		else
		{
			p++;
			hit_p = p;
		}
		cout << id << " " << *hit_p->second.begin() << endl;
		/*map_member.insert(make_pair(force, id));
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


		cout << id << " " << hit_p->second << endl;		*/
	}

	return 0;
}