#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));

	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(111);
	ServerSockAddr.sin_addr.s_addr = inet_addr("192.168.3.85");
	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	///////////////////
	while (true)
	{
		char Message[] = { 0, };
		cin >> Message;

		send(ServerSocket, Message, strlen(Message) + 1, 0);

		recv(ServerSocket, Message, 1024, 0);

		cout << Message << endl;
	}

	///////////////////

	closesocket(ServerSocket);

	WSACleanup();

	return 0;

}