// Bai1_TCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    // Khoi tao winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket client
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Phan giai ten mien
    char str[256];
    // printf("Nhap dia chi IP: \n");
    fflush(stdin);
    gets_s(str);
    SOCKADDR_IN serveraddr;
    addrinfo* info;

    int rets = getaddrinfo(str, "http", NULL, &info);
    if (rets != 0)
    {
        return 1;
    }

    // Copy dia chi tu info sang addr
    memcpy(&serveraddr, info->ai_addr, info->ai_addrlen);

    double port;
    // printf("Nhap Port: \n");
    scanf_s("%lf", &port);

    // Khai bao dia chi server 
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(str);
    addr.sin_port = htons(port);

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("connect() failed: error code %d\n", ret);
        return 1;
    }

    // Doc du lieu tu file va gui sang server
    char buf[256];

    printf("Message:\n");
    
    // Gui du lieu den server
    while (1)
    {
        gets_s(buf);
        if (strcmp(buf, "exit") == 0) break;
        send(client, buf, strlen(buf), 0);
    }



    closesocket(client);
    WSACleanup();
}
