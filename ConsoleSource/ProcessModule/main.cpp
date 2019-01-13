#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>


using namespace std;

int main(void)
{
	MODULEENTRY32 me32 = { 0 };
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	me32.dwSize = sizeof(MODULEENTRY32);
	if (::Module32First(hModuleSnap, &me32))
	{
		do
		{
			cout << me32.szExePath << "\n";
			cout << " 模块在本进程中的地址: " << me32.hModule << "\n";
		} while (::Module32Next(hModuleSnap, &me32));
	}
	::CloseHandle(hModuleSnap);
	system("pause");
	return 0;
}

