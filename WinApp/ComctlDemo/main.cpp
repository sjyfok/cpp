#include <Windows.h>
#include <CommCtrl.h>
#include <TlHelp32.h>
#include "Project1/resource.h"

#pragma comment(lib, "comctl32.lib")

#define IDC_STAUTS		101


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
		HWND hWndList = ::GetDlgItem(hDlg, IDC_LIST);
		::SendMessage(hWndList, LVM_SETEXTENDEDLISTVIEWSTYLE,
			0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		LVCOLUMN column;
		column.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;
		column.fmt = LVCFMT_CENTER;
		column.cx = 100;
		column.pszText = (LPSTR)("映像名称");
		::SendMessage(hWndList, LVM_INSERTCOLUMN, 0, (LPARAM)&column);
		column.pszText = (LPSTR)("PID");
		column.cx = 50;
		::SendMessage(hWndList, LVM_INSERTCOLUMN, 1, (LPARAM)&column);
		HWND hWndStatus = ::CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP,
			NULL, hDlg, IDC_STAUTS);
		::SendMessage(hWndStatus, SB_SETBKCOLOR, 0, RGB(0xa6, 0xca, 0xf0));
		int pInt[] = { 152, -1 };
		::SendMessage(hWndStatus, SB_SETPARTS, 2, (long)pInt);
		::SendMessage(hWndStatus, SB_SETTEXT, 0, (long)" 准备就绪");
		::SendMessage(hWndStatus, SB_SETTEXT, 1, (long)"Windows 程序设计进阶之路");
		UpdateProcess(hWndList);
	}
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
		case IDC_UPDATE:
			UpdateProcess(::GetDlgItem(hDlg, IDC_LIST));
			break;
		}
		break;
	case WM_NOTIFY:
	{
		if (wParam == IDC_LIST)
		{
			NMHDR *pHeader = (NMHDR*)lParam;
			HWND hWndList = pHeader->hwndFrom;
			if (pHeader->code == NM_DBLCLK)
			{
				NMLISTVIEW* pNMListView = (NMLISTVIEW*)pHeader;
				int nIndex = pNMListView->iItem;
				char szID[56];
				LVITEM lvi;
				memset(&lvi, 0, sizeof(LVITEM));
				lvi.iSubItem = 1;
				lvi.cchTextMax = 56;
				lvi.pszText = szID;
				::SendMessage(hWndList, LVM_GETITEMTEXT, (WPARAM)nIndex,
					(long)&lvi);
				if (::MessageBox(hDlg, "确实要终止进程吗?",
					"ComctlDemo", MB_OKCANCEL | MB_DEFBUTTON2) == IDCANCEL)
				{
					return 0;
				}
				HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE,
					atoi(szID));
				if (hProcess != NULL)
				{
					HWND hWndStatus = ::GetDlgItem(hDlg, IDC_STAUTS);
					if (::TerminateProcess(hProcess, 0))
					{
						::SendMessage(hWndStatus, SB_SETTEXT, 0, (long)"终止进程成功");
						UpdateProcess(hWndList);
					}
					else
					{
						::SendMessage(hWndStatus, SB_SETTEXT, 0, (long)"终止进程失败");
					}
				}
			}
		}
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
			::SendMessage(hWndList, LVM_INSERTITEM, 0, (long)&item);
			LVITEM lvi;
			lvi.iSubItem = 1;
			lvi.pszText = (LPTSTR)szID;
			::SendMessage(hWndList, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi);
			nItem++;
		} while (Process32Next(hProcessSnap, &pe32));
	}
	::CloseHandle(hProcessSnap);
}
