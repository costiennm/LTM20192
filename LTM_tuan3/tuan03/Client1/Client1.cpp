// Client1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    // Khoi tao socket
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Khai bao socket client
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi cua server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    // Ket noi
    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("connect() failed: error code %d\n", ret);
        return 1;
    }

    // Gui message sang server
    char buf[256] = "Hello Server. I am a new client.";
    send(client, buf, strlen(buf), 0);

    // Nhan du lieu tu server
    while (true)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            printf("Connect lost.\n");
            break;
        }

        // Xu ly du lieu nhan duoc
        if (ret < sizeof(buf))
            buf[ret] = 0;
        printf("Recived: %s\n", buf);
    }
    closesocket(client);
    WSACleanup();
}
