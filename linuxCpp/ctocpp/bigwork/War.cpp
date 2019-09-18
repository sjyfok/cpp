#include <iostream>
#include <iomanip>


using namespace std;

enum WarriorType
{
	DRAGON = 0,
	NINJA,
	ICEMAN,
	LION,
	WOLF,
};

enum HeadquarterType
{
	RED = 0,
	BLUE,
};

enum WeaponType
{
	SWORD = 0,
	BOMB,
	ARROW,
};

#define  WARRIOR_NUM		5
#define  WEAPON_NUM			3

class Headquarter;
class CSword;
class CBomb;
class CArrow;
///////////////////////////CWeapons//////////////////
class CWeapons
{
public:
	CWeapons() {};

	string m_Name;
};

class Warrior
{
public:
	Headquarter * m_pHeadquarter;  //所属司令部
	WarriorType type;
public:
	Warrior(WarriorType t, int l, int n)
		:type(t), live(l), num(n)
	{
		m_pHeadquarter = NULL;
		m_WCnt = 0;
	}
	virtual void Display();	
	void SetPos(int pos)
	{
		m_pos = pos;
	}
	//friend bool operator<(const Warrior w1, const Warrior w2);
	/*{
	if (num < w.num)
	return true;
	return false;
	}*/
protected:
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };
	CWeapons *m_pWeapons[WEAPON_NUM];
	int m_WCnt;
	int num;
	int live; //生命元	
	int m_pos;	//武士所在位置
};

//bool operator<(const Warrior w1, const Warrior w2)
//{
//
//	if (w1.num < w2.num)
//		return true;
//	return false;
//	
//}

//武士集合
class CWarriorSet
{
#define ALLOC_SIZE		(32) //每次分配空间32
public:
	CWarriorSet()
	{
		m_pWarriorset = new Warrior* [ALLOC_SIZE];
		for (int i = 0; i < ALLOC_SIZE; i++)
		{
			m_pWarriorset[i] = 0;
		}
		m_size = ALLOC_SIZE;
		m_used = 0;
	}
	void Insert(Warrior *pWarrior);
	Warrior* Begin();
	Warrior* End();
	void Remove(Warrior *pWarrior);
public:
	int m_size;
	int m_used;
	Warrior ** m_pWarriorset;
};

void CWarriorSet::Remove(Warrior *pWarrior)
{
	for (int i = 0; i < m_used; i++)
	{
		if (pWarrior == m_pWarriorset[i])
		{
			for (int j = i; j < m_used-1; j++)
			{
				m_pWarriorset[j] = m_pWarriorset[j + 1];
			}
			delete pWarrior;
		}
	}
}

Warrior* CWarriorSet::Begin()
{
	return m_pWarriorset[0];
}

Warrior* CWarriorSet::End()
{
	return m_pWarriorset[m_used];
}

void CWarriorSet::Insert(Warrior *pWarrior)
{
	if (m_used < m_size)
	{
		m_pWarriorset[m_used++] = pWarrior;
	}
	else
	{
		Warrior **ptr;
		m_size += ALLOC_SIZE;
		ptr = new Warrior* [m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_pWarriorset[i] = 0;
		}
		for (int i = 0; i < m_used; i++)
		{
			ptr[i] = m_pWarriorset[i];
		}
		delete[] m_pWarriorset;
		m_pWarriorset = ptr;
		m_pWarriorset[m_used++] = pWarrior;
	}
}

///////////////////////////////////////////////////////////////////////
class Headquarter
{

public:
	static int time;

	Headquarter(int live, int lives[], HeadquarterType color, int pos)
		:m_total_live(live), m_Color(color), m_pos(pos)
	{
		m_warrior_no = 1;
		for (int i = 0; i < WARRIOR_NUM; i++)
		{
			m_warrior_lives[i] = lives[i];
		}
	}
	int CanCreateWarrior();
	Warrior* CreateWarrior(WarriorType type);
	int GetWarriorCnt(WarriorType type);
	friend void Warrior::Display();
public:
	HeadquarterType m_Color;
	int m_warriorcnt[WARRIOR_NUM] = { 0, 0, 0, 0, 0 };
	CWarriorSet m_Warriorset;//存放司令部管理下的武士
	
protected:
	int m_total_live;
	int m_warrior_lives[WARRIOR_NUM];
	int m_warrior_no;	
	int m_pos; //司令部位置
};

class CSword : public CWeapons
{
public:
	CSword()
	{
		m_Name = "sword";
	}
};

class CBomb : public CWeapons
{
public:
	CBomb()
	{
		m_Name = "bomb";
	}
};

class CArrow : public CWeapons
{
public:
	CArrow()
	{
		m_Name = "arrow";
	}
};


class CDragon : public Warrior
{
public:
	CDragon(int l, int n, float m):Warrior(DRAGON, l, n)
	{
		int wtype = n % 3;
		
		CWeapons *pWeapon = NULL;
		switch (wtype)
		{
		case SWORD:
			pWeapon = new CSword();
			break;
		case BOMB:
			pWeapon = new CBomb();
			break;
		case ARROW:
			pWeapon = new CArrow();
			break;	
		}
		m_pWeapons[m_WCnt++] = pWeapon;

		m_Morale = m;
	}

	virtual void Display()
	{
		Warrior::Display();		
		if (m_WCnt)
		{
			cout << "It has a " << m_pWeapons[0]->m_Name << ",and it's morale is "
				<< setprecision(2)<<fixed<< m_Morale << endl;
		}
	}
private:
	float m_Morale;//士气
};

class CNinja : public Warrior
{
public:
	CNinja(int l, int n) : Warrior(NINJA, l, n)
	{	
		int wtype = n % 3;

		int i = 0;
		while (i < 2)
		{
			wtype = (n+i) % 3;
			CWeapons *pWeapon = NULL;
			switch (wtype)
			{
			case SWORD:
				pWeapon = new CSword();
				break;
			case BOMB:
				pWeapon = new CBomb();
				break;
			case ARROW:
				pWeapon = new CArrow();
				break;
			}
			m_pWeapons[m_WCnt++] = pWeapon;
			i++;
		}		
	}
	virtual void Display()
	{
		Warrior::Display();
		cout << "It has a " << m_pWeapons[0]->m_Name << " and a "
			<< m_pWeapons[1]->m_Name << endl;			
	}
};

class CIceman : public Warrior
{
public:
	CIceman(int l, int n) : Warrior(ICEMAN, l, n)
	{
		int wtype = n % 3;

		CWeapons *pWeapon = NULL;
		switch (wtype)
		{
		case SWORD:
			pWeapon = new CSword();
			break;
		case BOMB:
			pWeapon = new CBomb();
			break;
		case ARROW:
			pWeapon = new CArrow();
			break;
		}
		m_pWeapons[m_WCnt++] = pWeapon;
	}
	virtual void Display()
	{
		Warrior::Display();
		cout << "It has a " << m_pWeapons[0]->m_Name << endl;
	}
};

class CLion : public Warrior
{
public:
	CLion(int l, int n, int loy) : Warrior(LION, l, n)
	{
		m_loyalty = loy;
	}
	virtual void Display()
	{
		Warrior::Display();
		cout << "It's loyalty is " << m_loyalty << endl;
	}
	int GetLoyalty()
	{
		return m_loyalty;
	}
	int SubLoyalty(int loy)
	{
		m_loyalty -= loy;
	}

	void Runaway(void)
	{
		if (m_pHeadquarter->m_Color == RED)
			cout << " red " << m_Name[type] << " " << num
			<< " ran away" << endl;
		else
			cout << " blue " << m_Name[type] << " " << num
				<< " ran away" << endl;		
	}
private:
	int m_loyalty;//忠诚度
};

class CWolf : public Warrior
{
public:
	CWolf(int l, int n) : Warrior(WOLF, l, n)
	{}
	virtual void Display();
	
};

void CWolf::Display()
{
	Warrior::Display();
}


void Warrior::Display()
{
	//	if ( group == RED)
	if(m_pHeadquarter->m_Color == RED)
	{
		cout << " red " << m_Name[type] << " " << num <<
			" born" << endl;
		/*with strength " << live << ", " << 
			m_pHeadquarter->GetWarriorCnt(type) << " " <<
			 m_Name[type] << " in red headquarter" << endl;		*/	
	}
	else
	{
		cout << " blue " << m_Name[type] << " " << num <<
			" born" << endl;
			/*with strength " << live << "," << 
			m_pHeadquarter->GetWarriorCnt(type) << " " <<
			 m_Name[type] << " in blue headquarter" << endl;*/
	}
}







int Headquarter::GetWarriorCnt(WarriorType type)
{
	return m_warriorcnt[type];
}


Warrior* Headquarter::CreateWarrior(WarriorType type)
{
	Warrior *ptr = 0;

	if (m_total_live >= m_warrior_lives[type])
	{
		

		switch (type)
		{
		case DRAGON:
			{
				float morale = m_total_live - m_warrior_lives[type];
				morale /= m_warrior_lives[type];
				ptr = new CDragon(m_warrior_lives[type], m_warrior_no, morale);
			}
			break;
		case NINJA:
			ptr = new CNinja(m_warrior_lives[type], m_warrior_no);
			break;
		case ICEMAN:
			ptr = new CIceman(m_warrior_lives[type], m_warrior_no);
			break;
		case LION:
			ptr = new CLion(m_warrior_lives[type], m_warrior_no,
				m_total_live - m_warrior_lives[type]);
			break;
		/*case WOLF:
			ptr = new CWolf(m_warrior_lives[type], m_warrior_no);
			break;*/
		default:
			ptr = new Warrior(type, m_warrior_lives[type], m_warrior_no);
			break;
		}
	
		m_total_live -= m_warrior_lives[type];
		m_warrior_no++;
		m_warriorcnt[type]++;
		ptr->m_pHeadquarter = this;
		ptr->SetPos(m_pos);
		//将武士加入军籍
		m_Warriorset.Insert(ptr);
	}
	return ptr;
}


int Headquarter::CanCreateWarrior()
{
	int i;
	for (i = 0; i < WARRIOR_NUM; i++)
	{
		if (m_total_live >= m_warrior_lives[i])
			return 1;
	}
	return 0;	
}

/////////////////////////////////////////////////////////////////////////////

class RedHeadquarter : public Headquarter
{
public:
	RedHeadquarter(int live, int lives[], int pos) 
		:Headquarter(live, lives, RED, pos)
	{
		m_nextwarrior = ICEMAN;//iceman、lion、wolf、ninja、dragon	
	};

	Warrior* CreateWarrior();

//	void Warrior::Display();
private:
	WarriorType m_nextwarrior;
};

Warrior* RedHeadquarter::CreateWarrior(void)
{
	WarriorType type = m_nextwarrior;
	Warrior *pWarrior = 0;
	pWarrior = Headquarter::CreateWarrior(type);

	if (pWarrior)
	{
		switch (type)
		{
		case DRAGON:
			m_nextwarrior = ICEMAN;
			break;
		case NINJA:
			m_nextwarrior = DRAGON;
			break;
		case ICEMAN:
			m_nextwarrior = LION;
			break;
		case LION:
			m_nextwarrior = WOLF;
			break;
		case WOLF:
			m_nextwarrior = NINJA;
			break;
		default:
			break;
		}
	}
	return pWarrior;
}


class BlueHeadquarter : public Headquarter
{
public:
	BlueHeadquarter(int live, int lives[], int pos) 
		:Headquarter(live, lives, BLUE, pos)
	{
		m_nextwarrior = LION; //lion、dragon、ninja、iceman、wolf		
	};

	Warrior*  CreateWarrior();
private:
	WarriorType m_nextwarrior;	
	int m_pos;
};



Warrior* BlueHeadquarter::CreateWarrior()
{
	WarriorType type = m_nextwarrior;
	Warrior *pWarrior = NULL;
	pWarrior = Headquarter::CreateWarrior(type);
	switch (type)
	{
	case DRAGON:		
		m_nextwarrior = NINJA;
		break;
	case NINJA:		
		m_nextwarrior = ICEMAN;
		break;
	case ICEMAN:		
		m_nextwarrior = WOLF;
		break;
	case LION:		
		m_nextwarrior = DRAGON;
		break;
	case WOLF:		
		m_nextwarrior = LION;
		break;
	default:
		break;
	}
	return pWarrior;
}



class SystemOP
{
public:
	int m_nCity;
	int m_nLoyalty;
	int m_nSysLive;
	int m_CurHour;
	int m_CurMinute;
	int m_SysMinutes;
	int *m_pLiveWarrior;
	int *m_pAttack;
	RedHeadquarter *m_pRedHead;
	BlueHeadquarter *m_pBlueHead;


	void Init(int nCity, int nLoy, int nSysLive, int nMinutes, int *pLive,
		int *pAttack);
	void DispTime(void);
	void SysRun();
	void SysCreateWarrior();
	void SysCheckLion();
};

void SystemOP::Init(int nCity, int nLoy, int nSyslive, int nMinutes, int *pLive,
	int *pAttack)
{
	m_nCity = nCity;
	m_nLoyalty = nLoy;
	m_nSysLive = nSyslive;
	m_CurHour = 0;
	m_CurMinute = 0;
	m_SysMinutes = nMinutes;
	m_pLiveWarrior = pLive;
	m_pAttack = pAttack;
	m_pRedHead = new RedHeadquarter(m_nSysLive, m_pLiveWarrior, 0);
	m_pBlueHead = new BlueHeadquarter(m_nSysLive, m_pLiveWarrior, m_nCity+1);
}

void SystemOP::DispTime()
{
	cout << fixed << setw(3) << setfill('0')
		<< m_CurHour << ":"	<< setw(2) << setfill('0') << m_CurMinute;	
}

void SystemOP::SysCreateWarrior(void)
{
	Warrior *pWarrior;
	
	if ((pWarrior = m_pRedHead->CreateWarrior()) != NULL)
	{
		DispTime();
		pWarrior->Display();
	}
	
	if ((pWarrior = m_pBlueHead->CreateWarrior()) != NULL) 
	{
		DispTime();
		pWarrior->Display();
	}
}

void SystemOP::SysCheckLion()
{
	Warrior *p = m_pRedHead->m_Warriorset.Begin();// .m_pWarriorset[0];
	
	while (p != 0 && p != m_pRedHead->m_Warriorset.End())
	{
		if (p->type == LION)
		{
			CLion *pLion = (CLion*)p;
			if (pLion->GetLoyalty() == 0)
			{
				DispTime();
				pLion->Runaway();
				m_pRedHead->m_Warriorset.Remove(pLion);
			}
		}
		p++;
	}
	p = m_pBlueHead->m_Warriorset.Begin();
	while (p != 0 && p != m_pBlueHead->m_Warriorset.End())
	{
		if (p->type == LION)
		{
			CLion *pLion = (CLion*)p;
			if (pLion->GetLoyalty() == 0)
			{
				DispTime();
				pLion->Runaway();
				m_pRedHead->m_Warriorset.Remove(pLion);
			}
		}
		p++;
	}
}

void SysWarriorMove()
{

}





void SystemOP::SysRun()
{
	while (1)
	{
		switch (m_CurMinute)
		{
		default:
			break;
		case 0:   //每小时0分 创造武士
			SysCreateWarrior();
			m_CurMinute = 5;
			break;
		case 5:  //lion 逃跑时刻
			SysCheckLion();
			m_CurMinute = 10;
			break;
		case 10:  //武士前进
			SysWarriorMove();
			break;
		}
	}
}

int main()
{
	int cnt;

	int live, nCity, nLoyalty, tEnd;
	int hour_val = 0, minute_val =0;
	int branch = 0;
	int live_warrior[WARRIOR_NUM];
	int attack_live[WARRIOR_NUM];

	
	cin >> cnt;
	
	for (int i = 0; i < cnt; i++)
	{
		cin >> live >> nCity >> nLoyalty >> tEnd;

		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> live_warrior[j];
		}
		//武士攻击时的攻击力
		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> attack_live[j];
		}


		SystemOP sysOp;	
		sysOp.Init(nCity, nLoyalty, live, tEnd, live_warrior, attack_live);
				
		cout << "Case:" << i + 1 << endl;		
		sysOp.SysRun();

		//while (1)
		//{
		//	//printf("%03d", time_val);
		//	DispTime(hour_val, minute_val);



		//	if (pRed->CanCreateWarrior())
		//	{
		//		while ((pWarrior = pRed->CreateWarrior()) == NULL){}
		//		pWarrior->Display();
		//		delete pWarrior;
		//	}
		//	else
		//	{
		//		cout << " red headquarter stops making warriors" << endl;
		//		branch = 0;
		//		break;
		//	}

		//	//printf("%03d", time_val);
		//	DispTime(hour_val, minute_val);

		//	DispTime(hour, minute);

		//	if (pBlue->CanCreateWarrior())
		//	{
		//		while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
		//		pWarrior->Display();
		//		delete pWarrior;
		//	}
		//	else
		//	{
		//		cout << " blue headquarter stops making warriors" << endl;
		//		branch = 1;

		//		//time_val++;
		//		hour_val++;
		//		break;
		//	}	
		//	hour_val++;

		//		time_val++;
		//		break;
		//	}	
		//	time_val++;

		//}
		//if (branch) //blue
		//{
		//	while (pRed->CanCreateWarrior())
		//	{

		//		//printf("%03d", time_val);
		//		DispTime(hour_val, minute_val);
		//		while ((pWarrior = pRed->CreateWarrior()) == NULL) {}				
		//		pWarrior->Display();
		//		delete pWarrior;
		//		//time_val++;
		//		hour_val++;
		//	}
		//	//printf("%03d", time_val);
		//	DispTime(hour_val, minute_val);

		//		DispTime(hour, minute);
		//		while ((pWarrior = pRed->CreateWarrior()) == NULL) {}				
		//		pWarrior->Display();
		//		delete pWarrior;
		//		time_val++;
		//	}
		//	DispTime(hour, minute);

		//	cout << " red headquarter stops making warriors" << endl;		
		//}
		//else
		//{
		//	while (pBlue->CanCreateWarrior())
		//	{

		//		//printf("%03d", time_val);
		//		DispTime(hour_val, minute_val);

		//		DispTime(hour, minute);

		//		while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
		//		//pBlue->DispWarrior(pWarrior);
		//		pWarrior->Display();
		//		delete pWarrior;

		//		//time_val++;
		//		hour_val++;
		//	}
		//	//printf("%03d", time_val);
		//	DispTime(hour_val, minute_val);
		//	cout << " blue headquarter stops making warriors" << endl;
		//}	
		//delete pRed;
		//delete pBlue;		

		//		time_val++;
		//	}
		//	DispTime(hour, minute);
		//	cout << " blue headquarter stops making warriors" << endl;
		//}	

	}
		
	return 0;
}