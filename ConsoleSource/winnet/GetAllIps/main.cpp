#include <iostream>
#include "../netcomm/initsock.h"
#include "WS2tcpip.h"

#include "Iphlpapi.h"
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "WS2_32.lib")

CInitSock initSock;
using namespace std;

bool GetClobalData(void);

int main(void)
{
	char szHost[256];
	::gethostname(szHost, 256);
	addrinfo *res, *cur;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	int ret = getaddrinfo(szHost, NULL, &hints, &res);
	
	sockaddr_in *addr;
	char ipbuf[16];
	for (cur = res; cur != NULL;  cur = cur->ai_next)
	{
		addr = (struct sockaddr_in *)cur->ai_addr;
		PCSTR szIp = inet_ntop(AF_INET, &addr->sin_addr, ipbuf, 16);

		
		cout << "本机IP地址: " << szIp << endl;
	}
	
	GetClobalData();
	return 0;
}

u_char g_ucLocalMac[6];
DWORD g_dwGatewayIP;
DWORD g_dwLocalIP;
DWORD g_dwMask;

bool GetClobalData(void)
{
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	ULONG ulLen = 0;
	::GetAdaptersInfo(pAdapterInfo, &ulLen);
	pAdapterInfo = (PIP_ADAPTER_INFO)::GlobalAlloc(GPTR, ulLen);

	if (::GetAdaptersInfo(pAdapterInfo, &ulLen) == ERROR_SUCCESS)
	{
		if (pAdapterInfo != NULL)
		{
			memcpy(g_ucLocalMac, pAdapterInfo->Address, 6);
			InetPton(AF_INET, pAdapterInfo->GatewayList.IpAddress.String, &g_dwGatewayIP);
			InetPton(AF_INET, pAdapterInfo->IpAddressList.IpAddress.String, &g_dwLocalIP);
			InetPton(AF_INET, pAdapterInfo->IpAddressList.IpMask.String, &g_dwMask);		
		}
	}
	cout << "----------本地主机信息---------------" << endl;
	in_addr in;
	char ipbuf[16];
	in.S_un.S_addr = g_dwLocalIP;
	PCSTR szIp = inet_ntop(AF_INET, &in.S_un.S_addr, ipbuf, 16);
	cout << "IP 地址: " << szIp << endl;
	in.S_un.S_addr = g_dwGatewayIP;
	szIp = inet_ntop(AF_INET, &in.S_un.S_addr, ipbuf, 16);
	cout << "网关: " << szIp << endl;
	in.S_un.S_addr = g_dwMask;
	szIp = inet_ntop(AF_INET, &in.S_un.S_addr, ipbuf, 16);
	cout << "子网掩码: " << szIp << endl;
	
	cout << "MAC: ";
	
	/*cout << showbase << hex << g_ucLocalMac[0] << endl;*/
	//cout << g_ucLocalMac[0] << '-';
	printf("%2X %2X %2X %2X %2X %2X", g_ucLocalMac[0], g_ucLocalMac[1], g_ucLocalMac[2], g_ucLocalMac[3], g_ucLocalMac[4],
		g_ucLocalMac[5]);
	cout << endl;
	
	
	return true;
}