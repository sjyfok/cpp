////////////////////////////////////////////////
// WINCORE.CPP�ļ�

#include "_afxwin.h"
#include "winhand_.h"
#include "_afximpl.h"


// ��ܳ���ע�ᴰ����ʱʹ�õ�����
const TCHAR _afxWnd[] = AFX_WND;
const TCHAR _afxWndFrameOrView[] = AFX_WNDFRAMEORVIEW;



CWnd::CWnd()
{
	m_hWnd = NULL;
	m_pfnSuper = NULL;
}

CWnd::~CWnd()
{
	if(m_hWnd != NULL)
	{
		::DestroyWindow(m_hWnd);
	}
}

/////////////////////////////////////////////////
// ��ʼ����Ϣӳ���
BEGIN_MESSAGE_MAP(CWnd, CCmdTarget)
ON_WM_NCDESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////
// ���ӳ��

CHandleMap* afxMapHWND(BOOL bCreate = FALSE)
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	if(pState->m_pmapHWND == NULL && bCreate)
	{
		pState->m_pmapHWND = new CHandleMap();
	}
	return pState->m_pmapHWND;
}

CWnd* CWnd::FromHandle(HWND hWnd)
{
	CHandleMap* pMap = afxMapHWND(TRUE); // ����������򴴽�һ��CHandleMap����
	ASSERT(pMap != NULL);
	return (CWnd*)pMap->FromHandle(hWnd);
}

CWnd* CWnd::FromHandlePermanent(HWND hWnd)
{
	CHandleMap* pMap = afxMapHWND();
	CWnd* pWnd = NULL;
	if(pMap != NULL)
	{
		// ����������ӳ�䣨����ʱӳ�䣩�в��ҡ����������κ��µ�CWnd����
		pWnd = (CWnd*)pMap->LookupPermanent(hWnd);
	}
	return pWnd;
}

BOOL CWnd::Attach(HWND hWndNew)
{
	ASSERT(m_hWnd == NULL);	 // ��������һ��
	ASSERT(FromHandlePermanent(hWndNew) == NULL); // ����û��������ӳ����

	if(hWndNew == NULL)
		return FALSE;

	CHandleMap* pMap = afxMapHWND(TRUE);	// ����������򴴽�һ��CHandleMap����
	ASSERT(pMap != NULL);

	pMap->SetPermanent(m_hWnd = hWndNew, this); // ����һ��ӳ��
	return TRUE;
}

HWND CWnd::Detach()
{
	HWND hWnd = m_hWnd;
	if(hWnd != NULL)
	{
		CHandleMap* pMap = afxMapHWND(); // ��������ڲ�ȥ����
		if(pMap != NULL)
			pMap->RemoveHandle(hWnd);
		m_hWnd = NULL;
	}
	return hWnd;
}


///////////////////////////////////////////////
// �ַ���Ϣ

LRESULT __stdcall AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd == hWnd);
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}

LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, 
				WPARAM wParam = 0, LPARAM lParam = 0)
{
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	
	// ��Ϊ���ܻᷢ��Ƕ�׵��ã�����Ҫ���ȱ���ɵ���Ϣ���ں�������ʱ�ָ�
	MSG oldState = pThreadState->m_lastSendMsg;

	// ���±��߳��б���m_lastSendMsg��ֵ
	pThreadState->m_lastSendMsg.hwnd = hWnd;
	pThreadState->m_lastSendMsg.message = nMsg;
	pThreadState->m_lastSendMsg.wParam = wParam;
	pThreadState->m_lastSendMsg.lParam = lParam;

	// �������ܵ�����Ϣ

	// ����Ϣ����CWnd����
	LRESULT lResult;
	lResult = pWnd->WindowProc(nMsg, wParam, lParam);

	// ��Ϣ������ϣ��ڷ��ش��������ǰ�ָ�m_lastSendMsg��ֵ
	pThreadState->m_lastSendMsg = oldState;
	return lResult;
}

LRESULT CWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult;
	if(!OnWndMsg(message, wParam, lParam, &lResult))
		lResult = DefWindowProc(message, wParam, lParam);
	return lResult;
}

////////////////////////////////////////////////////////
// ע�ᴰ����

BOOL AfxRegisterClass(WNDCLASS* lpWndClass)
{
	WNDCLASS wndclass;
	if (GetClassInfo(lpWndClass->hInstance, lpWndClass->lpszClassName,
		&wndclass))
	{
		// �Ѿ�ע���˸���
		return TRUE;
	}
	if (!::RegisterClass(lpWndClass))
	{
		TRACE("Can't register window class named %s\n", lpWndClass->lpszClassName);
		return FALSE;
	}
	return TRUE;
}

LPCTSTR AfxRegisterWndClass(UINT nClassStyle, HCURSOR hCursor,
					HBRUSH hbrBackground, HICON hIcon)
{
	// ʹ���ֲ߳̾��洢�еĻ����������ʱ����
	LPTSTR lpszName = AfxGetThreadState()->m_szTempClassName;

	HINSTANCE hInst = AfxGetModuleState()->m_hCurrentInstanceHandle;
	if(hCursor == NULL && hbrBackground == NULL && hIcon == NULL)
		wsprintf(lpszName, "Afx:%d:%d", (int)hInst, nClassStyle);
	else
		wsprintf(lpszName, "Afx:%d:%d:%d:%d", (int)hInst, nClassStyle, 
					(int)hCursor, (int)hbrBackground, (int)hIcon);

	WNDCLASS wc = { 0 };
	if(::GetClassInfo(hInst, lpszName, &wc))
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

	if(!AfxRegisterClass(&wc))
	{
		TRACE("Can't register window class named %s\n", lpszName);						
		return NULL;
	}
	return lpszName;
}

BOOL AfxEndDeferRegisterClass(LONG fToRegister)
{
	WNDCLASS wndclass;
	memset(&wndclass, 0, sizeof(wndclass));
	wndclass.lpfnWndProc = ::DefWindowProc;
	wndclass.hInstance = AfxGetModuleState()->m_hCurrentInstanceHandle;
	wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);

	BOOL bResult = FALSE;
	if(fToRegister & AFX_WND_REG)
	{
		// �Ӵ��ڡ���û�б���ˢ�ӣ�û��ͼ�꣬�ȫ�ķ��
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.lpszClassName = _afxWnd;
		bResult = AfxRegisterClass(&wndclass);
	}
	else if(fToRegister & AFX_WNDFRAMEORVIEW_REG)
	{
		// ��ܻ���ͼ���ڡ�����ͨ����ɫ
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndclass.lpszClassName = _afxWndFrameOrView;
		bResult = AfxRegisterClass(&wndclass);
	}

	return bResult;
}

////////////////////////////////////////////
// �ҹ���Ϣ

WNDPROC AfxGetAfxWndProc()
{
	return &AfxWndProc;
}

LRESULT __stdcall _AfxCbtFilterHook(int code, WPARAM wParam, LPARAM lParam)
{
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	if(code != HCBT_CREATEWND)
	{
		// ֻ��HCBT_CREATEWND֪ͨ�¼�����Ȥ
		return ::CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code, wParam, lParam);
	}

	// �õ����ڳ�ʼ���Ĵ��ڵĴ��ھ����CWnd�����ָ��
	HWND hWnd = (HWND)wParam;
	CWnd* pWndInit = pThreadState->m_pWndInit;

	// ��hWnd������pWndInitָ���CWnd�����У������ô��ڵĴ��ں����ĵ�ַ
	if(pWndInit != NULL)
	{
		// hWnd��Ӧ�������þ��ӳ����
		ASSERT(CWnd::FromHandlePermanent(hWnd) == NULL);

		// ���Ӵ��ھ��
		pWndInit->Attach(hWnd);
	
		// �����������໯���ڵ��¼����ȷ���
		pWndInit->PreSubclassWindow();

		// ����Ҫ�ı䴰�ں����ĵ�ַ

		// Ҫ��pOldWndProcָ��ı����б���ԭ���Ĵ��ں���
		WNDPROC* pOldWndProc = pWndInit->GetSuperWndProcAddr();
		ASSERT(pOldWndProc != NULL);

		// ���໯�˴��ڣ��ı䴰�ں����ĵ�ַ��
		WNDPROC afxWndProc = AfxGetAfxWndProc();
		WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (DWORD_PTR)afxWndProc);
		/*WNDPROC oldWndProc = (WNDPROC)::SetWindowLong(hWnd, 
							GWL_WNDPROC, (DWORD)afxWndProc);*/
			pThreadState->m_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT,
			_AfxCbtFilterHook, NULL, ::GetCurrentThreadId());
		ASSERT(oldWndProc != NULL);
		if(oldWndProc != afxWndProc) // ���ȷʵ�ı���
			*pOldWndProc = oldWndProc;

		pThreadState->m_pWndInit = NULL;
	}
	return ::CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code, wParam, lParam);
}

void AfxHookWindowCreate(CWnd* pWnd)
{
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	if(pThreadState->m_pWndInit == pWnd)
		return;
	if(pThreadState->m_hHookOldCbtFilter == NULL)
		pThreadState->m_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT, 
					_AfxCbtFilterHook, NULL, ::GetCurrentThreadId());

	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd == NULL); // ���ҹ�һ��

	ASSERT(pThreadState->m_pWndInit == NULL);
	pThreadState->m_pWndInit = pWnd;
}

BOOL AfxUnhookWindowCreate()
{
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	if(pThreadState->m_hHookOldCbtFilter != NULL)
	{
		::UnhookWindowsHookEx(pThreadState->m_hHookOldCbtFilter);
		pThreadState->m_hHookOldCbtFilter = NULL;
	}

	if(pThreadState->m_pWndInit != NULL)
	{
		pThreadState->m_pWndInit = NULL;
		return FALSE;	// ����û�б��ɹ��İ�װ
	}
	return TRUE;
}

WNDPROC* CWnd::GetSuperWndProcAddr()
{
	return &m_pfnSuper;
}

LRESULT CWnd::Default()
{
	// ��������ܵ���һ����ϢΪ��������DefWindowProc����
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	return DefWindowProc(pThreadState->m_lastSendMsg.message, 
			pThreadState->m_lastSendMsg.wParam, pThreadState->m_lastSendMsg.lParam);
}

LRESULT CWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_pfnSuper != NULL)
		return ::CallWindowProc(m_pfnSuper, m_hWnd, message, wParam, lParam);

	WNDPROC pfnWndProc;
	if((pfnWndProc = *GetSuperWndProcAddr()) == NULL) 
		return ::DefWindowProc(m_hWnd, message, wParam, lParam);
	else
		return ::CallWindowProc(pfnWndProc, m_hWnd, message, wParam, lParam); 	
}

////////////////////////////////////////////////////////
// ��������

BOOL CWnd::Create(LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName, DWORD dwStyle,
	const RECT& rect,
	CWnd* pParentWnd, UINT nID,
	LPVOID lpParam)
{
	// ֻ���������ǵ���ʽ���Ӵ���
	ASSERT(pParentWnd != NULL);
	ASSERT((dwStyle & WS_POPUP) == 0);

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

	// �����麯��PreCreateWindow��ִ��ע�ᴰ����Ĵ���
	if(!PreCreateWindow(cs))
	{
		// �����麯��PostNcDestroy��֪ͨ�û�����û�б�����
		PostNcDestroy();
		return FALSE;
	}

	// ��������
	AfxHookWindowCreate(this);
	HWND hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
			cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
			cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	if(!AfxUnhookWindowCreate())
		PostNcDestroy();        // CreateWindowEx����ʧ�ܣ�֪ͨ�û�


	if(hWnd == NULL)
		return FALSE;
	ASSERT(hWnd == m_hWnd); // ���ˣ��´��ڵľ��Ӧ���Ѿ����ӵ���ǰCWnd����
	return TRUE;
}

BOOL CWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if(cs.lpszClass == NULL)
	{
		// Ĭ������£����������Ӵ���
		VERIFY(AfxEndDeferRegisterClass(AFX_WND_REG));
		ASSERT(cs.style & WS_CHILD);
		cs.lpszClass = _afxWnd;
	}
	return TRUE;
}

void CWnd::PostNcDestroy()
{
	// Ĭ�������ʲôҲ����
}

void CWnd::PreSubclassWindow()
{
	// Ĭ�������ʲôҲ����
}





const MSG* CWnd::GetCurrentMessage()
{
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	pThreadState->m_lastSendMsg.time = ::GetMessageTime();
	DWORD dw = ::GetMessagePos();
	pThreadState->m_lastSendMsg.pt.x = LOWORD(dw);
	pThreadState->m_lastSendMsg.pt.y = HIWORD(dw);
	return &pThreadState->m_lastSendMsg;
}






////////////////////////////////////////////////////////////
// �ַ���Ϣ

BOOL CWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LRESULT lResult = 0;

	// ��������Ϣ��֪ͨ��Ϣ����ָ���ĺ�������
	if(message == WM_COMMAND)
	{
		if(OnCommand(wParam, lParam))
		{
			lResult = 1;
			goto LReturnTrue;
		}
		return FALSE;
	}
	if(message == WM_NOTIFY)
	{
		NMHDR* pHeader = (NMHDR*)lParam;
		if(pHeader->hwndFrom != NULL && OnNotify(wParam, lParam, &lResult))
			goto LReturnTrue;
		return FALSE;
	}

	// �ڸ������Ϣӳ����в��Һ��ʵ���Ϣ�����������ҵ��Ļ��͵�����
	const AFX_MSGMAP* pMessageMap;
	const AFX_MSGMAP_ENTRY* lpEntry;
	for(pMessageMap = GetMessageMap(); pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMap)
	{
		ASSERT(pMessageMap != pMessageMap->pBaseMap);
		if((lpEntry = AfxFindMessageEntry(pMessageMap->pEntries, message, 0, 0)) != NULL)
				goto LDispatch;
	}
	return FALSE;

LDispatch:
	union MessageMapFunctions mmf;
	mmf.pfn = lpEntry->pfn;
	switch(lpEntry->nSig)
	{
	default:
		return FALSE;
	case AfxSig_vw:
		(this->*mmf.pfn_vw)(wParam);
		break;
	case AfxSig_vv:
		(this->*mmf.pfn_vv)();
		break;
	case AfxSig_is:
		(this->*mmf.pfn_is)((LPTSTR)lParam);
		break;	
	}

LReturnTrue:
	if(pResult != NULL)
		*pResult = lResult;
	return TRUE;
}

BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{ 
	return FALSE;
}

BOOL CWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{ 
	return FALSE; 
}


////////////////////////////////////////////////////
// Ĭ�ϵ���Ϣ����

int CWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return Default();
}

void CWnd::OnPaint()
{
	Default();
}

void CWnd::OnClose()
{
	Default();
}

void CWnd::OnDestroy()
{
	Default();
}

void CWnd::OnNcDestroy()
{
	CWinThread* pThread = AfxGetThread();
	if(pThread != NULL)     
	{
		if(pThread->m_pMainWnd == this)
		{
			if(pThread == AfxGetApp())   // Ӧ�ó�����˳�
			{
				::PostQuitMessage(0); 
			}
			pThread->m_pMainWnd = NULL;
		}
	}

	Default();
	Detach();
	// ������������������һ������
	PostNcDestroy();
}

void CWnd::OnTimer(UINT nIDEvent)
{
	Default();
}



const AFX_MSGMAP_ENTRY* AfxFindMessageEntry(const AFX_MSGMAP_ENTRY* lpEntry, 
						UINT nMsg, UINT nCode, UINT nID)
{
	while(lpEntry->nSig != AfxSig_end)
	{
		if(lpEntry->nMessage == nMsg && lpEntry->nCode == nCode &&
				(nID >= lpEntry->nID && nID <= lpEntry->nLastID))
			return lpEntry;
		lpEntry++;
	}
	return NULL;
}


IMPLEMENT_DYNCREATE(CWnd, CCmdTarget)