///////////////////////////////////////////////////////////////
// 02MemRepair.cppÎÄ¼ş

#include <iostream>


using namespace std;

int g_nNum;

int main(int argc, char * argv[])
{
	int i = 198;
	g_nNum = 1003;
	while (true)
	{
		cout << "i = " << ++i << "\t" << "addr = " <<  &i << "\t"
			<< "g_nNum = " << --g_nNum << "\t" << "addr = " << &g_nNum 
			<< endl;
		getchar();
	}

	return 0;
}