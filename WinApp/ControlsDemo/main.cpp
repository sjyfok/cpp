#include <Windows.h>
#include "Project1/resource.h"

BOOL __stdcall DlgProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP g_hBitmap1;
HBITMAP g_hBitmap2;
HICON g_hIcon;
HBRUSH g_hBgBrush;

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	g_hBitmap1 = ::LoadBitmap(hInstance, (LPCSTR)IDB_BITMAP1);
	g_hBitmap2 = ::LoadBitmap(hInstance, (LPCSTR)IDB_BITMAP2);
	g_hIcon = ::LoadIcon(hInstance, (LPCSTR)IDI_MAIN);
	g_hBgBrush = ::CreateSolidBrush(RGB(0xa6, 0xca, 0xf0));
	int nResult = ::DialogBoxParam(
		hInstance,
		(LPCTSTR)IDD_MAIN,
		NULL,
		(DLGPROC)DlgProc,
		NULL
	);
	::DeleteObject(g_hBgBrush);
	return 0;

	/*if (nResult == IDOK)
	{
		::MessageBox(NULL, "用户选择了确定按钮", "First Dialog", MB_OK);
	}
	else
	{
		::MessageBox(NULL, "用户选择了取消按钮", "First Dialog", MB_OK);
	}*/
}

BOOL __stdcall DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	default:
		break;
	case WM_INITDIALOG:		
		{
			::SendMessage(hDlg, WM_SETICON, ICON_BIG, (long)g_hIcon);
			HWND hWndBmp = ::GetDlgItem(hDlg, IDC_BMP);
			LONG nStyle = ::GetWindowLong(hWndBmp, GWL_STYLE);
			::SetWindowLong(hWndBmp, GWL_STYLE, nStyle | SS_BITMAP);
			::SendDlgItemMessage(hDlg, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP,
				(long)g_hBitmap1);
			::CheckDlgButton(hDlg, IDC_BMP1, BST_CHECKED);
		}
	//	::SetWindowText(hDlg, "First Dialog!");
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			break;
		case IDOK:
			{
				HWND hWndEdit = ::GetDlgItem(hDlg, IDC_INPUT);
				char szText[256];
				int nLen = ::GetWindowText(hWndEdit, szText, 256);
				if (nLen > 0)
				{
					::SendDlgItemMessage(hDlg, IDC_LIST, LB_ADDSTRING, NULL, (long)szText);
					::SetWindowText(hWndEdit, "");
				}
			}

			break;
		case IDCANCEL:
			::EndDialog(hDlg, IDCANCEL);
			break;
		case IDC_BMP1:
			{
				int nRet = ::IsDlgButtonChecked(hDlg, IDC_BMP1);
				if (nRet == BST_CHECKED)
				{
					::SendDlgItemMessage(hDlg, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hBitmap1);
				}
			}
			break;
		case IDC_BMP2:
			{
				int nRet = ::IsDlgButtonChecked(hDlg, IDC_BMP2);
				if (nRet == BST_CHECKED)
				{
					::SendDlgItemMessage(hDlg, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hBitmap2);
				}
			}
			break;
		case IDC_TOPMOST:
			{
				HWND hWndCheck = ::GetDlgItem(hDlg, IDC_TOPMOST);
				int nRet = ::SendMessage(hWndCheck, BM_GETCHECK, 0, 0);
				if (nRet == BST_CHECKED)
				{
					::SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
				}
				else
				{
					::SetWindowPos(hDlg, HWND_NOTOPMOST, 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
				}
			}
			break;
		case IDC_HIDE:
			{
				HWND hWndBmp = ::GetDlgItem(hDlg, IDC_BMP);
				HWND hWndCheck = ::GetDlgItem(hDlg, IDC_HIDE);
				int nRet = ::SendMessage(hWndCheck, BM_GETCHECK, 0, 0);
				if (nRet == BST_CHECKED)
				{
					::ShowWindow(hWndBmp, SW_HIDE);
				}
				else
				{
					::ShowWindow(hWndBmp, SW_SHOW);
				}
			}
			break;
		}
	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			::SetBkColor(hdc, RGB(0xa6, 0xca, 0xf0));
			if ((HWND)lParam == ::GetDlgItem(hDlg, IDC_AUTHOR))
			{
				::SetTextColor(hdc, RGB(0, 0, 0xFF));
			}
			return (int)g_hBgBrush;
		}
		break;
	}
	return 0;
}

