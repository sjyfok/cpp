#include "RapidFinder.h"
#include <stdio.h>

CRapidFinder::CRapidFinder(int nMaxThread) :m_nMaxThread(nMaxThread)
{
	m_nResultCount = 0;
	m_nThreadCount = 0;
	m_szMatchName[0] = '\0';
	m_listDir.Construct(offsetof(CDirectoryNode, pNext));
	m_hDirEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hExitEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	::InitializeCriticalSection(&m_cs);
}

CRapidFinder::~CRapidFinder()
{
	::CloseHandle(m_hDirEvent);
	::CloseHandle(m_hExitEvent);
	::DeleteCriticalSection(&m_cs);
}

BOOL CRapidFinder::CheckFile(LPCTSTR lpszFileName)
{
	char string[MAX_PATH];
	char strSearch[MAX_PATH];
	
	strcpy_s(string, lpszFileName);
	strcpy_s(strSearch, m_szMatchName);
	_strupr_s(string);
	_strupr_s(strSearch);
	if (strstr(string, strSearch) != NULL)
		return TRUE;
	return FALSE;
}


