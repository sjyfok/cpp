#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <fstream>

using namespace std;


typedef multimap<int, set<int>> MAP_MEMBER;

void PrintMap(MAP_MEMBER &mp, ofstream &fout);
int main()
{
	MAP_MEMBER map_member;	
	set<int> setid;

	///////////////////////////////////
	ofstream fout("out.txt");
	ifstream fin("in.txt");
	///////////////////////////////////
	int nCount, id, force, diff;
	MAP_MEMBER::iterator hit_p, rec_p;
	setid.insert(1);
	map_member.insert(make_pair(1000000000, setid));
	//cin >> nCount;
	fin >> nCount;



	for (int i = 0; i < nCount; i++)
	{
		//cin >> id >> force;
		fin >> id >> force;
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
		PrintMap(map_member, fout);
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
				if (*p->second.begin() < *hit_p->second.begin())
				{
					hit_p = p;
				}				
			}
		}
		else
		{
			p++;
			hit_p = p;
		}
		//cout << id << " " << *hit_p->second.begin() << endl;
		fout << id << " " << *hit_p->second.begin() << endl;
	}

	return 0;
}


void PrintMap(MAP_MEMBER &mp, ofstream &fout)
{
	MAP_MEMBER::iterator p = mp.begin();

	while (p != mp.end())
	{
		//cout << "force: " << p->first << " " << "set id: ";
		fout << "force: " << p->first << " " << "set id: ";

		set<int>::iterator sp = p->second.begin();
		while (sp != p->second.end())
		{
			//cout << *sp << " ";
			fout << *sp << " ";
			sp++;
		}
		//cout << endl;
		fout << endl;
		p++;
	}
}