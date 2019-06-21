#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	::MessageBox(NULL, "Hello, Win32Application", "WinAppDemo", MB_OK);
	return 0;
}