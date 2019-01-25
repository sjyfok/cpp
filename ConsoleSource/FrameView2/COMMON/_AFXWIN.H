///////////////////////////////////////
// _AFXWIN.H�ļ�

#ifndef __AFXWIN_H__
#define __AFXWIN_H__

#include <windows.h>

#include "_afx.h"
#include "_afxstat_.h"
#include "_afxmsg_.h"
#include "_afxcoll.h"


////////////////////////////////////////////////////////////

// type modifier for message handlers
#ifndef afx_msg
#define afx_msg  // �ڲ�ռλ��
#endif


////////////////////////////////////////////////////
// ������Ϣӳ��Ĵ���
class CCmdTarget;
typedef void (CCmdTarget::*AFX_PMSG)(void);

// һ��ӳ�����
struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;	// ������Ϣ
	UINT nCode;	// ���ƴ����WM_NOTIFY֪ͨ��
	UINT nID;	// �ؼ�ID�����Ϊ������Ϣ��ֵΪ0
	UINT nLastID;	// һ����Χ����������һ�������ؼ�ID������֧������Ϣӳ��
	UINT nSig;	// ָ������Ϣ��������������
	AFX_PMSG pfn;   // ��Ϣ��������
};

// ��Ϣӳ���
struct AFX_MSGMAP
{
	const AFX_MSGMAP* pBaseMap;		// ��������Ϣӳ����ĵ�ַ
	const AFX_MSGMAP_ENTRY* pEntries;	// ��Ϣӳ�����ָ��
};

// ��Ķ���
#define DECLARE_MESSAGE_MAP() \
private: \
	static const AFX_MSGMAP_ENTRY _messageEntries[]; \
protected: \
	static const AFX_MSGMAP messageMap; \
	virtual const AFX_MSGMAP* GetMessageMap() const; \

#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
	const AFX_MSGMAP* theClass::GetMessageMap() const \
		{ return &theClass::messageMap; } \
	const AFX_MSGMAP theClass::messageMap = \
	{ &baseClass::messageMap, &theClass::_messageEntries[0] }; \
	const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
	{ \

#define END_MESSAGE_MAP() \
		{0, 0, 0, 0, 0, (AFX_PMSG)0} \
	}; \

////////////////////////////////////////////////////
// CCmdTarget�ࣨ����Ŀ�꣩

class CCmdTarget : public CObject
{
	DECLARE_DYNCREATE(CCmdTarget);
public:
	CCmdTarget();

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////
// CWnd ��

class CWnd : public CCmdTarget
{
	DECLARE_DYNCREATE(CWnd)
public:	
	CWnd();
	virtual ~CWnd();

	HWND m_hWnd;
	operator HWND() const { return m_hWnd; }
	HWND GetSafeHwnd() { return this == NULL ? NULL : m_hWnd; }

	// ���ھ��ӳ��
	static CWnd* FromHandle(HWND hWnd);
	static CWnd* FromHandlePermanent(HWND hWnd);
	BOOL Attach(HWND hWndNew);
	HWND Detach();	


	// Ϊ���������Ӵ�������
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		LPVOID lpParam = NULL);

	// ���մ������ڵĴ���
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();

	static const MSG* GetCurrentMessage();

protected:

	// Ĭ����Ϣ���������ĵ�ַ
	WNDPROC m_pfnSuper;
	virtual WNDPROC* GetSuperWndProcAddr();

	// ����Ϣ����Ĭ�ϴ���
	LRESULT Default();	
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	

	// ����Windows��Ϣ
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);


	// ��Ϣ��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	// WM_CREATE��Ϣ
	afx_msg void OnPaint();			// WM_PAINT��Ϣ
	afx_msg void OnClose();			// WM_CLOSE��Ϣ
	afx_msg void OnDestroy();		// WM_DESTROY��Ϣ
	afx_msg void OnNcDestroy();		// WM_NCDESTROY��Ϣ
	afx_msg void OnTimer(UINT nIDEvent);	// WM_TIMER��Ϣ
	

	// �ַ���Ϣ��ʵ��
	friend LRESULT AfxCallWndProc(CWnd*, HWND, UINT, WPARAM, LPARAM);
	// �ҹ���Ϣ��ʵ��
	friend LRESULT __stdcall _AfxCbtFilterHook(int, WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

typedef void (CWnd::*AFX_PMSGW)(void); 
		// like 'AFX_PMSG' but for CWnd derived classes only

// ע�����Լ��Ĵ�����ĸ�������
LPCTSTR AfxRegisterWndClass(UINT nClassStyle,
	HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

BOOL AfxRegisterClass(WNDCLASS* lpWndClass);
BOOL AfxEndDeferRegisterClass(LONG fToRegister);

WNDPROC AfxGetAfxWndProc();

void AfxHookWindowCreate(CWnd* pWnd);
BOOL AfxUnhookWindowCreate();

const AFX_MSGMAP_ENTRY* AfxFindMessageEntry(const AFX_MSGMAP_ENTRY* lpEntry, 
						UINT nMsg, UINT nCode, UINT nID);

////////////////////////////////////////////////////
// CWinThread ��
extern CThreadSlotData* _afxThreadData;

typedef UINT (__cdecl *AFX_THREADPROC)(LPVOID);

class CWinThread : public CCmdTarget
{
	DECLARE_DYNCREATE(CWinThread)
public:
// �̶߳���ĳ�ʼ����Constructors��
	CWinThread();
	BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
		LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);


// ����������̶߳������е����ԣ�Attributes��
	CWnd* m_pMainWnd;	// ������
	BOOL m_bAutoDelete;	// ָʾ���߳̽������Ƿ�Ҫ���ٴ˶���

	HANDLE m_hThread;
	DWORD m_nThreadID;	
	operator HANDLE() const
		{ return this == NULL ? NULL : m_hThread; }
	
	int GetThreadPriority()
		{ return ::GetThreadPriority(m_hThread); }
	BOOL SetThreadPriority(int nPriority)
		{ return ::SetThreadPriority(m_hThread, nPriority); }

// ���̵߳Ĳ�����Operations��
	DWORD SuspendThread()
		{ return ::SuspendThread(m_hThread); }
	DWORD ResumeThread()
		{ return ::ResumeThread(m_hThread); }

// �������صĺ�����Overridables��
	// ִ���߳�ʵ����ʼ��
	virtual BOOL InitInstance();

	// ��ʼ������Ϣ
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PumpMessage();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL IsIdleMessage(MSG* pMsg);

	// �߳���ֹʱִ�����
	virtual int ExitInstance();
	
// ����ʵ��(Implementation)
public:
	virtual ~CWinThread();
	virtual void Delete();
	void CommonConstruct();

	MSG m_msgCur;
public:
	CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

	LPVOID m_pThreadParams;		// �û����ݸ����̵߳Ĳ���
	AFX_THREADPROC m_pfnThreadProc; // �̺߳����ĵ�ַ
};

// �ṩ���û�ʹ�õ�ȫ�ֺ���
CWinThread* AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
	DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
CWinThread* AfxGetThread();
void AfxEndThread(UINT nExitCode, BOOL bDelete = TRUE);


///////////////////////////////////////////////////////////////////////////////
// CWinApp��
class CWinApp : public CWinThread
{
	DECLARE_DYNCREATE(CWinApp)
public:
	CWinApp();
	virtual ~CWinApp();

// ����
	// WinMain�������ĸ�����
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPTSTR m_lpCmdLine;
	int m_nCmdShow;

// ����������ͨ����InitInstance�����н���
public:
	HCURSOR LoadCursor(UINT nIDResource) const;
	HICON LoadIcon(UINT nIDResource) const;

// �麯��
public:
	virtual BOOL InitApplication();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
};

__inline HCURSOR CWinApp::LoadCursor(UINT nIDResource) const
	{ return::LoadCursor(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource); }
__inline HICON CWinApp::LoadIcon(UINT nIDResource) const
	{ return::LoadIcon(AfxGetModuleState()->m_hCurrentResourceHandle, (LPCTSTR)nIDResource); }

CWinApp* AfxGetApp();

__inline CWinApp* AfxGetApp()
	{ return AfxGetModuleState()->m_pCurrentWinApp; }

BOOL AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPTSTR lpCmdLine, int nCmdShow);

#endif // __AFXWIN_H__


/*



////////////////////////////////////////////////////
// CWinThread ��
extern CThreadSlotData* _afxThreadData;

typedef UINT (__cdecl *AFX_THREADPROC)(LPVOID);

class CWinThread
{
public:
// �̶߳���ĳ�ʼ����Constructors��
	CWinThread();
	BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
		LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);


// ����������̶߳������е����ԣ�Attributes��
	BOOL m_bAutoDelete;	// ָʾ���߳̽������Ƿ�Ҫ���ٴ˶���

	HANDLE m_hThread;
	DWORD m_nThreadID;	
	operator HANDLE() const
		{ return this == NULL ? NULL : m_hThread; }
	
	int GetThreadPriority()
		{ return ::GetThreadPriority(m_hThread); }
	BOOL SetThreadPriority(int nPriority)
		{ return ::SetThreadPriority(m_hThread, nPriority); }

// ���̵߳Ĳ�����Operations��
	DWORD SuspendThread()
		{ return ::SuspendThread(m_hThread); }
	DWORD ResumeThread()
		{ return ::ResumeThread(m_hThread); }

// ����ʵ��(Implementation)
public:
	virtual ~CWinThread();
	virtual void Delete();
	void CommonConstruct();
public:
	CWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

	LPVOID m_pThreadParams;		// �û����ݸ����̵߳Ĳ���
	AFX_THREADPROC m_pfnThreadProc; // �̺߳����ĵ�ַ
};

// �ṩ���û�ʹ�õ�ȫ�ֺ���
CWinThread* AfxBeginThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam,
	int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
	DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
CWinThread* AfxGetThread();
void AfxEndThread(UINT nExitCode, BOOL bDelete = TRUE);





  */