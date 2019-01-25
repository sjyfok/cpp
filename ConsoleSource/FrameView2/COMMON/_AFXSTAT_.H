///////////////////////////////////////////////////////
// _AFXSTAT_.H�ļ�

#ifndef __AFXSTAT_H__
#define __AFXSTAT_H__

#ifndef __AFXTLS_H__
	#include "_afxtls_.h"
#endif


// AFX_MODULE_THREAD_STATE (ģ��-�߳�״̬)
class CWinThread;
class CHandleMap;
class AFX_MODULE_THREAD_STATE : public CNoTrackObject
{
public:
	// ָ��ǰ�̶߳���(CWinThread����)��ָ��
	CWinThread* m_pCurrentWinThread;

	// ���ھ��ӳ��
	CHandleMap* m_pmapHWND;
};

AFX_MODULE_THREAD_STATE* AfxGetModuleThreadState();


// AFX_MODULE_STATE (ģ��״̬)
struct CRuntimeClass;
class CWinApp;
class AFX_MODULE_STATE : public CNoTrackObject
{
public:
	
	CTypedSimpleList<CRuntimeClass*> m_listClass;	// ��¼ģ���е�����Ϣ

	CWinApp* m_pCurrentWinApp;	    // ��ǰCWinApp�����ָ��
	HINSTANCE m_hCurrentInstanceHandle; // ��ǰģ���ʵ�������Ҳ����ģ������
	HINSTANCE m_hCurrentResourceHandle; // ������Դ��ʵ�����

	// CThreadLocal<AFX_MODULE_THREAD_STATE> m_thread;
	THREAD_LOCAL(AFX_MODULE_THREAD_STATE, m_thread) // �ض����̵߳�״̬����
};

AFX_MODULE_STATE* AfxGetAppModuleState();
AFX_MODULE_STATE* AfxGetModuleState();

// _AFX_THREAD_STATE ���߳�״̬��
class CWnd;
class _AFX_THREAD_STATE : public CNoTrackObject
{
public:
	AFX_MODULE_STATE* m_pModuleState;

	// ע�ᴰ����ʱʹ�ã���������
	TCHAR m_szTempClassName[96]; 

	// ��������ʱʹ��
	CWnd* m_pWndInit;		// ���ڳ�ʼ����CWnd�����ָ��
	HHOOK m_hHookOldCbtFilter;	// ���Ӿ��

	MSG m_lastSendMsg;
};

EXTERN_THREAD_LOCAL(_AFX_THREAD_STATE, _afxThreadState);
_AFX_THREAD_STATE* AfxGetThreadState();

#endif // __AFXSTAT_H__



/*
3.3 ��

#ifndef __AFXSTAT_H__
#define __AFXSTAT_H__

#ifndef __AFXTLS_H__
	#include "_afxtls_.h"
#endif

class CWinThread;

// AFX_MODULE_THREAD_STATE (ģ��-�߳�״̬)
class AFX_MODULE_THREAD_STATE : public CNoTrackObject
{
public:
	// ָ��ǰ�̶߳���(CWinThread����)��ָ��
	CWinThread* m_pCurrentWinThread;
};

EXTERN_THREAD_LOCAL(AFX_MODULE_THREAD_STATE, _afxModuleThreadState)
AFX_MODULE_THREAD_STATE* AfxGetModuleThreadState();



#endif // __AFXSTAT_H__

 */