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

enum GroupType
{
	RED = 0,
	BLUE,
};

///////////////////////////CWeapons//////////////////
class CWeapons
{
public:
	CWeapons();
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



#define  WARRIOR_NUM		5
class Warrior
{
public:
	WarriorType type;
	
	Warrior(WarriorType t, int l, GroupType g, int n) 
		:type(t), live(l), group(g), num(n)
	{
		
	}
	char *GetName()
	{
		return m_Name[type];
	}
	int GetNum()
	{
		return num;
	}
	int GetLive()
	{
		return live;
	}

	virtual void Display()
	{}

protected:
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };
	
	int num;
	int live; //ÉùÃ÷Ôª
	GroupType group; //ÅÉ±ð
};

class CDragon : public Warrior
{
public:
	virtual void Display()
	{
		if (group == RED)
		{
			cout << " red " << m_Name[type] << " " << num << 
				" born with strength " << live << "," << 
		}
		cout << " red " << pWarrior->GetName() << " " << pWarrior->GetNum() <<
			" born with strength " << pWarrior->GetLive() << ","
			<< m_warriorcnt[pWarrior->type] << " " << pWarrior->GetName()
			<< " in red headquarter" << endl;
	}
};




class Headquarter
{
	
public:
	static int time;
	
	Headquarter(int live, int lives[]) :m_total_live(live)
	{
		m_warrior_no = 1;
		for (int i = 0; i < WARRIOR_NUM; i++)
		{
			m_warrior_lives[i] = lives[i];
		}
	}
	int CanCreateSamurai();
	Warrior*  CreateWarrior(WarriorType type, GroupType group);
protected:
	int m_total_live;
	int m_warrior_lives[WARRIOR_NUM];
	int m_warrior_no;
	int m_warriorcnt[WARRIOR_NUM] = { 0, 0, 0, 0, 0 };
};

Warrior* Headquarter::CreateWarrior(WarriorType type, GroupType group)
{
	Warrior *ptr = NULL;
	if (m_total_live >= m_warrior_lives[type])
	{
		ptr = new Warrior(type, m_warrior_lives[type], group, m_warrior_no);
		m_total_live -= m_warrior_lives[type];
		m_warrior_no++;
		m_warriorcnt[type]++;
	}

	return ptr;
}


int Headquarter::CanCreateSamurai()
{
	int i;
	for (i = 0; i < WARRIOR_NUM; i++)
	{
		if (m_total_live >= m_warrior_lives[i])
			return 1;
	}
	return 0;	
}

class RedHeadquarter : public Headquarter
{
public:
	RedHeadquarter(int live, int lives[]) :Headquarter(live, lives)
	{
		m_nextwarrior = ICEMAN;//iceman¡¢lion¡¢wolf¡¢ninja¡¢dragon
	};

	Warrior*  CreateWarrior();
	void DispWarrior(Warrior* pWarrior);
private:
	WarriorType m_nextwarrior;
};

void RedHeadquarter::DispWarrior(Warrior* pWarrior)
{
	cout << " red " << pWarrior->GetName() << " " << pWarrior->GetNum() <<
		" born with strength " << pWarrior->GetLive() << ","
		<< m_warriorcnt[pWarrior->type] << " " << pWarrior->GetName()
		<< " in red headquarter" << endl;
}

Warrior* RedHeadquarter::CreateWarrior()
{
	WarriorType type = m_nextwarrior;
	Warrior *pWarrior = NULL;
	pWarrior = Headquarter::CreateWarrior(type, RED);
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
	BlueHeadquarter(int live, int lives[]) :Headquarter(live, lives)
	{
		m_nextwarrior = LION; //lion¡¢dragon¡¢ninja¡¢iceman¡¢wolf
	};

	Warrior*  CreateWarrior();
	void DispWarrior(Warrior* pWarrior);
private:
	WarriorType m_nextwarrior;	
};

void BlueHeadquarter::DispWarrior(Warrior* pWarrior)
{
	cout << " blue " << pWarrior->GetName() << " " << pWarrior->GetNum() <<
		" born with strength " << pWarrior->GetLive() << ","
		<< m_warriorcnt[pWarrior->type] << " " << pWarrior->GetName()
		<< " in blue headquarter" << endl;
}

Warrior* BlueHeadquarter::CreateWarrior()
{
	WarriorType type = m_nextwarrior;
	Warrior *pWarrior = NULL;
	pWarrior = Headquarter::CreateWarrior(type, RED);
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
			if (pRed->CanCreateSamurai())
			{
				while ((pWarrior = pRed->CreateWarrior()) == NULL){}
				pWarrior->Display();
				pRed->DispWarrior(pWarrior);
				delete pWarrior;
			}
			else
			{
				cout << " red headquarter stops making warriors" << endl;
				branch = 0;
				break;
			}
			printf("%03d", time_val);
			if (pBlue->CanCreateSamurai())
			{
				while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
				pBlue->DispWarrior(pWarrior);
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
			while (pRed->CanCreateSamurai())
			{
				printf("%03d", time_val);
				while ((pWarrior = pRed->CreateWarrior()) == NULL) {}
				pRed->DispWarrior(pWarrior);
				delete pWarrior;
				time_val++;
			}
			printf("%03d", time_val);
			cout << " red headquarter stops making warriors" << endl;		
		}
		else
		{
			while (pBlue->CanCreateSamurai())
			{
				printf("%03d", time_val);
				while ((pWarrior = pBlue->CreateWarrior()) == NULL) {}
				pBlue->DispWarrior(pWarrior);
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