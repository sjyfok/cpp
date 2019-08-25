#include <iostream>
#include <string>


using namespace std;
template <class T>
class CMyistream_iterator
{

	// �ڴ˴�������Ĵ���
public:
	CMyistream_iterator(istream &is):m_is(is)
	{
		m_is >> m_Val;
	}
	T operator*()
	{
		return m_Val;
	}

	//��׺
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
		n1 = *inputInt; //���� n1
		int tmp = *inputInt;
		cout << tmp << endl;
		inputInt++;
		n2 = *inputInt; //���� n2
		inputInt++;
		n3 = *inputInt; //���� n3
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