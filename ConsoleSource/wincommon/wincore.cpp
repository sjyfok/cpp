#include "_afxwin.h"
#include "winhand_.h"
#include "_afximpl.h"

const TCHAR _afxWnd[] = AFX_WND;
const TCHAR _afxWndFrameOrView[] = AFX_WNDFRAMEORVIEW;

void AfxHookWindowCreate(CWnd* pWnd);
BOOL AfxUnhookWindowCreate();
LRESULT __stdcall _AfxCbtFilterHook(int code, WPARAM wParam, LPARAM lParam);

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

WNDPROC* CWnd::GetSuperWndProcAddr()
{
	return &m_pfnSuper;
}

LRESULT CWnd::Default()
{
	_AFX_THREAD_STATE *pThreadState = AfxGetThreadState();
	return DefWindowProc(pThreadState->m_lastSendMsg.message,
		pThreadState->m_lastSendMsg.wParam, pThreadState->m_lastSendMsg.lParam);
}

LRESULT CWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pfnSuper != NULL)
	{
		return ::CallWindowProc(m_pfnSuper, m_hWnd, message, wParam, lParam);
	}
	WNDPROC pfnWndProc;
	if ((pfnWndProc = *GetSuperWndProcAddr()) == NULL)
	{
		return ::DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	else
	{
		return ::CallWindowProc(pfnWndProc, m_hWnd, message, wParam, lParam);
	}
}

BOOL CWnd::Create(LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName, DWORD dwStyle,
	const RECT &rect,
	CWnd * pParentWnd, UINT nID,
	LPVOID lpParam)
{
	ASSERT(pParentWnd != NULL);
	ASSERT((dwStyle&WS_POPUP) == 0);
	return CreateEx(0, lpszClassName, lpszWindowName,
		dwStyle | WS_CHILD,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU)nID, (LPVOID)lpParam);
}

BOOL CWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName, DWORD dwStyle,
	int x, int y, int nWidth, int nHeight,
	HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	CREATESTRUCT cs;
	cs.dwExStyle = dwExStyle;
	cs.lpszClass = lpszClassName;
	cs.lpszName = lpszWindowName;
	cs.style = dwStyle;
	cs.x = x;
	cs.y = y;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.hwndParent = hWndParent;
	cs.hMenu = nIDorHMenu;
	cs.hInstance = AfxGetModuleState()->m_hCurrentInstanceHandle;
	cs.lpCreateParams = lpParam;
	if (!PreCreateWindow(cs))
	{
		PostNcDestroy();
		return FALSE;
	}
	AfxHookWindowCreate(this);
	HWND hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
		cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
		cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	if (!AfxUnhookWindowCreate())
	{
		PostNcDestroy();
	}
	if (hWnd == NULL)
	{
		return FALSE;
	}
	ASSERT(hWnd == m_hWnd);
	return TRUE;
}

BOOL CWnd::PreCreateWindow(CREATESTRUCT &cs)
{
	if (cs.lpszClass == NULL)
	{
		VERIFY(AfxEndDeferRegisterClass(AFX_WND_REG));
		ASSERT(cs.style&WS_CHILD);
		cs.lpszClass = _afxWnd;
	}
	return TRUE;
}

void CWnd::PostNcDestroy()
{

}

void CWnd::PreSubclassWindow()
{

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


IMPLEMENT_DYNCREATE(CWnd, CCmdTarget)

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
	HBRUSH hbrBackground, HICON hIcon)
{
	LPTSTR lpszName = AfxGetThreadState()->m_szTempClassName;
	HINSTANCE hInst = AfxGetModuleState()->m_hCurrentInstanceHandle;

	if ((hCursor == NULL) && (hbrBackground == NULL) && (hIcon = NULL))
	{
		wsprintf(lpszName, "Afx:%d:%d", (int)hInst, nClassStyle);
	}
	else
	{
		wsprintf(lpszName, "Afx:%d:%d:%d:%d", (int)hInst, nClassStyle,
			(int)hCursor, (int)hbrBackground, (int)hIcon);
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

void AfxHookWindowCreate(CWnd* pWnd)
{
	_AFX_THREAD_STATE *pThreadState = AfxGetThreadState();
	if (pThreadState->m_pWndInit == pWnd)
	{
		return;
	}
	if (pThreadState->m_hHookOldCbtFilter == NULL)
	{
		pThreadState->m_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT,
			_AfxCbtFilterHook, NULL, ::GetCurrentThreadId());
		ASSERT(pWnd != NULL);
		ASSERT(pWnd->m_hWnd == NULL);
		ASSERT(pThreadState->m_pWndInit == NULL);
		pThreadState->m_pWndInit = pWnd;
	}
}

BOOL AfxUnhookWindowCreate()
{
	_AFX_THREAD_STATE *pThreadState = AfxGetThreadState();
	if (pThreadState->m_hHookOldCbtFilter != NULL)
	{
		::UnhookWindowsHookEx(pThreadState->m_hHookOldCbtFilter);
		pThreadState->m_hHookOldCbtFilter = NULL;
	}
	if (pThreadState->m_pWndInit != NULL)
	{
		pThreadState->m_pWndInit = NULL;
		return FALSE;
	}
	return TRUE;
}

WNDPROC AfxGetAfxWndProc()
{
	return &AfxWndProc;
}

LRESULT __stdcall _AfxCbtFilterHook(int code, WPARAM wParam, LPARAM lParam)
{
	_AFX_THREAD_STATE *pThreadState = AfxGetThreadState();
	if (code != HCBT_CREATEWND)
	{
		return ::CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code, wParam, lParam);
	}
	HWND hWnd = (HWND)wParam;
	CWnd *pWndInit = pThreadState->m_pWndInit;
	if (pWndInit != NULL)
	{
		ASSERT(CWnd::FromHandlePermanent(hWnd) == NULL);
		pWndInit->Attach(hWnd);
		pWndInit->PreSubclassWindow();
		WNDPROC *pOldWndProc = pWndInit->GetSuperWndProcAddr();
		ASSERT(pOldWndProc != NULL);
		WNDPROC afxWndProc = AfxGetAfxWndProc();
		WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC,(DWORD_PTR)afxWndProc);// SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)afxWndProc);
		ASSERT(oldWndProc != NULL);
		if (oldWndProc != afxWndProc)
		{
			*pOldWndProc = oldWndProc;			
		}
		pThreadState->m_pWndInit = NULL;		
	}
	return ::CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code, wParam, lParam);
}
