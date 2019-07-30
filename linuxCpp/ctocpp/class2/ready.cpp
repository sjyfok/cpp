#include <iostream>
using namespace std;

enum SamuraiType
{
	DRAGON = 0,
	NINJA,
	ICEMAN,
	LION,
	WOLF,
};

class Samurai
{
public:
	SamuraiType type;
	Samurai(SamuraiType t, int l) :type(t), live(l) {}
private:
	int num;
	int live; //ÉùÃ÷Ôª
};




class Commander
{
	
public:
	static int time;
	Samurai*  CreateSamurai(SamuraiType type);
	Commander(int live, int dragon, int ninja,
		int iceman, int lion, int wolf) :total_live(live),
		live_dragon(dragon), live_ninja(ninja), live_iceman(iceman),
		live_lion(lion), live_wolf(wolf)
	{}
	int CanCreateSamurai();
private:
	int total_live;
	int live_dragon, live_ninja, live_iceman,
		live_lion, live_wolf;
};

Samurai* Commander::CreateSamurai(SamuraiType type)
{
	Samurai *ptr;
	switch (type)
	{
	case DRAGON:
		ptr = new Samurai(type, live_dragon);
		break;
	case NINJA:
		ptr = new Samurai(type, live_ninja);
		break;
	case ICEMAN:
		ptr = new Samurai(type, live_iceman);
		break;
	case LION :
		ptr = new Samurai(type, live_lion);
		break;
	case WOLF:
		ptr = new Samurai(type, live_wolf);
		break;
	default:
		break;
	} 
	return ptr;
}

int Commander::CanCreateSamurai()
{
	if (total_live >= live_dragon)
	{
		return 1;
	}
	else if (total_live >= live_ninja)
	{
		return 1;
	}
	else if (total_live >= live_iceman)
	{
		return 1;
	}
	else if (total_live >= live_lion)
	{
		return 1;
	}
	else if (total_live >= live_wolf)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class RedCommander : public Commander
{
public:
	RedCommander(int live, int live_dragon, int live_ninja,
		int live_iceman, int live_lion, int live_wolf) :Commander(live, live_dragon, live_ninja,
			live_iceman, live_lion, live_wolf) {};

};

class BlueCommander : public Commander
{

};






int main()
{
	int cnt;
	int live;
	int live_dragon, live_ninja, live_iceman,
		live_lion, live_wolf;
	
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		cin >> live;
		cin >> live_dragon >> live_ninja >> live_iceman >> live_lion
			>> live_wolf;
		RedCommander *pRed = new RedCommander(live, live_dragon, live_ninja,
			live_iceman, live_lion, live_wolf);
		while (pRed->CanCreateSamurai())
		{
			pRed->CraeteSamurai();
		}
	}

}