#include <Windows.h>
#include <iostream>
//#include <process.h>
//#include "../wincommon/_afxwin.h"
//#include "../wincommon/_afxtls.h"

using namespace std;


int main(int argc, char *argv[])
{
	char szFileName[] = "C:\\Program Files\\*.*";

	WIN32_FIND_DATA findData;
	HANDLE	hFindFile;
	hFindFile = ::FindFirstFile(szFileName, &findData);
	if (hFindFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.cFileName[0] == '.')
				continue;
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				printf("%s\n", findData.cFileName);
		} while (::FindNextFile(hFindFile, &findData));
		::FindClose(hFindFile);
	}
	return 0;
}