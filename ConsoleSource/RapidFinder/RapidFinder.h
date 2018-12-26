#ifndef __RAPIDFINDER_H__
#define __RAPIDFINDER_H__

#include "../wincommon/_afxwin.h"
struct CDirectoryNode : public CNoTrackObject
{
	CDirectoryNode *pNext;
	char szDir[MAX_PATH];
};

class CRapidFinder
{
public:
	CRapidFinder(int nMaxThrad);
	virtual ~CRapidFinder();
	BOOL CheckFile(LPCTSTR lpszFileName);
	int m_nResultCount;
	int m_nThreadCount;
	CTypedSimpleList<CDirectoryNode*>m_listDir;
	CRITICAL_SECTION m_cs;
	const int m_nMaxThread;
	char m_szMatchName[MAX_PATH];
	HANDLE m_hDirEvent;
	HANDLE m_hExitEvent;
};
#endif // !__RAPIDFINDER_H__
