#include <iostream>
using namespace std;
class MyCin
{

	// 在此处补充你的代码
public:
	MyCin& operator>>(int &n)
	{
		if (this->m_Sta == false)
		{
			return *this;
		}
		cin >> n;
		if (n == -1)
		{
			this->m_Sta = false;
		}
		else
		{
			this->m_Sta = true;
		}
			
		return *this;
	}

	operator bool()
	{
		return m_Sta;
	}
	MyCin()
	{
		m_Sta = true;
	}
private: 
	bool m_Sta;
};

int main()
{
	MyCin m;
	int n1, n2;
	while (m >> n1 >> n2)
		cout << n1 << " " << n2 << endl;
	return 0;
}