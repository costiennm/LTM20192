// Sever2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// Khoi tao thu vien
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Tao socket cho ket noi
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Giao thuc TCP

	// Khai bao dia chi server
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);

	// Gan dia chi voi socket
	bind(listener, (SOCKADDR*)&addr, sizeof(addr));

	// Chuyen sang trạng thái chờ kết nối
	listen(listener, 5);

	// Chap nhan ket noi
	while (true) {
		SOCKET client = accept(listener, NULL, NULL);

		// Nhan du lieu tu client
		char buf[2048];
		int ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0) {
			closesocket(client);
			continue;
		}

		// In ra man hinh du lieu nhan duoc
		if (ret < sizeof(buf))
			buf[ret] = 0;
		printf("%s\n", buf);

		const char* msg("HTTP/1.1 20 OK\nContent-Type: text/html\n\n <htmt><body><h1>Hello World</h1></body></html>");
		send(client, msg, strlen(msg), 0);

		closesocket(client);
	}
}

