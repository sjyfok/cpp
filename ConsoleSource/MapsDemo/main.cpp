#include <iostream>
#include   "_afxcoll.h"
#include <process.h>

using namespace std;





int main(void)
{
	CMapPtrToPtr map;
	char szDay[][16] = { "Sunday", "Monday", "Tuesday", "Wednesdy", "Thursday", "Friday", "Saturday" };
	map[szDay[0]] = (void*)"星期日";
	map[szDay[1]] = (void*)"星期一";
	map[szDay[2]] = (void*)"星期二";
	map[szDay[3]] = (void*)"星期三";
	map[szDay[4]] = (void*)"星期四";
	map[szDay[5]] = (void*)"星期五";
	map[szDay[6]] = (void*)"星期六";
	cout << szDay[4] << ": " << (char *)map[szDay[4]] << endl;
	system("pause");
	return 0;
}

