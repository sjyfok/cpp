#ifndef __RTTI_H__

class CBoy
{
public:
	CBoy();
	~CBoy();
public:
	const int *GetRunTimeClass()
	{
		return &classCBoy;
	}
	static const int classCBoy;
private:

};

const int CBoy::classCBoy = 1;

CBoy::CBoy()
{
}

CBoy::~CBoy()
{
}

class CGirl
{
public:
public:
	const int *GetRuntimeClass()
	{
		return &classCGirl;
	}
	static const int classCGirl;
};
#endif // !__RTTI_H__
