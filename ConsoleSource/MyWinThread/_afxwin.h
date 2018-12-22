#ifndef __AFXWIN_H__
#define __AFXWIN_H__

#include <Windows.h>

class CWinThread
{
public:
	CWinThread();
	BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
		LPSECURITY_ATTRIBUTES lpSecurtyAttrs = NULL);
	HANDLE m_hThread;
	operator HANDLE() const { return m_hThread; }
	DWORD m_nThreadID;
	int GetThreadPriority();
	BOOL SetThreadPriority(int nPriority);
	DWORD SuspendThread();
	DWORD ResumeThread();
};
#endif // !__AFXTLS_H__
