// tcp_server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "WS2_32")


int main()
{
	system("title TCP服务器");

	//检查协议栈是否可使用
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("error:  WSAStartup() faile...\n");
		return -1;
	}

	printf("服务器已经启动...\n");

	//创建服务器端的套接字
	SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

	//建立服务器端的地址
	SOCKADDR_IN addrSrever;
	addrSrever.sin_family = AF_INET;
	addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrever.sin_port = htons(2000);

	//绑定套接字
	if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
	{
		printf("error:  bind() faile...:%d\n", WSAGetLastError());
		return -1;
	}

	//监听
	if (SOCKET_ERROR == listen(SockServer, 5))
	{
		printf("error:  listen() faile...:%d\n", WSAGetLastError());
		return -1;
	}
	printf("服务器监听中...\n");
	
	//初始化客户地址长度参数
	int len = sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;
	char szSendBuf[2048] = "已经连接服务器成功";
	char szRecvBuf[2048] = "";

	//等待客户的连接请求,接收请求连接
	SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
	if (INVALID_SOCKET == sockAccept)
	{
		printf("error:  accept() faile...:%d\n", WSAGetLastError());
		return -1;
	}

	//输出连接成功的客户IP和端口号
	printf("Accepted client IP:[%s], prot:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

	//进入一个无限循环，
	while (true)
	{

	    recv(sockAccept, szRecvBuf, sizeof(szRecvBuf), 0);
	    printf("客户端:%s \n", szRecvBuf);
	    /*printf(">>");
	    scanf("%s", szSendBuf);
	    send(SockServer, szSendBuf, strlen(szSendBuf) + 1, 0);*/

	}
	
	//关闭套接字
	closesocket(SockServer);
	//关闭协议栈的检查
	WSACleanup();


    return 0;
}

