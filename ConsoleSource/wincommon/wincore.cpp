#include "_afxwin.h"
#include "winhand_.h"
#include "_afximpl.h"

const TCHAR _afxWnd[] = AFX_WND;
const TCHAR _afxWndFrameOrView[] = AFX_WNDFRAMEORVIEW;

CWnd::CWnd()
{
	m_hWnd = NULL;
}

CWnd::~CWnd()
{
	if (m_hWnd != NULL)
	{
		::DestroyWindow(m_hWnd);
	}
}

CHandleMap *afxMapHWND(BOOL bCreate = FALSE)
{
	AFX_MODULE_THREAD_STATE *pState = AfxGetModuleThreadState();
	if (pState->m_pmapHWND == NULL && bCreate)
	{
		pState->m_pmapHWND = new CHandleMap();
	}
	return pState->m_pmapHWND;
}

CWnd* CWnd::FromHandle(HWND hWnd)
{
	CHandleMap *pMap = afxMapHWND(TRUE);
	ASSERT(pMap != NULL);
	return (CWnd*)pMap->FromHandle(hWnd);
}

CWnd* CWnd::FromHandlePermanent(HWND hWnd)
{
	CHandleMap *pMap = afxMapHWND();
	CWnd *pWnd = NULL;
	if (pMap != NULL)
	{
		pWnd = (CWnd*)pMap->LookupPermanent(hWnd);
	}
	return pWnd;
}

BOOL CWnd::Attach(HWND hWndNew)
{
	ASSERT(m_hWnd == NULL);
	ASSERT(FromHandlePermanent(hWndNew) == NULL);
	if (hWndNew == NULL)
	{
		return FALSE;
	}
	CHandleMap *pMap = afxMapHWND(TRUE);
	ASSERT(pMap != NULL);
	pMap->SetPermanent(m_hWnd = hWndNew, this);
	return TRUE;
}

HWND CWnd::Detach()
{
	HWND hWnd = m_hWnd;
	if (hWnd != NULL)
	{
		CHandleMap *pMap = afxMapHWND();
		if (pMap != NULL)
		{
			pMap->RemoveHandle(hWnd);
		}
		m_hWnd = NULL;
	}
	return hWnd;
}


LRESULT __stdcall AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CWnd *pWnd = CWnd::FromHandlePermanent(hWnd);
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd == hWnd);
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}

LRESULT AfxCallWndProc(CWnd *pWnd, HWND hWnd, UINT nMsg,
	WPARAM wParam = 0, LPARAM lParam = 0)
{
	_AFX_THREAD_STATE *pThreadState = AfxGetThreadState();
	MSG oldState = pThreadState->m_lastSendMsg;
	pThreadState->m_lastSendMsg.hwnd = hWnd;
	pThreadState->m_lastSendMsg.message = nMsg;
	pThreadState->m_lastSendMsg.wParam = wParam;
	pThreadState->m_lastSendMsg.lParam = lParam;

	LRESULT lResult;
	lResult = pWnd->WindowProc(nMsg, wParam, lParam);
	pThreadState->m_lastSendMsg = oldState;
	return lResult;
}

LRESULT CWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BOOL AfxEndDeferRegisterClass(LONG fToRegister)
{
	WNDCLASS wndclass;
	memset(&wndclass, 0, sizeof(wndclass));
	wndclass.lpfnWndProc = ::DefWindowProc;
	wndclass.hInstance = AfxGetModuleState()->m_hCurrentInstanceHandle;
	wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	BOOL bResult = FALSE;
	if (fToRegister & AFX_WND_REG)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.lpszClassName = _afxWnd;
		bResult = AfxRegisterClass(&wndclass);
	}
	else if (fToRegister &AFX_WNDFRAMEORVIEW_REG)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndclass.lpszClassName = _afxWndFrameOrView;
		bResult = AfxRegisterClass(&wndclass);
	}
	return bResult;
}

BOOL AfxRegisterClass(WNDCLASS *lpWndClass)
{
	WNDCLASS wndclass;
	if (GetClassInfo(lpWndClass->hInstance, lpWndClass->lpszClassName, &wndclass))
	{
		return TRUE;
	}
	if (!::RegisterClass(lpWndClass))
	{
		TRACE("Can't register window class name %s\n", lpWndClass->lpszClassName);
		return FALSE;
	}
	return TRUE;
}

LPCTSTR AfxRegisterWndClass(UINT nClassStyle, HCURSOR hCursor,
	HBRUSH hbtBackground, HICON hIcon)
{
	LPTSTR lpszName = AfxGetThreadState()->m_szTempClassName;
	HINSTANCE hInst = AfxGetModuleState()->m_hCurrentInstanceHandle;
	if (hCursor == NULL && hbrBackground == NULL && hIcon = NULL)
	{
		wsprintf(lpszName, "Afx:%d:%d", (int)hInst, nClassStyle);
	}
	else
	{
		wsprintf(lpszName, "Afx:%d:%d:%d:%d", (int)hInst, nClassStyle,
			(int)hCursor, (int)hbtBackground, (int)hIcon);
	}
	WNDCLASS wc = { 0 };
	if (::GetClassInfo(hInst, lpszName, &wc))
	{
		ASSERT(wc.style == nClassStyle);
		return lpszName;
	}
	wc.hInstance = hInst;
	wc.style = nClassStyle;
	wc.hCursor = hCursor;
	wc.hbrBackground = hbrBackground;
	wc.hIcon = hIcon;
	wc.lpszClassName = lpszName;
	wc.lpfnWndProc = ::DefWindowProc;
	if (!AfxRegisterClass(&wc))
	{
		TRACE("Can't register window class named %s\n", lpszName);
		return NULL;
	}
	return lpszName;
}	
