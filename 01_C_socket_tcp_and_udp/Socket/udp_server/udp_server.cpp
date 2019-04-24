// udp_server.cpp : 定义控制台应用程序的入口点。

//
//下面是一个最简单的 UDP 服务器程序 UDPServer. 它运行之后，进入无限循环，监听
//4567 端口到来的 UDP 封包，如果发现就将用户数据以字符串形式打印出来。相关代码如下。

#include "stdafx.h"
#pragma comment(lib, "WS2_32")


int main()
{
	system("title UDP_Server_2018_1_11");

	WSADATA wsaDate;
	WSAStartup(MAKEWORD(2, 2), &wsaDate);

	// 创建套接字
	SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket()\n");
	}

	// 填充 sockaddr_in 结构
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(3456);

	// 绑定这个套接字到一个本地地址
	if (SOCKET_ERROR == bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR_IN)))
	{
		printf("Failed bin()\n");
		return 0;
	}

	// 接收数据
	char szRecvBuf[1024] = "";
	SOCKADDR_IN addrClient;
	//SOCKET sockClient;   //*****UDP这里没有这个*****
	int len = sizeof(SOCKADDR_IN);


	while (true)
	{
		int nRecv = recvfrom(sockServer, szRecvBuf, 1024, 0, (SOCKADDR *)&addrClient, &len); //接收返回总的字节数

		if (nRecv > 0)
		{
			szRecvBuf[nRecv] = '\0';
			printf("接收到数据(%s):%s\n", inet_ntoa(addrClient.sin_addr), szRecvBuf);
		}

	}

	//关闭套接字
	closesocket(sockServer);

	//关闭这个库
	WSACleanup();

	return 0;
}

