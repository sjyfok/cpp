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
	WEAPONTYPEEND,
};

#define  WARRIOR_NUM		5
#define  WEAPON_NUM			10 //每个武士最多拥有10个武器

class Headquarter;
class CSword;
class CBomb;
class CArrow;
///////////////////////////CWeapons//////////////////
class CWeapons
{
public:
	CWeapons(string s, WeaponType wType) : m_Name(s),m_wType(wType){};
	virtual int GetInjury(int force = 0);
	virtual int GetBackInjury(int force = 0);
	virtual int CheckWeapon();  //检查武器是否可用
	string m_Name;
	WeaponType m_wType;
};

int CWeapons::GetInjury(int force)
{
	return 0;
}

int CWeapons::GetBackInjury(int force)
{
	return 0;
}

int CWeapons::CheckWeapon(void)
{
	return 1;  //范围武器的残值 范围0是武器报废
}

class Warrior
{
public:
	Headquarter * m_pHeadquarter;  //所属司令部
	WarriorType type;
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };
	int num;  //武士编号
public:
	Warrior(WarriorType t, int l, int f, int n)
		:type(t), live(l), m_force(f), num(n)
	{
		m_pHeadquarter = NULL;
		m_WCnt = 0;
		m_usedWeapon = 0;
	}
	virtual void Display();	
	virtual void Yell()
	{}
	//缴获对方武器
	void SwitchWeapon()
	{
		if (m_WCnt)
		{
			m_usedWeapon++;
			if (m_usedWeapon >= m_WCnt)
			{
				m_usedWeapon = 0;
			}
		}
	}

	void SeizedWeapons(Warrior *pw);
	void SetPos(int pos)
	{
		m_pos = pos;
	}

	int GetPos()
	{
		return m_pos;
	}
	int GetWeaponCnt()
	{
		return m_WCnt;
	}
	virtual void Move();
	void DispPos();
	void AddWeapon(CWeapons *pWeapon);
	int CanRobWeaponsCnt();
	int GetWeaponsCnt() //获得武器数量
	{
		return m_WCnt;
	}
	CWeapons* RemoveWeapon(int idx);
	int Fight(Warrior *pWarrior);
	//void AttackWith(CWeapons *pWeapon, Warrior *pWarrior);
	void Injury(int dlive);
	int GetLive()
	{
		return live;
	}
	
	void Report();

	int GetForce()
	{
		return m_force;
	}
protected:
	CWeapons *m_pWeapons[WEAPON_NUM];
	int m_terrer[WEAPON_NUM];
	int m_usedWeapon;
	int m_WCnt;
	int live; //生命元	
	int m_pos;	//武士所在位置
	int m_force;
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
	Warrior** Begin();
	Warrior** End();
	Warrior** REnd();//返回最后一个有效记录 集合为空返回 NULL
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
		//	delete pWarrior;
			m_used--;
			break;
		}
	}
}

Warrior** CWarriorSet::Begin()
{
	return &m_pWarriorset[0];
}

Warrior** CWarriorSet::End()
{
	return &m_pWarriorset[m_used];	
}

Warrior** CWarriorSet::REnd()
{
	if (m_used)
	{
		return &m_pWarriorset[m_used - 1];
	}
	return NULL;
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

	Headquarter(int live, int lives[], int force[], HeadquarterType color, int pos)
		:m_total_live(live), m_Color(color), m_pos(pos)
	{
		m_warrior_no = 1;
		for (int i = 0; i < WARRIOR_NUM; i++)
		{
			m_warrior_lives[i] = lives[i];
			m_warrior_force[i] = force[i];
		}
	}
	bool CanCreateWarrior(WarriorType type);
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
	int m_warrior_force[WARRIOR_NUM];
	int m_warrior_no;	
	int m_pos; //司令部位置
};

class CSword : public CWeapons
{
public:
	CSword():CWeapons("sword", SWORD)
	{
		
	}
	virtual int GetForce(int f = 0);
};

int CSword::GetForce(int f)
{
	float tmp;
	tmp = f;
	tmp *= 0.2;
	return (int)tmp;
}

class CBomb : public CWeapons
{
public:
	CBomb():CWeapons("bomb", BOMB)
	{
		m_nUsed = 1;  //bomb 只能用一次
	}
	virtual int GetInjury(int f = 0);
	virtual int GetBackInjury(int force = 0);
	virtual int CheckWeapon();  //检查武器
	int m_nUsed;
};

int CBomb::CheckWeapon()
{
	return m_nUsed;
}

int CBomb::GetBackInjury(int f)
{
	float tmp = f;
	tmp *= 0.5;
	return (int)tmp;
}

int CBomb::GetInjury(int f)
{
	float tmp = f;
	tmp *= 0.4;
	m_nUsed--;
	return (int)tmp;
}

class CArrow : public CWeapons
{
public:
#define  ARROW_USED_TOL   (2)  
	CArrow():CWeapons("arrow", ARROW)
	{
		m_nUsed = ARROW_USED_TOL;
	}

	virtual int GetInjury(int f = 0);
	virtual int CheckWeapon();  //检查武器
	int m_nUsed;  //使用次数  新武器可使用3次，用过3次后消亡
};

int CArrow::CheckWeapon()
{
	return m_nUsed;
}

int CArrow::GetInjury(int f)
{
	float tmp = f;
	tmp *= 0.3;
	m_nUsed--;
	return (int)tmp;
}

class CDragon : public Warrior
{
public:
	CDragon(int l, int f, int n, float m):Warrior(DRAGON, l, f, n)
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

		AddWeapon(pWeapon);
		m_Morale = m;
	}

	virtual void Display()
	{
		Warrior::Display();		
	/*	if (m_WCnt)
		{
			cout << "It has a " << m_pWeapons[0]->m_Name << ",and it's morale is "
				<< setprecision(2)<<fixed<< m_Morale << endl;
		}*/
	}
	virtual void Yell()
	{
		if (m_pHeadquarter->m_Color == RED)
		{
			cout << " red dragon " << num << " yelled in city " << m_pos << endl;
		}
		else
		{
			cout << " blue dragon " << num << " yelled in city " << m_pos << endl;
		}
	}
private:
	float m_Morale;//士气
};

class CNinja : public Warrior
{
public:
	CNinja(int l, int f, int n) : Warrior(NINJA, l, f, n)
	{	
		int wtype ;

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
			AddWeapon(pWeapon);
			//m_pWeapons[m_WCnt++] = pWeapon;
			i++;
		}		
	}
	virtual void Display()
	{
		Warrior::Display();
		/*cout << "It has a " << m_pWeapons[0]->m_Name << " and a "
			<< m_pWeapons[1]->m_Name << endl;	*/		
	}
};

class CIceman : public Warrior
{
public:
	CIceman(int l, int f, int n) : Warrior(ICEMAN, l, f, n)
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
		AddWeapon(pWeapon);
		//m_pWeapons[m_WCnt++] = pWeapon;
	}
	virtual void Display()
	{
		Warrior::Display();
		//cout << "It has a " << m_pWeapons[0]->m_Name << endl;
	}
	//iceman 每前进一步 消耗掉0.1的生命
	virtual void Move()  
	{
		float flive = live;
		flive *= 0.1;
		live -= (int)flive;		
		Warrior::Move();
	}
};

//LION没前几一步 需要消耗的忠诚度
int g_loy_use = 0;
class CLion : public Warrior
{
public:
	CLion(int l, int f, int n, int loy) : Warrior(LION, l, f, n)
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
		AddWeapon(pWeapon);
		m_loyalty = loy;
	}
	virtual void Display()
	{
		Warrior::Display();
		cout << "Its loyalty is " << m_loyalty << endl;
	}
	virtual void Move()
	{
		SubLoyalty(g_loy_use);
		Warrior::Move();
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
	CWolf(int l, int f, int n) : Warrior(WOLF, l, f, n)
	{}
	virtual void Display();
	void RobWeapons(Warrior *pWarrior);
	bool CanRobWeapons(Warrior *pWarrior); //判断是否可以抢夺
};

void CWolf::Display()
{
	Warrior::Display();
}

bool CWolf::CanRobWeapons(Warrior *pWarrior)
{
	//武器太多 
	if (m_WCnt >= WARRIOR_NUM)
	{
		return false;
	}
	//对方没有武器
	if (pWarrior->CanRobWeaponsCnt() <= 0)
	{
		return false;
	}
	return true;
}

void CWolf::RobWeapons(Warrior *pWarrior)
{
	if (m_WCnt < WARRIOR_NUM)
	{
		CWeapons *pWeapon;
		int fnRob = 0;//实际被抢走的武器数量
		int nRob = pWarrior->CanRobWeaponsCnt();
		while (nRob)
		{
			fnRob++;
			--nRob;
			pWeapon = pWarrior->RemoveWeapon(nRob);
			AddWeapon(pWeapon);
			if (m_WCnt >= WARRIOR_NUM)
			{
				break;
			}
		}
		if (fnRob)
		{
			if (m_pHeadquarter->m_Color == RED)
			{
				cout << " red wolf " << num << " took " << fnRob
					<< " " << pWeapon->m_Name <<
					" from red " << pWarrior->m_Name[pWarrior->type]
					<< " " << pWarrior->num << " in city " << m_pos << endl;					
			}
			else
			{
				cout << " blue wolf " << num << " took " << fnRob
					<< " " << pWeapon->m_Name <<
					" from red " << pWarrior->m_Name[pWarrior->type]
					<< " " << pWarrior->num << " in city " << m_pos << endl;
			}
		}
	}
}

void Warrior::Move()
{
	if (m_pHeadquarter->m_Color == RED)
		++m_pos;
	else		
		--m_pos;
}

void Warrior::DispPos()
{
	if (m_pHeadquarter->m_Color == RED)
		cout << " red " << m_Name[type] << " " << num
		<< " marched to city " << m_pos << " with " << live
		<< " elements and force " << m_force << endl;
	else
		cout << " blue " << m_Name[type] << " " << num
		<< " marched to city " << m_pos << " with " << live
		<< " elements and force " << m_force << endl;
}

int Warrior::CanRobWeaponsCnt()
{
	if (m_WCnt <= 0)
	{
		return 0;
	}
	else
	{
		int wType = m_pWeapons[0]->m_wType;
		CWeapons *pWeapon = m_pWeapons[1];
		int i;
		for (i = 1; i < m_WCnt; i++)
		{
			if (pWeapon->m_wType != wType)
			{
				return i;
			}
		}
		return i;
	}	
}

CWeapons* Warrior::RemoveWeapon(int idx)
{
	CWeapons *pWeapon = NULL;
	if (idx < m_WCnt)
	{
		pWeapon = m_pWeapons[idx];
		for (int i = idx; i < m_WCnt-1; i++)
		{
			m_pWeapons[i] = m_pWeapons[i + 1];
		}
		m_WCnt--;
	}

	return pWeapon;
}

void Warrior::AddWeapon(CWeapons *pWeapon)
{
	//武器是已经排好序的数组，先按照武器类型排序 类型就是编号
	//加入类型是arrow，需要将用过的排在前面
	if (m_WCnt < WEAPON_NUM)  //
	{
		int doit = 0;
		//拥有武器的数量没有超过最大值
		int i = 0;
		for (i = 0; i < m_WCnt; i++)
		{
			if (m_pWeapons[i]->m_wType >= pWeapon->m_wType)
			{
				if (m_pWeapons[i]->m_wType == pWeapon->m_wType 
					&& pWeapon->m_wType == ARROW)
				{
					CArrow *p1, *p2;
					p1 = (CArrow*)pWeapon;
					p2 = (CArrow*)m_pWeapons[i];
					if (p1->m_nUsed <= p2->m_nUsed) //可以插入到I的位置
					{
						doit = 1;
					}
				}
				else
					doit = 1;	
				if (doit == 1)
				{
					for (int j = m_WCnt; j >= i; j--)
					{
						m_pWeapons[j + 1] = m_pWeapons[j];
					}
					m_pWeapons[i] = pWeapon;
					m_WCnt++;
					break;
				}
			}			
		}
		if (i >= m_WCnt)  //最大
		{
			m_pWeapons[m_WCnt++] = pWeapon;
		}
	}
}

//缴获武器
void Warrior::SeizedWeapons(Warrior *pw)
{
	if (m_WCnt < WARRIOR_NUM)
	{
		CWeapons *pWeapon;
		int fnRob = 0;//实际被抢走的武器数量
		int nWeapon = pw->GetWeaponsCnt();
		while (nRob)
		{
			fnRob++;
			--nRob;
			pWeapon = pw->RemoveWeapon(nRob);
			AddWeapon(pWeapon);
			if (m_WCnt >= WARRIOR_NUM)
			{
				break;
			}
		}
		if (fnRob)
		{
			if (m_pHeadquarter->m_Color == RED)
			{
				cout << " red wolf " << num << " took " << fnRob
					<< " " << pWeapon->m_Name <<
					" from red " << pWarrior->m_Name[pWarrior->type]
					<< " " << pWarrior->num << " in city " << m_pos << endl;
			}
			else
			{
				cout << " blue wolf " << num << " took " << fnRob
					<< " " << pWeapon->m_Name <<
					" from red " << pWarrior->m_Name[pWarrior->type]
					<< " " << pWarrior->num << " in city " << m_pos << endl;
			}
		}
	}
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




void Warrior::Injury(int dlive)
{
	live -= dlive;
}

//void Warrior::AttackWith(CWeapons *pWeapon, Warrior *pWarrior)
//{
//	
//}

//返回0表示失败 返回1 表示平局 返回2 表示胜利 返回3表示需要继续战斗
int Warrior::Fight(Warrior *pWarrior)
{
	//
	if (GetWeaponCnt())
	{
		CWeapons *pWeapon = m_pWeapons[m_usedWeapon];
		int hurt = pWeapon->GetInjury(m_force);
		pWarrior->Injury(hurt);
		hurt = pWeapon->GetBackInjury(hurt);
		Injury(hurt);
		if (!pWeapon->CheckWeapon())
		{
			RemoveWeapon(m_usedWeapon);
		}
		SwitchWeapon();
	}
	



	//int rsl = 3;
	////双方都没有武器 算平局
	//if (GetWeaponCnt() == 0 && pWarrior->GetWeaponCnt() == 0)
	//{
	//	rsl = 1;  //平局
	//}
	//else
	//{
	//	CWeapons *pWeapon;
	//	pWeapon = m_pWeapons[m_usedWeapon];
	//	int force = pWeapon->GetForce(m_force);

	//	pWarrior->SubLive(force);
	//	if (pWeapon->m_wType == BOMB)
	//	{
	//		force = pWeapon->GetSelfInjury(force);  //参考对敌的伤害
	//		SubLive(force);
	//	}
	//	if (pWeapon->m_wType == ARROW)
	//	{
	//		if (!pWeapon->CheckWeapon())
	//		{
	//			EraseTerrer(m_usedWeapon);
	//			RemoveWeapon(m_usedWeapon);
	//		}
	//	}

	//	//检查胜败
	//	if (GetLive() <= 0)
	//	{
	//		//双方都死了
	//		if (pWarrior->GetLive() <= 0)
	//			rsl = 1;		 //平局
	//		else rsl = 0; //失败 //自己死了对方还活着
	//	}
	//	else if (pWarrior->GetLive() <= 0)
	//	{
	//		rsl = 2; //对方死了 胜利
	//	}		
	//}

	//return rsl;
}

void Warrior::Report()
{
	int weapon[WEAPONTYPEEND];
	int i = 0;
	for (i = 0; i < WEAPONTYPEEND; i++)
	{
		weapon[i] = 0;
	}
	for (i = 0; i < m_WCnt; i++)
	{
		weapon[m_pWeapons[i]->m_wType] ++;
	}
	if (m_pHeadquarter->m_Color == RED)
	{
		cout << " red " << m_Name[type] << " " << num
			<< " has " << weapon[SWORD] << " sword "
			<< weapon[BOMB] << " bomb " << weapon[ARROW]
			<< " arrow and " << live << " elements" << endl;
	}
	else
	{
		cout << " blue " << m_Name[type] << " " << num
			<< " has " << weapon[SWORD] << " sword "
			<< weapon[BOMB] << " bomb " << weapon[ARROW]
			<< " arrow and " << live << " elements" << endl;
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
				ptr = new CDragon(m_warrior_lives[type], m_warrior_force[type], m_warrior_no, morale);
			}
			break;
		case NINJA:
			ptr = new CNinja(m_warrior_lives[type], m_warrior_force[type], m_warrior_no);
			break;
		case ICEMAN:
			ptr = new CIceman(m_warrior_lives[type], m_warrior_force[type], m_warrior_no);
			break;
		case LION:
			ptr = new CLion(m_warrior_lives[type], m_warrior_force[type], m_warrior_no,
				m_total_live - m_warrior_lives[type]);
			break;
		case WOLF:
			ptr = new CWolf(m_warrior_lives[type], m_warrior_force[type],m_warrior_no);
			break;
		default:
			//ptr = new Warrior(type, m_warrior_lives[type], m_warrior_force[type], m_warrior_no);
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


bool Headquarter::CanCreateWarrior(WarriorType type)
{
	return (m_total_live >= m_warrior_lives[type]);

	/*int i;
	for (i = 0; i < WARRIOR_NUM; i++)
	{
		if (m_total_live >= m_warrior_lives[i])
			return 1;
	}
	return 0;	*/
}

/////////////////////////////////////////////////////////////////////////////

class RedHeadquarter : public Headquarter
{
public:
	RedHeadquarter(int live, int lives[], int forces[], int pos) 
		:Headquarter(live, lives, forces, RED, pos)
	{
		m_nextwarrior = ICEMAN;//iceman、lion、wolf、ninja、dragon	
	};

	Warrior* CreateWarrior();
	void DispLive()
	{
		cout << " " << m_total_live << " elements in red headquarter" << endl;
	}
//	void Warrior::Display();
//private:
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
	BlueHeadquarter(int live, int lives[], int forces[], int pos) 
		:Headquarter(live, lives, forces, BLUE, pos)
	{
		m_nextwarrior = LION; //lion、dragon、ninja、iceman、wolf		
	};

	Warrior*  CreateWarrior();
	void DispLive()
	{
		cout << " " << m_total_live << " elements in blue headquarter" << endl;
	}
	WarriorType m_nextwarrior;
private:		
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
	CWarriorSet *m_pCity;
	


	void Init(int nCity, int nLoy, int nSysLive, int nMinutes, int *pLive,
		int *pAttack);
	bool CheckTimeOver();
	void DispTime(void);
	void SysRun();
	void SysCreateWarrior();
	void SysCheckLion();
	void SysWarriorMove();
	void SysWolfRobWappon();
	void SysFight();
	void SysReportHeader();
	void SysReportWarrior();
private:
	bool SysFightIsOver(Warrior *pw1, Warrior *pw2);
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
	g_loy_use = m_nLoyalty;
	m_pCity = new CWarriorSet[nCity];
	m_pRedHead = new RedHeadquarter(m_nSysLive, m_pLiveWarrior, m_pAttack, 0);
	m_pBlueHead = new BlueHeadquarter(m_nSysLive, m_pLiveWarrior, m_pAttack, m_nCity+1);
}

bool SystemOP::CheckTimeOver()
{
	int total = m_CurHour * 60 + m_CurMinute;
	if (total >= m_SysMinutes)
	{
		return false;
	}
	return true;
}


void SystemOP::DispTime()
{
	cout << fixed << setw(3) << setfill('0')
		<< m_CurHour << ":"	<< setw(2) << setfill('0') << m_CurMinute;	
}

void SystemOP::SysCreateWarrior(void)
{
	Warrior *pWarrior;
	
	if (m_pRedHead->CanCreateWarrior(m_pRedHead->m_nextwarrior))
	{
		pWarrior = m_pRedHead->CreateWarrior();
		DispTime();
		pWarrior->Display();
	}
		
	if (m_pBlueHead->CanCreateWarrior(m_pBlueHead->m_nextwarrior))
	{
		pWarrior = m_pBlueHead->CreateWarrior();
		DispTime();
		pWarrior->Display();
	}
}

void SystemOP::SysCheckLion()
{
	Warrior **p = m_pRedHead->m_Warriorset.Begin();// .m_pWarriorset[0];
	
	while (*p != 0 && p != m_pRedHead->m_Warriorset.End())
	{
		if ((*p)->type == LION)
		{
			CLion *pLion = (CLion*)(*p);
			if (pLion->GetLoyalty() == 0)
			{
				DispTime();
				pLion->Runaway();
				m_pCity[pLion->GetPos() - 1].Remove(pLion);
				m_pRedHead->m_Warriorset.Remove(pLion);
				delete pLion;
			}
		}
		p++;
	}
	p = m_pBlueHead->m_Warriorset.Begin();
	while (*p != 0 && p != m_pBlueHead->m_Warriorset.End())
	{
		if ((*p)->type == LION)
		{
			CLion *pLion = (CLion*)(*p);
			if (pLion->GetLoyalty() == 0)
			{
				DispTime();
				pLion->Runaway();
				m_pCity[pLion->GetPos() - 1].Remove(pLion);
				m_pBlueHead->m_Warriorset.Remove(pLion);
				delete pLion;
			}
		}
		p++;
	}
}

void SystemOP::SysWarriorMove()
{
	Warrior **p = m_pRedHead->m_Warriorset.Begin();// .m_pWarriorset[0];

	while (*p != 0 && p != m_pRedHead->m_Warriorset.End())
	{
		if ((*p)->GetPos() != 0)
		{
			m_pCity[(*p)->GetPos()-1].Remove(*p);
		}		
		(*p)->Move();
		m_pCity[(*p)->GetPos()-1].Insert(*p);

		p++;
	}
	p = m_pBlueHead->m_Warriorset.Begin();
	while (*p != 0 && p != m_pBlueHead->m_Warriorset.End())
	{
		if ((*p)->GetPos() != m_nCity+1)
		{
			m_pCity[(*p)->GetPos()-1].Remove(*p);
		}
		(*p)->Move();
		m_pCity[(*p)->GetPos()-1].Insert(*p);
		p++;
	}

	for (int i = 0; i < m_nCity; i++)
	{
		Warrior **pw1, **pw2;
		switch (m_pCity[i].m_used)
		{
		default:
			break;
		case 1:
			pw1 = m_pCity[i].Begin();
			DispTime();
			(*pw1)->DispPos();
			break;
		case 2:
			pw1 = m_pCity[i].Begin();
			pw2 = pw1 + 1;
			if ((*pw1)->m_pHeadquarter->m_Color == RED)
			{
				DispTime();
				(*pw1)->DispPos();
				DispTime();
				(*pw2)->DispPos();
			}
			else
			{
				DispTime();
				(*pw2)->DispPos();
				DispTime();
				(*pw1)->DispPos();
			}
		}		
	}
}

void SystemOP::SysWolfRobWappon()
{
	//按城市遍历
	int i = 0;
	for (i = 0; i < m_nCity; i++)
	{
		if (m_pCity[i].m_used >= 2)
		{
			Warrior **p1, **p2;
			CWolf *pWolf;
			p1 = m_pCity[i].Begin();
			p2 = p1 + 1;
			//两个武士当中有一个WOLF，WOLF将抢夺对方的武器
			if ((*p1)->type == WOLF && (*p2)->type != WOLF)
			{
				pWolf = (CWolf*)(*p1);
				if (pWolf->CanRobWeapons(*p2))
				{
					DispTime();
					pWolf->RobWeapons(*p2);
				}
			}
			if ((*p1)->type != WOLF && (*p2)->type == WOLF)
			{
				pWolf = (CWolf*)(*p2);
				if (pWolf->CanRobWeapons(*p1))
				{
					DispTime();
					pWolf->RobWeapons(*p1);
				}
			}			
		}
	}
	////先找到RED的WOLF 然后去变量BLUE的武士 找到在同一城市的武士,抢夺武器
	////
	//Warrior **p = m_pRedHead->m_Warriorset.Begin();// .m_pWarriorset[0];

	//while (*p != 0 && p != m_pRedHead->m_Warriorset.End())
	//{
	//	if ((*p)->type == WOLF)
	//	{
	//		int nCity = (*p)->GetPos();
	//		Warrior **pT = m_pBlueHead->m_Warriorset.Begin();
	//		while (*pT != 0 && pT != m_pBlueHead->m_Warriorset.End())
	//		{
	//			if ((*pT)->GetPos() == nCity && (*pT)->type != WOLF)
	//			{
	//				//抢夺武器
	//				CWolf *pWolf = (CWolf*)(*p);
	//				DispTime();
	//				pWolf->RobWeapons(*pT);
	//			}
	//			pT++;
	//		}
	//	}		
	//	p++;
	//}
	//p = m_pBlueHead->m_Warriorset.Begin();
	//while (*p != 0 && p != m_pBlueHead->m_Warriorset.End())
	//{
	//	if ((*p)->type == WOLF)
	//	{
	//		int nCity = (*p)->GetPos();
	//		Warrior **pT = m_pRedHead->m_Warriorset.Begin();
	//		while (*pT != 0 && pT != m_pRedHead->m_Warriorset.End())
	//		{
	//			if ((*pT)->GetPos() == nCity && (*pT)->type != WOLF)
	//			{
	//				//抢夺武器
	//				CWolf *pWolf = (CWolf*)(*p);
	//				pWolf->RobWeapons(*pT);
	//			}
	//			pT++;
	//		}
	//	}		
	//	p++;
	//}
}


bool SystemOP::SysFightIsOver(Warrior *pw1, Warrior *pw2)
{
	//1一方已经死掉
	if (pw1->GetLive() > 0 && pw2->GetLive() <= 0)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " red " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " killed blue " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " in city " << pw1->GetPos()
				<< " remaining " << pw1->GetLive() << " elements" << endl;
		}
		else
		{
			cout << " blue " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " killed red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " in city " << pw1->GetPos()
				<< " remaining " << pw1->GetLive() << " elements" << endl;
		}
		return true;
	}
	else if (pw1->GetLive() <= 0 && pw2->GetLive() > 0)
	{
		DispTime();
		if (pw2->m_pHeadquarter->m_Color == RED)
		{
			cout << " red " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " killed blue " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " in city " << pw2->GetPos()
				<< " remaining " << pw2->GetLive() << " elements" << endl;
		}
		else
		{
			cout << " blue " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " killed red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " in city " << pw2->GetPos()
				<< " remaining " << pw2->GetLive() << " elements" << endl;
		}
		return true;
	}
	//2 上方都死掉
	if (pw1->GetLive() <= 0 && pw2->GetLive() <= 0)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " and blue " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " died in city " << pw1->GetPos() << endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " and blue " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " died in city " << pw2->GetPos() << endl;
		}
		return true;
	}
	//3双方都没有武器 结束战斗
	if (pw1->GetWeaponCnt() == 0 &&
		pw2->GetWeaponCnt() == 0)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " and blue " <<
				pw2->m_Name[pw2->type] << " " << pw2->num
				<< " were alive in " << "city " << pw1->GetPos()
				<< endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " and blue " <<
				pw1->m_Name[pw1->type] << " " << pw1->num
				<< " were alive in " << "city " << pw1->GetPos()
				<< endl;
		}
		return true;
	}	
	//4双方的攻击力太弱 不能对对方造成伤害
	if (pw1->GetForce() <= 1 && pw2->GetForce() <= 1)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " and blue " <<
				pw2->m_Name[pw2->type] << " " << pw2->num
				<< " were alive in " << "city " << pw1->GetPos()
				<< endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " and blue " <<
				pw1->m_Name[pw1->type] << " " << pw1->num
				<< " were alive in " << "city " << pw1->GetPos()
				<< endl;
		}
		return true;
	}
	return false;  //没有分出胜负
}

void SystemOP::SysFight()  
{
	//变量城市 找到有两个武士的开始战斗
	int i = 0;
	for (i = 0; i < m_nCity; i++)
	{
		if (m_pCity[i].m_used >= 2)
		{
			Warrior **p1, **p2;
			p1 = m_pCity[i].Begin();
			p2 = p1 + 1;
			if ((i+1)%2) //奇数
			{
				while (!SysFightIsOver(*p1, *p2))  //部分胜负
				{
					//红方先进攻
					if ((*p1)->m_pHeadquarter->m_Color == RED
						&& (*p2)->m_pHeadquarter->m_Color == BLUE)
					{
						(*p1)->Fight(*p2);
						if (SysFightIsOver(*p1, *p2))
							break;
						//还击
						(*p2)->Fight(*p1);
						if (SysFightIsOver(*p1, *p2))
							break;
					}
					else if ((*p1)->m_pHeadquarter->m_Color == BLUE
						&& (*p2)->m_pHeadquarter->m_Color == RED)
					{
						(*p2)->Fight(*p1);
						if (SysFightIsOver(*p1, *p2))
							break;
						//还击
						(*p1)->Fight(*p2);
						if (SysFightIsOver(*p1, *p2))
							break;						
					}
				}
				//战斗结束  将牺牲的武士清除
				Headquarter *pHeadquarter;
				if ((*p1)->GetLive() <= 0)
				{
					pHeadquarter = (*p1)->m_pHeadquarter;
					m_pCity[i].Remove(*p1);
					pHeadquarter->m_Warriorset.Remove(*p1);
					delete *p1;
				}
				else
				{
					if ((*p1)->type == DRAGON)
					{
						DispTime();
						(*p1)->Yell();
					}
				}
				if ((*p2)->GetLive() <= 0)
				{
					pHeadquarter = (*p2)->m_pHeadquarter;
					m_pCity[i].Remove(*p2);
					pHeadquarter->m_Warriorset.Remove(*p2);
					delete *p2;
				}
				else
				{
					if ((*p2)->type == DRAGON)
					{
						DispTime();
						(*p2)->Yell();
					}
				}
			}
			else
			{
				while (!SysFightIsOver(*p1, *p2))
				{
					//蓝方先攻击
					if ((*p1)->m_pHeadquarter->m_Color == BLUE
						&& (*p2)->m_pHeadquarter->m_Color == RED)
					{
						(*p1)->Fight(*p2);
						if (SysFightIsOver(*p1, *p2))
							break;
						(*p2)->Fight(*p1);
						if (SysFightIsOver(*p1, *p2))
							break;						
					}
					else if ((*p1)->m_pHeadquarter->m_Color == RED
						&& (*p2)->m_pHeadquarter->m_Color == BLUE)
					{
						(*p2)->Fight(*p1);
						if (SysFightIsOver(*p1, *p2))
							break;
						(*p1)->Fight(*p2);
						if (SysFightIsOver(*p1, *p2))
							break;
					}
				}
				//战斗结束  将牺牲的武士清除
				Headquarter *pHeadquarter;
				if ((*p1)->GetLive() <= 0)
				{
					pHeadquarter = (*p1)->m_pHeadquarter;
					m_pCity[i].Remove(*p1);
					pHeadquarter->m_Warriorset.Remove(*p1);
					delete *p1;
				}
				else
				{
					if ((*p1)->type == DRAGON)
					{
						DispTime();
						(*p1)->Yell();
					}
				}
				if ((*p2)->GetLive() <= 0)
				{
					pHeadquarter = (*p2)->m_pHeadquarter;
					m_pCity[i].Remove(*p2);
					pHeadquarter->m_Warriorset.Remove(*p2);
					delete *p2;
				}
				else
				{
					if ((*p2)->type == DRAGON)
					{
						DispTime();
						(*p2)->Yell();
					}
				}
			}
		}		
	}	
}


void SystemOP::SysReportHeader()
{
	DispTime();
	m_pRedHead->DispLive();
	DispTime();
	m_pBlueHead->DispLive();
}


void SystemOP::SysReportWarrior()
{
	//从城市编号由小到大 先显示RED 后显示BLUE
	int i = 0;
	for (i = 0; i < m_nCity; i++)
	{
		Warrior **p;
		p = m_pCity[i].Begin();
		while (*p != 0 && p != m_pCity[i].End())
		{
			if ((*p)->m_pHeadquarter->m_Color == RED)
			{
				DispTime();				
				(*p)->Report();
			}
			p++;
		}		
	}

	for (i = 0; i < m_nCity; i++)
	{
		Warrior **p;
		p = m_pCity[i].Begin();
		while (*p != 0 && p != m_pCity[i].End())
		{
			if ((*p)->m_pHeadquarter->m_Color == BLUE)
			{
				DispTime();
				(*p)->Report();
			}
			p++;
		}
	}

	//Warrior **p = m_pRedHead->m_Warriorset.REnd();// .m_pWarriorset[0];

	//if (p != NULL)
	//{
	//	while (p != m_pRedHead->m_Warriorset.Begin())
	//	{
	//		DispTime();
	//		(*p)->Report();
	//		p--;
	//	}
	//	if (p == m_pRedHead->m_Warriorset.Begin())
	//	{
	//		DispTime();
	//		(*p)->Report();
	//	}
	//}
	//
	//p = m_pBlueHead->m_Warriorset.REnd();
	//if (p != NULL)
	//{
	//	while (p != m_pBlueHead->m_Warriorset.Begin())
	//	{
	//		DispTime();
	//		(*p)->Report();
	//		p--;
	//	}
	//	if (p == m_pBlueHead->m_Warriorset.Begin())
	//	{
	//		DispTime();
	//		(*p)->Report();
	//	}
	//}
	
}

void SystemOP::SysRun()
{
	while (CheckTimeOver())
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
			m_CurMinute = 35;
			break;
		case 35: //WOLF 抢夺武器
			SysWolfRobWappon();
			m_CurMinute = 40;
			break;
		case 40: //发生战斗
			SysFight();
			m_CurMinute = 50;
			break;
		case 50: //司令部报告声明元
			SysReportHeader();
			m_CurMinute = 55;
			break;
		case 55: //武士报告武器状况
			SysReportWarrior();
			m_CurMinute = 0;
			m_CurHour++;
			break;
		}
	}
}

int main()
{
	int cnt;

	int live, nCity, nLoyalty, tEnd;
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