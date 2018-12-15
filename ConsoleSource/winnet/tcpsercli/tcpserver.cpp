#include "../netcomm/initsock.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;

CInitSock initSock;

int main(void)
{
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == INVALID_SOCKET)
	{
		cout << "Failed socket()\n";
		return 0;
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (::bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "Failed bind()\n";
		return 0;
	}

	if (::listen(sListen, 2) == SOCKET_ERROR)
	{
		cout << "Failed listen()\n";
		return 0;
	}

	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	SOCKET sClient;
	char szText[] = "TCP Server Demo!\n";
	while (true)
	{
		sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
		if (sClient == INVALID_SOCKET)
		{
			cout << "Failed accept()\n";
			continue;
		}
		char ipbuf[16];
		inet_ntop(AF_INET, &remoteAddr.sin_addr, ipbuf, 16);
		cout << "接受到一个连接: " << ipbuf;

		::send(sClient, szText, strlen(szText), 0);
		::closesocket(sClient);
	}
	::closesocket(sListen);
	return 0;
}