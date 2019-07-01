#include <Windows.h>
#include <stdio.h>

#ifdef _DEBUG
void __cdecl AfxTrace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	char szBuffer[512];
	_vsnprintf_s(szBuffer, 512, lpszFormat, args);
	::OutputDebugString(szBuffer);
	va_end(args);
}

#endif // _DEBUG


