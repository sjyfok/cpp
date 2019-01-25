///////////////////////////////////////////////////////
// DUMPOUT.CPP�ļ�

#include <windows.h>
#include <stdio.h> // _vsnprintf function

#ifdef _DEBUG	// ֻ���ڵ���ģʽ�²ű�����ļ�

void __cdecl AfxTrace(LPCTSTR lpszFormat, ...)
{
	// ��ʽ�����ǵõ�������
	va_list args;
	va_start(args, lpszFormat);

	char szBuffer[512];
	_vsnprintf_s(szBuffer, 512, lpszFormat, args);

	// �����������
	::OutputDebugString(szBuffer);

	va_end(args);
}

#endif // _DEBUG