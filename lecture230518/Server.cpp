#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN ListenSockAddr;
	ZeroMemory(&ListenSockAddr, sizeof(ListenSockAddr));

	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = inet_addr("192.168.3.85");
	ListenSockAddr.sin_port = htons(111);

	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, 0);

	SOCKADDR_IN ClientSockAddr;
	ZeroMemory(&ClientSockAddr, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	///////////////////
	while (true)
	{
		char Message[1024] = { 0, };
		recv(ClientSocket, Message, 1024, 0);

		string strMessage = (string)Message;
		int OperatorIndexPlus = strMessage.find("+");
		int OperatorIndexMinus = strMessage.find("-");
		int OperatorIndexMultiply = strMessage.find("*");
		int OperatorIndexDivide = strMessage.find("/");
		int OperatorIndex = -1;

		if (OperatorIndexPlus != -1)
		{
			OperatorIndex = OperatorIndexPlus;
		}
		else if (OperatorIndexMinus != -1)
		{
			OperatorIndex = OperatorIndexMinus;
		}
		else if (OperatorIndexMultiply != -1)
		{
			OperatorIndex = OperatorIndexMultiply;
		}
		else if (OperatorIndexDivide != -1)
		{
			OperatorIndex = OperatorIndexDivide;
		}

		string strInt1 = strMessage.substr(0, OperatorIndex);
		string strInt2 = strMessage.substr(OperatorIndex + 1, strMessage.length());

		const char* ccInt1 = strInt1.c_str();
		int Int1 = atoi(ccInt1);
		const char* ccInt2 = strInt2.c_str();
		int Int2 = atoi(ccInt2);
		int ResultInt = 0;

		if (OperatorIndexPlus != -1)
		{
			ResultInt = Int1 + Int2;
		}
		else if (OperatorIndexMinus != -1)
		{
			ResultInt = Int1 - Int2;
		}
		else if (OperatorIndexMultiply != -1)
		{
			ResultInt = Int1 * Int2;
		}
		else if (OperatorIndexDivide != -1)
		{
			ResultInt = Int1 / Int2;
		}

		_itoa_s(ResultInt, Message, 10);
		send(ClientSocket, Message, strlen(Message) + 1, 0);
	}
	///////////////////

	closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();

	return 0;
}





