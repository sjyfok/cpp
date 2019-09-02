#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
	// �ڴ˴�������Ĵ���
private:
	int m_3drow;
	
public:
	class CArray2D
	{
	public:
		int row, col;
		T *pData;
		CArray2D(int r, int c):row(r),col(c)
		{
			if (r*c)
				pData = new T[r*c];
			else
				pData = NULL;
		}
		CArray2D()
		{}
		~CArray2D()
		{
			if (pData)
			{
				delete[] pData;
			}
		}
		void Init(int r, int c)
		{
			row = r;
			col = c;
			if (r*c)
				pData = new T[r*c];
			else
				pData = NULL;
		}
		T* operator[](int i)
		{
			return pData + col * i;
		}
		operator void*()
		{
			return this->pData;
		}
	};
	CArray2D *m_pData;
	CArray3D(int x, int y, int z)
	{
		m_pData = new CArray2D[x];// (y, z);
		m_3drow = x;
		for (int i = 0; i < x; i++)
		{
			m_pData[i].Init(y, z);			
		}
	}
	~CArray3D()
	{
		if (m_pData)
			delete[] m_pData;
	}
	CArray2D& operator[](int i)
	{
		return *(m_pData + i);
	}
};

CArray3D<int> a(3, 4, 5);
CArray3D<double> b(3, 2, 2);
void PrintA()
{
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
			cout << endl;
		}
	}
}
void PrintB()
{
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k)
				cout << b[i][j][k] << ",";
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for (int i = 0; i < 3; ++i) {
		a[i];
		for (int j = 0; j < 4; ++j) {
			a[j][i];
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
			a[j][i][i];
		}
	}
	PrintA();
	memset(a[1], -1, 20 * sizeof(int));
	memset(a[1], -1, 20 * sizeof(int));
	PrintA();
	memset(a[1][1], 0, 5 * sizeof(int));
	PrintA();

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				b[i][j][k] = 10.0 / (i + j + k + 1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;

	return 0;
}