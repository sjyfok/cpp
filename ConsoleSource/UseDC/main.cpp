#include <Windows.h>

//需要先打开记事本程序 并且打开一个无标题的空文件
int main(int argc, char *argv[])
{
	HDC hdc;

	HWND hWnd = ::FindWindow(NULL, "无标题 - 记事本");
	char sz[] = "大家好";
	while (::IsWindow(hWnd))
	{
		hdc = GetDC(hWnd);
		::TextOut(hdc, 10, 10, sz, strlen(sz));
		::ReleaseDC(hWnd, NULL);
		Sleep(1000);
	}
	::MessageBox(NULL, "记事本程序已经退出", NULL, MB_OK);



	return 0;
}