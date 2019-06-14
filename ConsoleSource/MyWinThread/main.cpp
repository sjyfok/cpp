#include <iostream>
#include <process.h>
#include "afxwin.h"
#include "afxtls.h"

using namespace std;


UINT MyFunc(LPVOID lpParam)
{
	printf("Thread Identify: %d\n", AfxGetThread()->m_nThreadID);
	//cout << "Thread Identify: " << AfxGetThread()->m_nThreadID << endl;

	return 0;
}

int main(void)
{
	
	for (int i = 0; i < 10; i++)
	{
		AfxBeginThread(MyFunc, NULL);
	
	}
	system("pause");
	return 0;
}

