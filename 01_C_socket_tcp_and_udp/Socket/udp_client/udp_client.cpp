// udp_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	// 初始化Winsock库
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 创建套节字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	// 也可以在这里调用bind函数绑定一个本地地址
	// 否则系统将会自动安排

	// 填写远程地址信息
	SOCKADDR_IN addrClient;
	char szbuf[20] = "";
	printf("请输入服务器的IP:");
	scanf("%s", szbuf);
	addrClient.sin_addr.S_un.S_addr = inet_addr(szbuf);
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(3456);

	// 注意，这里要填写服务器程序所在机器的IP地址  如果你的计算机没有联网，直接使用127.0.0.1即可
	// 发送数据
	char szSendBuf[1024] = "";
	while (true)
	{
		printf(">>");
		scanf("%s", szSendBuf);
		sendto(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0, (SOCKADDR *)&addrClient, sizeof(SOCKADDR_IN));
	}


	closesocket(sockClient);
	WSACleanup();



	return 0;
}


