#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

// �ڴ˴�������Ĵ���
template <class Key, class T, class Pred = greater<Key>>
class MyMultimap :public multimap<Key, T, Pred>
{
public:
	void Set(Key k, T v)
	{
		typename multimap<Key, T, Pred>::iterator p;
		p = this->begin();
		while (p != this->end())
		{
			if (p->first == k)
				p->second = v;
			p++;
		}
	}
	/*
	void Set(string k, int v)
	{
		MyMultimap<string, int>::iterator p = this->begin();
		while (p != this->end())
		{
			if (p->first == k)
			p->second = v;
			p++;
		}
	}

	void Set(int k, string v)
	{
		MyMultimap<int, string>::iterator p = this->begin();
		while (p != this->end())
		{
			if (p->first == k)
				p->second = v;
			p++;
		}
	}*/
};

template <class F, class S>
ostream& operator<<(ostream& os, pair<F, S> &s)
{
	os << "(" << s.first << "," << s.second << ")";
	return os;
}

struct Student
{
	string name;
	int score;
};
template <class T>
void Print(T first, T last) {
	for (; first != last; ++first)
		cout << *first << ",";
	cout << endl;
}
int main()
{

	Student s[] = { { "Tom",80 },{ "Jack",70 },
	{ "Jone",90 },{ "Tom",70 },{ "Alice",100 } };

	MyMultimap<string, int> mp;
	for (int i = 0; i<5; ++i)
		mp.insert(make_pair(s[i].name, s[i].score));
	Print(mp.begin(), mp.end()); //�������Ӵ�С���

	mp.Set("Tom", 78); //��������Ϊ"Tom"��ѧ���ĳɼ�������Ϊ78
	Print(mp.begin(), mp.end());



	MyMultimap<int, string, less<int> > mp2;
	for (int i = 0; i<5; ++i)
		mp2.insert(make_pair(s[i].score, s[i].name));

	Print(mp2.begin(), mp2.end()); //���ɼ���С�������
	mp2.Set(70, "Error");          //�����гɼ�Ϊ70��ѧ�������ֶ���Ϊ"Error"
	Print(mp2.begin(), mp2.end());
	cout << "******" << endl;

	mp.clear();

	string name;
	string cmd;
	int score;
	while (cin >> cmd) {
		if (cmd == "A") {
			cin >> name >> score;
			if (mp.find(name) != mp.end()) {
				cout << "erroe" << endl;
			}
			mp.insert(make_pair(name, score));
		}
		else if (cmd == "Q") {
			cin >> name;
			MyMultimap<string, int>::iterator p = mp.find(name);
			if (p != mp.end()) {
				cout << p->second << endl;
			}
			else {
				cout << "Not Found" << endl;
			}
		}
	}
	return 0;
}