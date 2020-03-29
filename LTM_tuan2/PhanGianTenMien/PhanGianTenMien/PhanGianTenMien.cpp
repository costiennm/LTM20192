// PhanGianTenMien.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
    // Khoi tao thu vien Winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    addrinfo* info;
    SOCKADDR_IN addr;

    int ret = getaddrinfo("hust.edu.vn", "http", NULL, &info);
    if (ret == 0)
    {
        memcpy(&addr, info->ai_addr, info->ai_addrlen);
        printf("Phan giai tien mien thanh cong.\n");
        printf("Dia chi IP: %s", inet_ntoa(addr.sin_addr));
    }
}
