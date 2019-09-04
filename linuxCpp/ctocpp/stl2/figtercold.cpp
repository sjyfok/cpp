#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

//��Ա��Ϣ
struct CMemberInfo
{
	int id;
	int jointime;

	CMemberInfo(int i, int t) :id(i), jointime(t)
	{}
	CMemberInfo()
	{}
};

class CMember
{
public:
	int m_force;
	CMemberInfo m_info;
	CMember(int f, int i, int t) :m_force(f), m_info(i, t)
	{}
	CMember()
	{}
};

typedef multimap<int, CMemberInfo> MAP_MEMBER;

int main()
{
	MAP_MEMBER map_member;
	int iTime = 0;  //
	int nCount;
	CMember firstm(1000000000, 1, iTime++);

	map_member.insert(make_pair(firstm.m_force, firstm.m_info));
	cin >> nCount;

	for (int i = 0; i < nCount; i++)
	{
		CMember member;
		int diffforce;
		MAP_MEMBER::iterator tp, hit_p;
		cin >> member.m_info.id >> member.m_force;
		member.m_info.jointime = iTime++;
		map_member.insert(make_pair(member.m_force, member.m_info));
		MAP_MEMBER::iterator p = map_member.lower_bound(member.m_force);
		if (p != map_member.begin())
		{
			//��ʵ��������
			tp = p;
			p--;
			diffforce = abs(p->first - member.m_force);
			hit_p = p;
			//�鿴ʵ���������� �ҳ������ͬ�ļ�¼��id��С��
			while (p != map_member.begin())
			{
				p--;
				if (diffforce == abs(p->first-member.m_force))					
				{
					if (p->second.id < hit_p->second.id)
						hit_p = p;
				}
				else
				{
					break;
				}
			}
			//ʵ��ǿ������
			p = tp;
			p++;
			if (diffforce >= abs(p->first-member.m_force))
			{
				if (diffforce == abs(p->first - member.m_force))
				{
					if (p->second.id < hit_p->second.id)
						hit_p = p;

					while (p != map_member.end())
					{
						p++;
						if (diffforce == abs(p->first - member.m_force))
						{
							if (p->second.id < hit_p->second.id)
								hit_p = p;
						}
						else
						{
							break;
						}
					}

					cout << member.m_info.id << " " << hit_p->second.id << endl;
				}
				else
				{
					diffforce = abs(p->first - member.m_force);
					hit_p = p;
					while (p != map_member.end())
					{
						p++;
						if (diffforce == abs(p->first - member.m_force))
						{
							if (p->second.id < hit_p->second.id)
								hit_p = p;
						}
						else
						{
							break;
						}
					}

					cout << member.m_info.id << " " << hit_p->second.id << endl;
				}
			}
			else
			{
				cout << member.m_info.id << " " << hit_p->second.id << endl;
			}
		}
		else
		{
			p++;
			diffforce = abs(p->first - member.m_force);
			hit_p = p;
			//ֻ����ʵ��ǿ��
			while (p != map_member.end())
			{
				p++;
				if (diffforce == abs(p->first - member.m_force))
				{
					if (p->second.id < hit_p->second.id)
						hit_p = p;
				}
				else
				{
					break;
				}
			}

			cout << member.m_info.id << " " << hit_p->second.id << endl;
		}		
	}

	return 0;
}