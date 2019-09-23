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
#define  WEAPON_NUM			10 //ÿ����ʿ���ӵ��10������

class Headquarter;
class CSword;
class CBomb;
class CArrow;
class Warrior;
///////////////////////////CWeapons//////////////////
class CWeapons
{
public:
	CWeapons(string s, WeaponType wType) : m_Name(s),m_wType(wType){};
	virtual int GetInjury(int force = 0);
	virtual int GetBackInjury(Warrior *pw, int force = 0);
	virtual int CheckWeapon();  //��������Ƿ����
	virtual int MeasureInjury(int force = 0);
	string m_Name;
	WeaponType m_wType;
};

int CWeapons::MeasureInjury(int force)
{
	return 0;
}

int CWeapons::GetInjury(int force)
{
	return MeasureInjury(force);
}

int CWeapons::GetBackInjury(Warrior *pw, int force)
{
	return 0;
}

int CWeapons::CheckWeapon(void)
{
	return 1;  //��Χ�����Ĳ�ֵ ��Χ0����������
}

class Warrior
{
public:
	Headquarter * m_pHeadquarter;  //����˾�
	WarriorType type;
	char *m_Name[WARRIOR_NUM] = { "dragon", "ninja","iceman","lion", "wolf" };
	int num;  //��ʿ���
	int m_pos;	//��ʿ����λ��
	int m_WCnt;
	int live; //����Ԫ	
	int m_force;
public:
	Warrior(WarriorType t, int l, int f, int n)
		:type(t), live(l), m_force(f), num(n)
	{
		m_pHeadquarter = NULL;
		m_WCnt = 0;
		m_usedWeapon = 0;
		m_live_rec = 0;
		m_weapon_rec = 0;
	}
	virtual ~Warrior()
	{
		int i = 0;
		while (i < m_WCnt)
		{
			if (m_owned[i] == true)
			{
				delete m_pWeapons[i];
			}
			i++;
		}
	}
	virtual void Display();	
	virtual void Yell()
	{}
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
	//�ɻ�Է�����
	void SeizedWeapons(Warrior *pw);
	void SetPos(int pos, int a_pos)
	{
		m_pos = pos;
		m_aim_pos = a_pos;
	}

	virtual void Move();
	bool DispPos();	//��ʾ��ʿ���ڵ�λ�� ����Ѿ�����Է�˾� ���� true ���򷵻� false
	void AddWeapon(CWeapons *pWeapon);
	int CanRobWeaponsCnt();
	WeaponType GetWeaponType(int idx)
	{
		return m_pWeapons[idx]->m_wType;
	}
	int GetArrowCnt(int idx) //��ָ��λ�ô���ʼ��ARROW�����ĸ���
	{
		int i = idx;
		int nArrow = 0;
		while (i < m_WCnt)
		{
			if (m_pWeapons[i]->m_wType == ARROW)
			{
				nArrow++;
			}
			else
			{
				break;
			}
			i++;
		}
		return nArrow;
	}

	void DestroyWeapon(int idx);
	void RemoveWeapon();
	CWeapons* GetWeapon(int idx);
	CWeapons* DisarmWeapon(int idx); //��е
	int Fight(Warrior *pWarrior);
	//void AttackWith(CWeapons *pWeapon, Warrior *pWarrior);
	void Injury(int dlive);
	void Report();
	bool IsStaChange(); //�ж���ʿ��ս���� ����״̬���������ı�����  ���䷵��1 ��ŷ���0
	//ս����ʼǰ��������
	int ResetWeapon()
	{
		m_usedWeapon = 0;
	}
protected:
	CWeapons *m_pWeapons[WEAPON_NUM];
	bool m_owned[WEAPON_NUM]; //��ʾ��������ӵ����� ��ֵΪflashʱ����ʾ����ӵ�д����� ��ʾ���ɻ�
	int m_usedWeapon;	
	int m_aim_pos;  //Ŀ��
	int m_live_rec; //��¼�������仯���
	int m_weapon_rec; //��¼�����仯���
};



//bool operator<(const Warrior w1, const Warrior w2)
//{
//
//	if (w1.num < w2.num)
//		return true;
//	return false;
//	
//}

//��ʿ����
class CWarriorSet
{
#define ALLOC_SIZE		(32) //ÿ�η���ռ�32
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
	~CWarriorSet()
	{
		int i = 0;
		while (i < m_used)
		{
			delete m_pWarriorset[i];
			i++;
		}
		delete [] m_pWarriorset;
	}
	void Insert(Warrior *pWarrior);
	Warrior** Begin();
	Warrior** End();
	Warrior** REnd();//�������һ����Ч��¼ ����Ϊ�շ��� NULL
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

	Headquarter(int live, int lives[], int force[], HeadquarterType color, int pos, int a_pos)
		:m_total_live(live), m_Color(color), m_pos(pos), m_aim_pos(a_pos)
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
//	CWarriorSet m_Warriorset;//���˾������µ���ʿ
	int m_pos; //˾�λ��
	int m_aim_pos; //�з�˾�λ��
protected:
	int m_total_live;
	int m_warrior_lives[WARRIOR_NUM];
	int m_warrior_force[WARRIOR_NUM];
	int m_warrior_no;		
};

class CSword : public CWeapons
{
public:
	CSword():CWeapons("sword", SWORD)
	{
		
	}
	virtual int GetInjury(int force = 0);
	virtual int MeasureInjury(int force = 0);
};

int CSword::MeasureInjury(int f)
{
	float tmp;
	tmp = f;
	tmp *= 0.2;
	return (int) tmp;
}

int CSword::GetInjury(int f)
{
	return MeasureInjury(f);
}

class CBomb : public CWeapons
{
public:
	CBomb():CWeapons("bomb", BOMB)
	{
		m_nUsed = 1;  //bomb ֻ����һ��
	}
	virtual int GetInjury(int f = 0);
	virtual int GetBackInjury(Warrior *pw, int force = 0);
	virtual int CheckWeapon();  //�������
	virtual int MeasureInjury(int force = 0);
	int m_nUsed;
};

int CBomb::CheckWeapon()
{
	return m_nUsed;
}

int CBomb::GetBackInjury(Warrior *pw, int f)
{
	if (pw->type == NINJA)
	{
		return 0;
	}
	float tmp = f;
	tmp *= 0.5;
	return (int)tmp;
}

int CBomb::MeasureInjury(int f)
{
	float tmp = f;
	tmp *= 0.4;
	return (int)tmp;
}

int CBomb::GetInjury(int f)
{
	int rsl = MeasureInjury(f);
	m_nUsed--;
	return rsl;
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
	virtual int CheckWeapon();  //�������
	virtual int MeasureInjury(int force = 0);
	int m_nUsed;  //ʹ�ô���  ��������ʹ��3�Σ��ù�3�κ�����
};

int CArrow::CheckWeapon()
{
	return m_nUsed;
}

int CArrow::MeasureInjury(int force)
{
	float tmp = force;
	tmp *= 0.3;
	return (int)tmp;
}

int CArrow::GetInjury(int f)
{
	int rsl = MeasureInjury(f);
	m_nUsed--;
	return rsl;
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
	float m_Morale;//ʿ��
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
	//iceman ÿǰ��һ�� ���ĵ�0.1������
	virtual void Move()  
	{
		float flive = live;
		flive *= 0.1;
		live -= (int)flive;		
		Warrior::Move();
	}
};

//LIONûǰ��һ�� ��Ҫ���ĵ��ҳ϶�
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

	bool JudgeRunaway()
	{
		if (m_loyalty <= 0 && m_pos != m_aim_pos)
		{
			return true;
		}
		return false;
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
	int m_loyalty;//�ҳ϶�
};

class CWolf : public Warrior
{
public:
	CWolf(int l, int f, int n) : Warrior(WOLF, l, f, n)
	{}
	virtual void Display();
	void RobWeapons(Warrior *pWarrior);
	bool CanRobWeapons(Warrior *pWarrior); //�ж��Ƿ��������
};

void CWolf::Display()
{
	Warrior::Display();
}

bool CWolf::CanRobWeapons(Warrior *pWarrior)
{
	//����̫�� 
	if (m_WCnt >= WEAPON_NUM)
	{
		return false;
	}
	//�Է�û������
	if (pWarrior->CanRobWeaponsCnt() <= 0)
	{
		return false;
	}
	return true;
}

void CWolf::RobWeapons(Warrior *pWarrior)
{
	if (m_WCnt < WEAPON_NUM)
	{
		CWeapons *pWeapon;
		int fnRob = 0;//ʵ�ʱ����ߵ���������
		int nRob = pWarrior->CanRobWeaponsCnt();
		while (nRob)
		{
			fnRob++;
			--nRob;
			pWeapon = pWarrior->DisarmWeapon(nRob);// pWarrior->RemoveWeapon(nRob);
			AddWeapon(pWeapon);
			if (m_WCnt >= WEAPON_NUM)
			{				
				break;				
			}
		}
		if (fnRob)
		{
			pWarrior->RemoveWeapon();
			if (m_pHeadquarter->m_Color == RED)
			{
				cout << " red wolf " << num << " took " << fnRob
					<< " " << pWeapon->m_Name <<
					" from blue " << pWarrior->m_Name[pWarrior->type]
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


//��ʾ��ʿ���ڵ�λ�� ����Ѿ�����Է�˾� ���� true ���򷵻� false
bool Warrior::DispPos()
{
	if (m_pos == m_aim_pos)
	{
		if (m_pHeadquarter->m_Color == RED)
			cout << " red " << m_Name[type] << " " << num
			<< " reached blue headquarter with " << live
			<< " elements and force " << m_force << endl;
		else
			cout << " blue " << m_Name[type] << " " << num
			<< " reached red headquarter with " << live
			<< " elements and force " << m_force << endl;
		return true;
	}
	else
	{
		if (m_pHeadquarter->m_Color == RED)
			cout << " red " << m_Name[type] << " " << num
			<< " marched to city " << m_pos << " with " << live
			<< " elements and force " << m_force << endl;
		else
			cout << " blue " << m_Name[type] << " " << num
			<< " marched to city " << m_pos << " with " << live
			<< " elements and force " << m_force << endl;
		return false;
	}
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
		CWeapons *pWeapon;// = m_pWeapons[1];
		int i;
		for (i = 1; i < m_WCnt; i++)
		{
			pWeapon = m_pWeapons[i];
			if (pWeapon->m_wType != wType)
			{
				return i;
			}
		}
		return i;
	}	
}

//��������
CWeapons* Warrior::DisarmWeapon(int idx)
{
	CWeapons *pWeapon = NULL;
	if (idx < m_WCnt)
	{
		pWeapon = m_pWeapons[idx];
		m_owned[idx] = false;
	}
	return pWeapon;
}

CWeapons* Warrior::GetWeapon(int idx)
{
	CWeapons *pWeapon = NULL;
	if (idx < m_WCnt)
	{
		pWeapon = m_pWeapons[idx];
	}
	return pWeapon;
}

void Warrior::RemoveWeapon()
{
	int i = 0;
	for (i = 0; i < m_WCnt; i++)
	{
		if (m_owned[i] == false) //��ʾ�Ѿ�����ӵ�д�����
		{
			int j = i+1;
			int k = i;
			for (; j < m_WCnt; j ++, k++)
			{
				m_pWeapons[k] = m_pWeapons[j];
				m_owned[k] = m_owned[j];
			}
			m_WCnt--;
			i--; //�޸�ѭ������ ��ǰֵ����һ��
		}
	}
	
}

void Warrior::DestroyWeapon(int idx)
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
		delete pWeapon;
		//���ٵ����������һ������
		if (m_usedWeapon >= m_WCnt)
		{
			m_usedWeapon = 0;
		}
	}
}
void Warrior::AddWeapon(CWeapons *pWeapon)
{
	//�������Ѿ��ź�������飬�Ȱ��������������� ���;��Ǳ��
	//����������arrow����Ҫ���ù�������ǰ��
	if (m_WCnt < WEAPON_NUM)  //
	{
		int doit = 0;
		//ӵ������������û�г������ֵ
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
					if (p1->m_nUsed <= p2->m_nUsed) //���Բ��뵽I��λ��
					{
						doit = 1;
					}
				}
				else
					doit = 1;	
				if (doit == 1)
				{
					for (int j = m_WCnt; j > i; j--)
					{
						m_pWeapons[j] = m_pWeapons[j-1];
						m_owned[j] = m_owned[j-1];
					}
					m_pWeapons[i] = pWeapon;
					m_owned[i] = true;
					m_WCnt++;
					break;
				}
			}			
		}
		if (i >= m_WCnt)  //���
		{
			m_pWeapons[i] = pWeapon;
			m_owned[i] = true;
			m_WCnt++;
		}
	}
}

//�ɻ�����
void Warrior::SeizedWeapons(Warrior *pw)
{
	if (m_WCnt < WEAPON_NUM)
	{
		CWeapons *pWeapon;
		int nWeapon = pw->m_WCnt; //���Ա��ɻ����������
		int i = 0;
		while (i < nWeapon)
		{
			if (pw->GetWeaponType(i) == ARROW)  //��ǰҪ�ɻ��������ARROW
			{
				int nArrow = pw->GetArrowCnt(i);//�ӵ�һ��Ҫ�ɻ��ARROW��ʼ��ARROW����
				if (m_WCnt+nArrow <= WEAPON_NUM) //���Խ�ARROWȫ���ɻ�
				{
					//�ɻ�ȫ��ARROW
					while (nArrow)
					{
						nArrow--;
						pWeapon = pw->DisarmWeapon(i);// pw->RemoveWeapon(i);
						AddWeapon(pWeapon);
						i++;
					}
				}
				else  //���ܽ�ȫ��ARROW�ɻ�
				{
					//�Ӻ�����ǰ�ɻ�
					int ti = i+nArrow-1; //���һ��ARROW��λ��
					while (m_WCnt < WEAPON_NUM)
					{
						pWeapon = pw->DisarmWeapon(ti);// pw->RemoveWeapon(ti);
						AddWeapon(pWeapon);
						ti--;
					}
				}
			}
			else //�������͵�����
			{
				pWeapon = pw->DisarmWeapon(i);// pw->RemoveWeapon(i);
				AddWeapon(pWeapon);
				i++;
			}
			if (m_WCnt >= WEAPON_NUM)
			{
				break;
			}
		}
		pw->RemoveWeapon();  //�����ɻ�������Ƴ���������
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

bool Warrior::IsStaChange()
{
	int i = 0;
	//����״̬�仯���
	bool weapon_sta = true; //�仯
	if (m_WCnt <= 0)
	{
		weapon_sta = false; //����
	}
	else
	{
		if (m_weapon_rec == m_usedWeapon)
		{
			CWeapons *pWeapon = m_pWeapons[m_usedWeapon];
			if (pWeapon->m_wType == SWORD)
			{
				weapon_sta = false;
			}
		}
		m_weapon_rec = m_usedWeapon;
	}

	bool live_sta = true;
	if (m_live_rec == live)
	{
		live_sta = false;
	}
	m_live_rec = live;

	return (live_sta | weapon_sta);
	/*if (live_sta && weapon_sta)
	{

	}


	while (i < m_WCnt)
	{
		CWeapons *pWeapons = m_pWeapons[i];
		if (pWeapons->MeasureInjury(m_force) < 1)
			return true;
		i++;
	}
	if (m_WCnt == 0)
		return true;
	return false;*/
}

//����0��ʾʧ�� ����1 ��ʾƽ�� ����2 ��ʾʤ�� ����3��ʾ��Ҫ����ս��
int Warrior::Fight(Warrior *pWarrior)
{
	//
	if (m_WCnt)
	{
		CWeapons *pWeapon = m_pWeapons[m_usedWeapon];
		int hurt = pWeapon->GetInjury(m_force);
		pWarrior->Injury(hurt);
		hurt = pWeapon->GetBackInjury(this, hurt);
		Injury(hurt);
		if (!pWeapon->CheckWeapon())
		{
			DestroyWeapon(m_usedWeapon);
			//RemoveWeapon(m_usedWeapon);
		}
		else
			SwitchWeapon();
	}	
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
		ptr->SetPos(m_pos, m_aim_pos);
		//����ʿ�������
		//m_Warriorset.Insert(ptr);
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
	RedHeadquarter(int live, int lives[], int forces[], int pos, int a_pos) 
		:Headquarter(live, lives, forces, RED, pos, a_pos)
	{
		m_nextwarrior = ICEMAN;//iceman��lion��wolf��ninja��dragon	
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
	BlueHeadquarter(int live, int lives[], int forces[], int pos, int a_pos) 
		:Headquarter(live, lives, forces, BLUE, pos, a_pos)
	{
		m_nextwarrior = LION; //lion��dragon��ninja��iceman��wolf		
	};

	Warrior*  CreateWarrior();
	void DispLive()
	{
		cout << " " << m_total_live << " elements in blue headquarter" << endl;
	}
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
	void Release(); //����
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
	bool SysLionRunaway(Warrior *pw);
	void SysCheckTakeover(int pos);
	bool m_game_is_over;
};

void SystemOP::Init(int nCity, int nLoy, int nSyslive, int nMinutes, int *pLive,
	int *pAttack)
{
	m_nCity = nCity+2;
	m_nLoyalty = nLoy;
	m_nSysLive = nSyslive;
	m_CurHour = 0;
	m_CurMinute = 0;
	m_SysMinutes = nMinutes;
	m_pLiveWarrior = pLive;
	m_pAttack = pAttack;
	g_loy_use = m_nLoyalty;
	m_pCity = new CWarriorSet[m_nCity];  //������˾�Ҳ���ų���
	m_pRedHead = new RedHeadquarter(m_nSysLive, m_pLiveWarrior, m_pAttack, 0, m_nCity-1);
	m_pBlueHead = new BlueHeadquarter(m_nSysLive, m_pLiveWarrior, m_pAttack, m_nCity-1, 0);
	m_game_is_over = false;
}

void SystemOP::Release() //����
{
	delete[]m_pCity;
	delete m_pRedHead;
	delete m_pBlueHead;
}

bool SystemOP::CheckTimeOver()
{
	int total = m_CurHour * 60 + m_CurMinute;
	if (total > m_SysMinutes)
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
		//����˾�
		m_pCity[pWarrior->m_pos].Insert(pWarrior);
	}
		
	if (m_pBlueHead->CanCreateWarrior(m_pBlueHead->m_nextwarrior))
	{
		pWarrior = m_pBlueHead->CreateWarrior();
		DispTime();
		pWarrior->Display();
		m_pCity[pWarrior->m_pos].Insert(pWarrior);
	}
}


bool SystemOP::SysLionRunaway(Warrior *pw)
{
	CLion *pLion = (CLion*)pw;
	if (pLion->JudgeRunaway() == true)
	{
		DispTime();
		pLion->Runaway();
		m_pCity[pLion->m_pos].Remove(pw);
		//m_pRedHead->m_Warriorset.Remove(pw);
		delete pLion;
		return true;
	}
	return false;
}

void SystemOP::SysCheckLion()
{
	//�������� ����˾�
	for (int i = 0; i < m_nCity; i++)
	{
		Warrior **pw1, **pw2;	
		switch (m_pCity[i].m_used)
		{
		default:
			break;
		case 1:
			pw1 = m_pCity[i].Begin();
			if ((*pw1)->type == LION)
			{
				SysLionRunaway(*pw1);
			}
			break;
		case 2:
			pw1 = m_pCity[i].Begin();
			pw2 = pw1 + 1;
			if ((*pw1)->type == LION && (*pw2)->type != LION)
			{
				SysLionRunaway(*pw1);
			}
			else if ((*pw1)->type != LION && (*pw2)->type == LION)
			{
				SysLionRunaway(*pw2);
			}
			else if ((*pw1)->type == LION && (*pw2)->type == LION)
			{
				if ((*pw1)->m_pHeadquarter->m_Color == RED)
				{
					SysLionRunaway(*pw1);
					pw1 = m_pCity[i].Begin();
					SysLionRunaway(*pw1);
				}
				else
				{
					SysLionRunaway(*pw2);
					SysLionRunaway(*pw1);
				}
			}			
			break;			
		}
	}
}

void SystemOP::SysWarriorMove()
{
	int i;
	//RED move
	for (i = m_nCity-2; i >= 0; i--)
	{
		Warrior **pw1, **pw2;
		if (m_pCity[i].m_used)
		{
			Warrior *pw;
			switch (m_pCity[i].m_used)
			{
			default:
				break;
			case 1:
				pw1 = m_pCity[i].Begin();
				if ((*pw1)->m_pHeadquarter->m_Color == RED)
				{
					pw = *pw1;
					m_pCity[(*pw1)->m_pos].Remove(*pw1);
					pw->Move();
					m_pCity[pw->m_pos].Insert(pw);
				}
				
				break;
			case 2:
				pw1 = m_pCity[i].Begin();
				if ((*pw1)->m_pHeadquarter->m_Color != RED)
				{
					pw1++;					
				}
				pw = *pw1;
				m_pCity[(*pw1)->m_pos].Remove(*pw1);
				pw->Move();
				m_pCity[pw->m_pos].Insert(pw);
				break;
			}
		}
	}
	//blue
	for (i = 1; i < m_nCity; i++)
	{
		Warrior **pw1, **pw2;
		if (m_pCity[i].m_used)
		{
			Warrior *pw;
			switch (m_pCity[i].m_used)
			{
			default:
				break;
			case 1:
				pw1 = m_pCity[i].Begin();
				if ((*pw1)->m_pHeadquarter->m_Color == BLUE)
				{
					pw = *pw1;
					m_pCity[(*pw1)->m_pos].Remove(*pw1);
					pw->Move();
					m_pCity[pw->m_pos].Insert(pw);
				}

				break;
			case 2:
				pw1 = m_pCity[i].Begin();
				if ((*pw1)->m_pHeadquarter->m_Color != BLUE)
				{
					pw1++;
				}
				pw = *pw1;
				m_pCity[(*pw1)->m_pos].Remove(*pw1);
				pw->Move();
				m_pCity[pw->m_pos].Insert(pw);
				break;
			}
		}
	}

	//���λ����Ϣ
	for (i = 0; i < m_nCity; i++)
	{
		Warrior **pw1, **pw2;
		switch (m_pCity[i].m_used)
		{
		default:
			break;
		case 1:
			pw1 = m_pCity[i].Begin();
			DispTime();
			if ((*pw1)->DispPos())
				SysCheckTakeover((*pw1)->m_pos);
			break;
		case 2:
			pw1 = m_pCity[i].Begin();
			pw2 = pw1 + 1;
			if ((*pw1)->m_pHeadquarter->m_Color == RED)
			{
				DispTime();
				if ((*pw1)->DispPos())
					SysCheckTakeover((*pw1)->m_pos);
				DispTime();
				if ((*pw2)->DispPos())
					SysCheckTakeover((*pw2)->m_pos);
			}
			else
			{
				DispTime();
				if((*pw2)->DispPos())
					SysCheckTakeover((*pw2)->m_pos);
				DispTime();
				if ((*pw1)->DispPos())
					SysCheckTakeover((*pw1)->m_pos);
			}
		}		
	}
	
}

void SystemOP::SysCheckTakeover(int pos)
{
	//�ж�˾��Ƿ�ռ��
	if (m_pRedHead->m_pos == pos)
	{
		DispTime();
		cout << " red headquarter was taken" << endl;
		m_game_is_over = true;
	}
	if (m_pBlueHead->m_pos == pos)
	{
		DispTime();
		cout << " blue headquarter was taken" << endl;
		m_game_is_over = true;

	}
	/*if (m_pCity[m_pRedHead->m_pos].m_used)
	{
		DispTime();
		cout << " red headquarter was taken" << endl;
		m_game_is_over = true;
	}
	if (m_pCity[m_pBlueHead->m_pos].m_used)
	{
		DispTime();
		cout << " blue headquarter was taken" << endl;
		m_game_is_over = true;
	}*/
}

void SystemOP::SysWolfRobWappon()
{
	//�����б���
	int i = 0;
	for (i = 1; i < m_nCity-1; i++)
	{
		if (m_pCity[i].m_used >= 2)
		{
			Warrior **p1, **p2;
			CWolf *pWolf;
			p1 = m_pCity[i].Begin();
			p2 = p1 + 1;
			//������ʿ������һ��WOLF��WOLF������Է�������
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
}


bool SystemOP::SysFightIsOver(Warrior *pw1, Warrior *pw2)
{
	//1һ���Ѿ�����
	if (pw1->live > 0 && pw2->live <= 0)
	{
		//����ʧ�ܷ�������
		pw1->SeizedWeapons(pw2);
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " red " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " killed blue " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " in city " << pw1->m_pos
				<< " remaining " << pw1->live << " elements" << endl;
		}
		else
		{
			cout << " blue " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " killed red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " in city " << pw1->m_pos
				<< " remaining " << pw1->live << " elements" << endl;
		}
		return true;
	}
	else if (pw1->live <= 0 && pw2->live > 0)
	{
		//����ʧ�ܷ�������
		pw2->SeizedWeapons(pw1);
		DispTime();
		if (pw2->m_pHeadquarter->m_Color == RED)
		{
			cout << " red " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " killed blue " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " in city " << pw2->m_pos
				<< " remaining " << pw2->live << " elements" << endl;
		}
		else
		{
			cout << " blue " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " killed red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " in city " << pw2->m_pos
				<< " remaining " << pw2->live << " elements" << endl;
		}
		return true;
	}
	//2 �Ϸ�������
	if (pw1->live <= 0 && pw2->live <= 0)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " and blue " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " died in city " << pw1->m_pos << endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type] << " " << pw2->num
				<< " and blue " << pw1->m_Name[pw1->type] << " " << pw1->num
				<< " died in city " << pw2->m_pos << endl;
		}
		return true;
	}
	//3˫����û������ ����ս��
	if (pw1->m_WCnt == 0 &&	pw2->m_WCnt == 0)
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " and blue " <<
				pw2->m_Name[pw2->type] << " " << pw2->num
				<< " were alive in " << "city " << pw1->m_pos
				<< endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " and blue " <<
				pw1->m_Name[pw1->type] << " " << pw1->num
				<< " were alive in " << "city " << pw1->m_pos
				<< endl;
		}
		return true;
	}	
	//4�ж�������ʿ֮���ս�����м�����ȥ�ı�Ҫ��  ˫�����е�����������̫�� ���ܶԶԷ�����˺�
	if ((!pw1->IsStaChange()) && (!pw2->IsStaChange()))
	{
		DispTime();
		if (pw1->m_pHeadquarter->m_Color == RED)
		{
			cout << " both red " << pw1->m_Name[pw1->type]
				<< " " << pw1->num << " and blue " <<
				pw2->m_Name[pw2->type] << " " << pw2->num
				<< " were alive in " << "city " << pw1->m_pos
				<< endl;
		}
		else
		{
			cout << " both red " << pw2->m_Name[pw2->type]
				<< " " << pw2->num << " and blue " <<
				pw1->m_Name[pw1->type] << " " << pw1->num
				<< " were alive in " << "city " << pw1->m_pos
				<< endl;
		}
		return true;
	}
	return false;  //û�зֳ�ʤ��
}

void SystemOP::SysFight()  
{
	//�������� �ҵ���������ʿ�Ŀ�ʼս��
	int i = 0;
	bool fight = true;
	for (i = 1; i < m_nCity-1; i++)
	{		
		fight = true;
		if (m_pCity[i].m_used >= 2)
		{
			Warrior **p1, **p2;
			p1 = m_pCity[i].Begin();
			p2 = p1 + 1;
			(*p1)->ResetWeapon();
			(*p2)->ResetWeapon();
			if (i%2) //����
			{
			//	while (!SysFightIsOver(*p1, *p2))  //����ʤ��
				while (fight)// !SysFightIsOver(*p1, *p2))  //����ʤ��
				{
					//�췽�Ƚ���
					if ((*p1)->m_pHeadquarter->m_Color == RED
						&& (*p2)->m_pHeadquarter->m_Color == BLUE)
					{
						(*p1)->Fight(*p2);
						if ((*p2)->live > 0) //����
							(*p2)->Fight(*p1);
						fight = !SysFightIsOver(*p1, *p2);
					}
					else if ((*p1)->m_pHeadquarter->m_Color == BLUE
						&& (*p2)->m_pHeadquarter->m_Color == RED)
					{
						(*p2)->Fight(*p1);
						if ((*p1)->live > 0)
							(*p1)->Fight(*p2);
						fight = !SysFightIsOver(*p1, *p2);								
					}
				}
				//ս������  ����������ʿ���
				Headquarter *pHeadquarter;
				Warrior *pw;
				if ((*p1)->live <= 0)
				{
					pHeadquarter = (*p1)->m_pHeadquarter;
					pw = *p1;
					m_pCity[i].Remove(*p1);
				//	pHeadquarter->m_Warriorset.Remove(pw);
					delete pw;
				}
				else
				{
					if ((*p1)->type == DRAGON)
					{
						DispTime();
						(*p1)->Yell();
					}
				}
				if ((*p2)->live <= 0)
				{
					pHeadquarter = (*p2)->m_pHeadquarter;
					pw = *p2;
					m_pCity[i].Remove(*p2);
				//	pHeadquarter->m_Warriorset.Remove(pw);
					delete pw;
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
				while (fight)
				{
					//�����ȹ���
					if ((*p1)->m_pHeadquarter->m_Color == BLUE
						&& (*p2)->m_pHeadquarter->m_Color == RED)
					{
						(*p1)->Fight(*p2);
						if ((*p2)->live > 0) //����
							(*p2)->Fight(*p1);
						fight = !SysFightIsOver(*p1, *p2);							
					}
					else if ((*p1)->m_pHeadquarter->m_Color == RED
						&& (*p2)->m_pHeadquarter->m_Color == BLUE)
					{
						(*p2)->Fight(*p1);
						if ((*p1)->live > 0)
							(*p1)->Fight(*p2);
						fight = !SysFightIsOver(*p1, *p2);						
					}
				}
				//ս������  ����������ʿ���
				Headquarter *pHeadquarter;
				Warrior *pw;
				if ((*p1)->live <= 0)
				{
					pHeadquarter = (*p1)->m_pHeadquarter;
					pw = *p1;
					m_pCity[i].Remove(*p1);
			//		pHeadquarter->m_Warriorset.Remove(pw);
					delete (pw);
				}
				else
				{
					if ((*p1)->type == DRAGON)
					{
						DispTime();
						(*p1)->Yell();
					}
				}
				if ((*p2)->live <= 0)
				{
					pHeadquarter = (*p2)->m_pHeadquarter;
					pw = *p2;
					m_pCity[i].Remove(*p2);
			//		pHeadquarter->m_Warriorset.Remove(pw);
					delete pw;
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
	//�ӳ��б����С���� ����ʾRED ����ʾBLUE
	int i = 0;
	for (i = 1; i < m_nCity-1; i++)
	{
		if (m_pCity[i].m_used <= 0)
		{
			continue;
		}
		if (m_pCity[i].m_used >= 2)
		{
			Warrior **p1, **p2;
			p1 = m_pCity[i].Begin();
			p2 = p1 + 1;
			if ((*p1)->m_pHeadquarter->m_Color == RED)
			{
				DispTime();
				(*p1)->Report();
				DispTime();
				(*p2)->Report();
			}
			else
			{
				DispTime();
				(*p2)->Report();
				DispTime();
				(*p1)->Report();
			}
		}
		else
		{
			Warrior **p = m_pCity[i].Begin();
			DispTime();
			(*p)->Report();
		}
	}		
}

void SystemOP::SysRun()
{
	while (CheckTimeOver()&&!m_game_is_over)
	{
		switch (m_CurMinute)
		{
		default:
			break;
		case 0:   //ÿСʱ0�� ������ʿ
			SysCreateWarrior();
			m_CurMinute = 5;
			break;
		case 5:  //lion ����ʱ��
			SysCheckLion();
			m_CurMinute = 10;
			break;
		case 10:  //��ʿǰ��
			SysWarriorMove();
			m_CurMinute = 35;
			break;
		case 35: //WOLF ��������
			SysWolfRobWappon();
			m_CurMinute = 40;
			break;
		case 40: //����ս��
			SysFight();
			m_CurMinute = 50;
			break;
		case 50: //˾���������Ԫ
			SysReportHeader();
			m_CurMinute = 55;
			break;
		case 55: //��ʿ��������״��
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
		//��ʿ����ʱ�Ĺ�����
		for (int j = 0; j < WARRIOR_NUM; j++)
		{
			cin >> attack_live[j];
		}


		SystemOP sysOp;	
		sysOp.Init(nCity, nLoyalty, live, tEnd, live_warrior, attack_live);
				
		cout << "Case " << i + 1 << ":" << endl;		
		sysOp.SysRun();
		sysOp.Release();
	}
		
	return 0;
}