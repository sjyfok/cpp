#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {

	// �ڴ˴�������Ĵ���
private:
	string m_name;
	int m_age;
	string m_number;
	int m_firstyear;
	int m_secondyear;
	int m_thirdyear;
	int m_fouryear;
	float m_avg;
public:

	void input()
	{
		char m;
		getline(cin, m_name, ',');
		cin >> m_age;
		while (cin.get() != ',') {};
		getline(cin, m_number, ',');	
		cin >> m_firstyear;
		while (cin.get() != ',') {};
		cin >> m_secondyear;
		while (cin.get() != ',') {};
		cin >> m_thirdyear;
		while (cin.get() != ',') {};
		cin >> m_fouryear;
	}

	void calculate()
	{
		float sum;
		sum = m_firstyear + m_secondyear + m_thirdyear + m_fouryear;
		m_avg = sum / 4;
	}

	void output()
	{

		cout << m_name << "," << m_age
			<< "," << m_number << ","
			<< m_avg << endl;
	}
};





int main() {
	Student student;        // ������Ķ���
	student.input();        // ��������
	student.calculate();    // ����ƽ���ɼ�
	student.output();       // �������
	return 0;
}