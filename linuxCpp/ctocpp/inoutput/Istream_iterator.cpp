#include <iostream>
#include <string>


using namespace std;
template <class T>
class CMyistream_iterator
{

	// 在此处补充你的代码
public:
	CMyistream_iterator(istream &is):m_is(is)
	{
		m_is >> m_Val;
	}
	T operator*()
	{
		return m_Val;
	}

	//后缀
	void operator++(int)
	{
		m_is >> m_Val;
	}
private:
	T m_Val;
	istream & m_is;
};




int main()
{
	int t;
	cin >> t;
	while (t--) {
		CMyistream_iterator<int> inputInt(cin);
		int n1, n2, n3;
		n1 = *inputInt; //读入 n1
		int tmp = *inputInt;
		cout << tmp << endl;
		inputInt++;
		n2 = *inputInt; //读入 n2
		inputInt++;
		n3 = *inputInt; //读入 n3
		cout << n1 << " " << n2 << " " << n3 << " ";
		CMyistream_iterator<string> inputStr(cin);
		string s1, s2;
		s1 = *inputStr;
		inputStr++;
		s2 = *inputStr;
		cout << s1 << " " << s2 << endl;
	}
	return 0;
}