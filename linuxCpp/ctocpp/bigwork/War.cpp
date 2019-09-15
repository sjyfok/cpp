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

protected:
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };
	CWeapons *m_pWeapons[WEAPON_NUM];
	int m_WCnt;
	int num;
	int live; //生命元	
};

///////////////////////////////////////////////////////////////////////
class Headquarter
{

public:
	static int time;

	Headquarter(int live, int lives[], HeadquarterType color)
		:m_total_live(live), m_Color(color)
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
protected:
	int m_total_live;
	int m_warrior_lives[WARRIOR_NUM];
	int m_warrior_no;
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
			" born with strength " << live << "," << 
			m_pHeadquarter->GetWarriorCnt(type) << " " <<
			 m_Name[type] << " in red headquarter" << endl;			
	}
	else
	{
		cout << " blue " << m_Name[type] << " " << num <<
			" born with strength " << live << "," << 
			m_pHeadquarter->GetWarriorCnt(type) << " " <<
			 m_Name[type] << " in blue headquarter" << endl;
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
	RedHeadquarter(int live, int lives[]) 
		:Headquarter(live, lives, RED)
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
	
	return pWarrior;
}






class BlueHeadquarter : public Headquarter
{
public:
	BlueHeadquarter(int live, int lives[]) 
		:Headquarter(live, lives, BLUE)
	{
		m_nextwarrior = LION; //lion、dragon、ninja、iceman、wolf		
	};

	Warrior*  CreateWarrior();
private:
	WarriorType m_nextwarrior;	
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


class SystemOp
{
public:
	RedHeadquarter * m_pRedHeader;
	BlueHeadquarter *m_pBlueHeader;
	int *m_pLiveWarrior;
	int *m_pAttack;
	int m_CurHour;   //当前时间
	int m_CurMinute;
	int m_SysMinutes;  //系统总时间
	int m_nCity;	//系统中城市总数
	int m_nLoyalty; //忠诚度

public:
	SystemOp();
	~SystemOp();
	void CreateWarriorMonment();  //创建武士时刻
	void DispCurSysTime();
};

SystemOp::~SystemOp()
{
	delete m_pRedHeader;
	delete m_pBlueHeader;
}

SystemOp::SystemOp()
{
	RedHeadquarter *pRed = new RedHeadquarter(live, live_warrior);
	BlueHeadquarter *pBlue = new BlueHeadquarter(live, live_warrior);
}

void SystemOp::CreateWarriorMonment()
{

}

void SystemOp::DispCurSysTime()
{
	cout << fixed << setw(3) << setfill('0') << m_CurHour
		<< ":" << setw(2) << m_CurMinute << " ";
	cout.flush();
}

int GetCurMinutes(int hour, int minutes)
{
	return hour * 60 + minutes;
}




int main()
{
	int cnt;
	int live, nCity, nLoyalty, tol_minutes, cur_minutes;
	int hour = 0, minute = 0;  //时间
	int branch = 0;
	int live_warrior[WARRIOR_NUM];
	int attack_live[WARRIOR_NUM]; //攻击力

	Warrior *pWarrior;
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		cin >> live >> nCity >> nLoyalty >> tol_minutes;
		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> live_warrior[j];
		}
		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> attack_live[j];
		}

		SystemOp op = new SystemOp()

		RedHeadquarter *pRed = new RedHeadquarter(live, live_warrior);
		BlueHeadquarter *pBlue = new BlueHeadquarter(live, live_warrior);
		
		cout << "Case:" << i + 1 << endl;
		cur_minutes = 0;
		while (cur_minutes < tol_minutes)
		{
			cur_minutes = GetCurMinutes(hour, minute);
			switch (minute)
			{
			default:
				break;
			case 0:  //创建武士
				minute = 5;
				
				break;
			case 5:  //lion 逃跑时刻
				minute = 10;
				break;
			case 10: //武士前进一步
				minute = 35;
				break; 
			case 35: //wolf抢夺敌人武器
				minute = 40;				
				break;
			case 40: //双方武士发生战斗
				minute = 50;
				break;
			case 50: //报告司令部的生命元
				minute = 55;				
				break;
			case 55: //每个武士报告拥有的武器
				minute = 0;
				hour++;			
				break;
			}
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
		//		time_val++;
		//		break;
		//	}	
		//	time_val++;
		//}
		//if (branch) //blue
		//{
		//	while (pRed->CanCreateWarrior())
		//	{
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
		//		DispTime(hour, minute);
		//		while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
		//		//pBlue->DispWarrior(pWarrior);
		//		pWarrior->Display();
		//		delete pWarrior;
		//		time_val++;
		//	}
		//	DispTime(hour, minute);
		//	cout << " blue headquarter stops making warriors" << endl;
		}	
		delete pRed;
		delete pBlue;		
	}
		
	return 0;
}