#include "../netcomm/initsock.h"
#include <iostream>
#include "WS2tcpip.h"

using namespace std;

CInitSock initSock;
int main(void)
{
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		cout << "Failed socket\n";
		return 0;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(23042);
	inet_pton(AF_INET, "192.168.0.30", &servAddr.sin_addr.S_un.S_addr);// inet_addr("127.0.0.1");
	if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
	{
		cout << "Failed connect\n";
		return 0;
	}
	char buff[256];
	int nRecv = ::recv(s, buff, 256, 0);
	if (nRecv > 0)
	{
		buff[nRecv] = '\0';
		cout << "接受到数据: " << buff << endl;
	}
	::closesocket(s);
	return 0;
}