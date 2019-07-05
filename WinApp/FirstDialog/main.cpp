#include <Windows.h>
#include "Project1/resource.h"

BOOL __stdcall DlgProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int nResult = ::DialogBoxParam(
		hInstance,
		(LPCTSTR)IDD_MAIN,
		NULL,
		(DLGPROC)DlgProc,
		NULL
	);
	if (nResult == IDOK)
	{
		::MessageBox(NULL, "�û�ѡ����ȷ����ť", "First Dialog", MB_OK);
	}
	else
	{
		::MessageBox(NULL, "�û�ѡ����ȡ����ť", "First Dialog", MB_OK);
	}
}

BOOL __stdcall DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	default:
		break;
	case WM_INITDIALOG:
		::SetWindowText(hDlg, "First Dialog!");
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			break;
		case IDOK:
			::EndDialog(hDlg, IDOK);
			break;
		case IDCANCEL:
			::EndDialog(hDlg, IDCANCEL);
			break;
		}
		break;
	}
	return 0;
}

