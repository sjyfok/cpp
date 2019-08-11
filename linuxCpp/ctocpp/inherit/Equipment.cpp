#include <iostream>
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

#define  WARRIOR_NUM		5

class Headquarter;
///////////////////////////CWeapons//////////////////
class CWeapons
{
public:
	CWeapons();
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
	}
	void Display();


protected:
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };

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
	CSword();
};

class CBomb : public CWeapons
{
public:
	CBomb();
};

class CArrow : public CWeapons
{
public:
	CArrow();
};





class Headquarter;
class RedHeadquarter;

void Warrior::Display()
{
	//	if ( group == RED)
	if(m_pHeadquarter->m_Color == RED)
	{
		cout << " red " << m_Name[type] << " " << num <<
			" born with strength " << live << "," << 
		//	m_pHeadquarter->GetWarriorCnt(type) << " " <<
			 m_Name[type] << " in red headquarter" << endl;			
	}
	//else
	//{
	//	cout << " blue " << m_Name[type] << " " << num <<
	//		" born with strength " << live << "," << 
	////		m_pHeadquarter->GetWarriorCnt(type) << " " <<
	//		 m_Name[type] << " in blue headquarter" << endl;
	//}
}

class CDragon : public Warrior
{
public:
	virtual void Display()
	{
		Warrior::Display();

	}
};





int Headquarter::GetWarriorCnt(WarriorType type)
{
	return m_warriorcnt[type];
}


Warrior* Headquarter::CreateWarrior(WarriorType type)
{
	Warrior *ptr = 0;

	if (m_total_live >= m_warrior_lives[type])
	{
		ptr = new Warrior(type, m_warrior_lives[type], m_warrior_no);
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

	friend void Warrior::Display();
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




int main()
{
	int cnt;
	int live;
	int time_val = 0;
	int branch = 0;
	int live_warrior[WARRIOR_NUM];
	Warrior *pWarrior;
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		cin >> live;
		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> live_warrior[j];
		}
		RedHeadquarter *pRed = new RedHeadquarter(live, live_warrior);
		BlueHeadquarter *pBlue = new BlueHeadquarter(live, live_warrior);
		
		cout << "Case:" << i + 1 << endl;
		time_val = 0;
		while (1)
		{
			printf("%03d", time_val);
			if (pRed->CanCreateWarrior())
			{
				while ((pWarrior = pRed->CreateWarrior()) == NULL){}
				pWarrior->Display();
				delete pWarrior;
			}
			else
			{
				cout << " red headquarter stops making warriors" << endl;
				branch = 0;
				break;
			}
			printf("%03d", time_val);
			if (pBlue->CanCreateWarrior())
			{
				while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
				pWarrior->Display();
				//pBlue->DispWarrior(pWarrior);
				delete pWarrior;
			}
			else
			{
				cout << " blue headquarter stops making warriors" << endl;
				branch = 1;
				time_val++;
				break;
			}	
			time_val++;
		}
		if (branch) //blue
		{
			while (pRed->CanCreateWarrior())
			{
				printf("%03d", time_val);
				while ((pWarrior = pRed->CreateWarrior()) == NULL) {}
				//pRed->DispWarrior(pWarrior);
				pWarrior->Display();
				delete pWarrior;
				time_val++;
			}
			printf("%03d", time_val);
			cout << " red headquarter stops making warriors" << endl;		
		}
		else
		{
			while (pBlue->CanCreateWarrior())
			{
				printf("%03d", time_val);
				while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
				//pBlue->DispWarrior(pWarrior);
				pWarrior->Display();
				delete pWarrior;
				time_val++;
			}
			printf("%03d", time_val);
			cout << " blue headquarter stops making warriors" << endl;
		}	
		delete pRed;
		delete pBlue;		
	}
		
	return 0;
}