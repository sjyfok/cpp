#include <Windows.h>

//��Ҫ�ȴ򿪼��±����� ���Ҵ�һ���ޱ���Ŀ��ļ�
int main(int argc, char *argv[])
{
	HDC hdc;

	HWND hWnd = ::FindWindow(NULL, "�ޱ��� - ���±�");
	char sz[] = "��Һ�";
	while (::IsWindow(hWnd))
	{
		hdc = GetDC(hWnd);
		::TextOut(hdc, 10, 10, sz, strlen(sz));
		::ReleaseDC(hWnd, NULL);
		Sleep(1000);
	}
	::MessageBox(NULL, "���±������Ѿ��˳�", NULL, MB_OK);



	return 0;
}