#include <Windows.h>

int main(int argc, char *argv[])
{
	HWND hWnd = ::FindWindow(NULL, "�ޱ��� - ���±�");
	if (hWnd != NULL)
	{
		::SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
	return 0;
}