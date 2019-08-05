#include <iostream>
#include <cstring>
using namespace std;

class Array2 {

	// 在此处补充你的代码
public:
	int row, col;
	int *ptr;
public:
	Array2(int r, int c):row(r), col(c)
	{
		if (c*r != 0)
		{
			ptr = new int[r*c];
		}
		else
			ptr = NULL;
	}
	~Array2()
	{
		if (ptr)
		{
			delete[] ptr;
		}
	}
	Array2()
	{
		row = col = 0;
	}

	int* operator[](int i) 
	{
		return ptr+col*i;
	}

	int operator()(int r, int c)
	{
		return *(ptr + r * col + c);
	}

	Array2& operator=(Array2 a)
	{
		if (a.ptr != ptr)
		{
			row = a.row;
			col = a.col;
		}
		if (ptr != NULL)
		{
			delete[] ptr;
		}
		ptr = new int[row*col];
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				*(ptr + i * col + j) = *(a.ptr + i * col + j);
			}
		}
		return *this;
	}

};

int main() {
	Array2 a(3, 4);
	int i, j;
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 4; j++)
			//第一个[]调用Array2的重载运算符
			//第二个[]调用的是int的[] 运算符
			a[i][j] = i * 4 + j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; j++) {
			cout << a(i, j) << ",";
		}
		cout << endl;
	}
	cout << "next" << endl;
	Array2 b;     b = a;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; j++) {
			cout << b[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}