#include <Windows.h>
#include <CommCtrl.h>
#include <TlHelp32.h>
#include "Project1/resource.h"

#pragma comment(lib, "comctl32.lib")


BOOL __stdcall DlgProc(HWND, UINT, WPARAM, LPARAM);
void UpdateProcess(HWND hWndList);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	::InitCommonControls();
	
	::DialogBoxParam(
		hInstance,
		(LPCTSTR)IDD_MAIN,
		NULL,
		(DLGPROC)DlgProc,
		NULL
	);
	return 0;
}

BOOL __stdcall DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	default:
		break;
	case WM_INITDIALOG:
	{
		HWND hWndProgress = ::GetDlgItem(hDlg, IDC_PROGRESS);
		::SendMessage(hWndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 20));
		::SendMessage(hWndProgress, PBM_SETSTEP, 1, 0);
		::SendMessage(hWndProgress, PBM_SETBKCOLOR, 0, RGB(0, 0, 0xFF));
		::SendMessage(hWndProgress, PBM_SETBARCOLOR, 0, RGB(0xFF, 0, 0));		
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			break;
		case IDOK:
			SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_STEPIT, 0, 0);
			break;
		case IDCANCEL:
			::EndDialog(hDlg, IDCANCEL);
			break;
		}
		break;	
	}
			
	return 0;
}

void UpdateProcess(HWND hWndList)
{
	::SendMessage(hWndList, LVM_DELETEALLITEMS, 0, 0);
	int nItem = 0;
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			char szID[56];
			wsprintf(szID, "%u", pe32.th32ProcessID);
			LVITEM item = { 0 };
			item.iItem = nItem;
			item.mask = LVIF_TEXT;
			item.pszText = (LPTSTR)pe32.szExeFile;
			::SendMessage(hWndList, LVM_INSERTITEM, 0, (LPARAM)&item);
			LVITEM lvi;
			lvi.iSubItem = 1;
			lvi.pszText = (LPTSTR)szID;
			::SendMessage(hWndList, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi);
			nItem++;
		} while (Process32Next(hProcessSnap, &pe32));
	}
	::CloseHandle(hProcessSnap);
}
