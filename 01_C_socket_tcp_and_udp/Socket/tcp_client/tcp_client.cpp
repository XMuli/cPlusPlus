// tcp_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "WS2_32")


int main()
{
	system("title TCP客户端");

	//检查协议栈是否可使用
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("error:  WSAStartup() faile...\n");
		return -1;
	}

	//创建客户端的套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET == sockClient)
	{
		printf("error:  socket() faile...:%d\n", WSAGetLastError());
		return -1;
	}

	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	char szInIP[30] = "";
	printf("请输入对方IP地址（同局域网）：eg:127.0.0.1\nIP>>");
	scanf("%s", szInIP);
	addrServer.sin_addr.S_un.S_addr = inet_addr(szInIP);
	addrServer.sin_port = htons(2000);

	//请求与服务器建立TCP连接
	if (INVALID_SOCKET == connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)))
	{
		printf("error:  connect() faile...:%d\n", WSAGetLastError());
		return -1;
	}
		

	char szRecvBuf[2048] = "";
	char szSendBuf[2048] = "客户端已经连接成功";


	while (true)
	{
		printf(">>");
		scanf("%s", szSendBuf);
		send(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0);
		/*recv(sockClient, szRecvBuf, sizeof(szRecvBuf), 0);
		printf("客户端:%s \n", szRecvBuf);*/

	}




	

	closesocket(sockClient);


	WSACleanup();
    return 0;
}

