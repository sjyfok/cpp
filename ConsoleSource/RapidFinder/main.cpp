#include <iostream>
#include <process.h>
#include "RapidFinder.h"

using namespace std;


UINT FinderEntry(LPVOID lpParam)
{
	CRapidFinder *pFinder = (CRapidFinder*)lpParam;
	CDirectoryNode *pNode = NULL;
	BOOL bActive = TRUE;
	while (true)
	{
		::EnterCriticalSection(&pFinder->m_cs);
		if (pFinder->m_listDir.IsEmpty())
		{
			bActive = FALSE;
		}
		else
		{
			pNode = pFinder->m_listDir.GetHead();
			pFinder->m_listDir.Remove(pNode);
		}
		::LeaveCriticalSection(&pFinder->m_cs);
		if (!bActive)
		{
			::EnterCriticalSection(&pFinder->m_cs);
			pFinder->m_nThreadCount--;
			if (pFinder->m_nThreadCount == 0)
			{
				::LeaveCriticalSection(&pFinder->m_cs);
				break;
			}
			::LeaveCriticalSection(&pFinder->m_cs);
			ResetEvent(pFinder->m_hDirEvent);
			::WaitForSingleObject(pFinder->m_hDirEvent, INFINITE);
			::EnterCriticalSection(&pFinder->m_cs);
			pFinder->m_nThreadCount++;
			::LeaveCriticalSection(&pFinder->m_cs);
			bActive = TRUE;
			continue;
		}

		WIN32_FIND_DATA fileData;
		HANDLE hFindFile;
		if (pNode->szDir[strlen(pNode->szDir) - 1] != '\\')
			strcat(pNode->szDir, "\\");
		strcat(pNode->szDir, "*.*");
		hFindFile = ::FindFirstFile(pNode->szDir, &fileData);
		if (hFindFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (fileData.cFileName[0] == '.')
					continue;
				if (fileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				{
					CDirectoryNode *p = new CDirectoryNode;
					strncpy(p->szDir, pNode->szDir, strlen(pNode->szDir) - 3);
					strcat(p->szDir, fileData.cFileName);
					::EnterCriticalSection(&pFinder->m_cs);
					pFinder->m_listDir.AddHead(p);
					::LeaveCriticalSection(&pFinder->m_cs);
					::SetEvent(pFinder->m_hDirEvent);
				}
				else
				{
					if (pFinder->CheckFile(fileData.cFileName))
					{
						::EnterCriticalSection(&pFinder->m_cs);
						::InterlockedIncrement((long*)&pFinder->m_nResultCount);
						::LeaveCriticalSection(&pFinder->m_cs);
						printf(" %s\n", fileData.cFileName);
						
					}
				}
			} while (::FindNextFile(hFindFile, &fileData));
		}
		delete pNode;
		pNode = NULL;
	}
	::SetEvent(pFinder->m_hDirEvent);
	if (::WaitForSingleObject(pFinder->m_hDirEvent, 0) != WAIT_TIMEOUT)
	{
		::SetEvent(pFinder->m_hExitEvent);
	}
	return 0;
}


int main(void)
{
	CRapidFinder *pFinder = new CRapidFinder(1);
	CDirectoryNode *pNode = new CDirectoryNode;

	char szPath[] = "C:\\";
	char szFile[] = "stdafx";

	strcpy(pNode->szDir, szPath);
	pFinder->m_listDir.AddHead(pNode);
	strcpy(pFinder->m_szMatchName, szFile);
	pFinder->m_nThreadCount = pFinder->m_nMaxThread;
	

	for (int i = 0; i < pFinder->m_nMaxThread; i++)
	{
		AfxBeginThread(FinderEntry, pFinder);
	
	}
	::WaitForSingleObject(pFinder->m_hExitEvent, INFINITE);
	printf("最终查找到的文件的个数为: %d\n", pFinder->m_nResultCount);
	delete pFinder;
	system("pause");
	return 0;
}

