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
	fd_set fdSocket;
	FD_ZERO(&fdSocket);
	FD_SET(sListen, &fdSocket);
	while (true)
	{
		fd_set fdRead = fdSocket;
		int nRet = ::select(0, &fdSocket, NULL, NULL, NULL);
		if (nRet > 0)
		{
			for (int i = 0; i < (int)fdSocket.fd_count; i++)
			{
				if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
				{
					if (fdSocket.fd_array[i] == sListen)
					{
						if (fdSocket.fd_count < FD_SETSIZE)
						{
							sockaddr_in addrRemote;
							int nAddrLen = sizeof(addrRemote);
							SOCKET sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);
							FD_SET(sNew, &fdSocket);
							char ipbuf[16];
							inet_ntop(AF_INET, &addrRemote.sin_addr, ipbuf, 16);
							cout << "接收到连接 : " << ipbuf << endl;
						}
						else
						{
							cout << "Too much connecttions!\n";
							continue;
						}
					}
					else
					{
						char szText[256];
						int nRecv = ::recv(fdSocket.fd_array[i], szText, strlen(szText), 0);
						if (nRecv > 0)
						{
							szText[nRecv] = '\0';
							cout << "接收到数据: " << szText << endl;
						}
						else
						{
							closesocket(fdSocket.fd_array[i]);
							FD_CLR(fdSocket.fd_array[i], &fdSocket);
						}

					}
				}
			}
		}
		else
		{
			cout << "Fail select\n";
			break;
		}
	}
	return 0;
	//sockaddr_in remoteAddr;
	//int nAddrLen = sizeof(remoteAddr);
	//SOCKET sClient;
	//char szText[] = "TCP Server Demo!\n";
	//while (true)
	//{
	//	sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
	//	if (sClient == INVALID_SOCKET)
	//	{
	//		cout << "Failed accept()\n";
	//		continue;
	//	}
	//	char ipbuf[16];
	//	inet_ntop(AF_INET, &remoteAddr.sin_addr, ipbuf, 16);
	//	cout << "接受到一个连接: " << ipbuf;

	//	::send(sClient, szText, strlen(szText), 0);
	//	::closesocket(sClient);
	//}
	//::closesocket(sListen);
	//return 0;
}