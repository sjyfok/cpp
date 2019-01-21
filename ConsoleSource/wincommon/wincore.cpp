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