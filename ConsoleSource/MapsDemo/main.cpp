#include <iostream>
#include   "_afxcoll.h"
#include <process.h>

using namespace std;





int main(void)
{
	CMapPtrToPtr map;
	char szDay[][16] = { "Sunday", "Monday", "Tuesday", "Wednesdy", "Thursday", "Friday", "Saturday" };
	map[szDay[0]] = (void*)"������";
	map[szDay[1]] = (void*)"����һ";
	map[szDay[2]] = (void*)"���ڶ�";
	map[szDay[3]] = (void*)"������";
	map[szDay[4]] = (void*)"������";
	map[szDay[5]] = (void*)"������";
	map[szDay[6]] = (void*)"������";
	cout << szDay[4] << ": " << (char *)map[szDay[4]] << endl;
	system("pause");
	return 0;
}

