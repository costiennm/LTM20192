// TPCClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("So tham so phai la 3\n");
        return 1;
    }
    // Khoi tao winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Gan dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    // Tam dung cho server vao trang thai cho ket noi
    system("pause");

    // Ket noi
    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));

    // Kiem tra ket noi
    if (ret == SOCKET_ERROR)
        return 1;

    // Nhan du lieu tu server
    char buf[256];
    ret = recv(client, buf, sizeof(buf), 0);
    if (ret <= 0)
    {
        closesocket(client);
        return 1;
    }

    // In ra du lieu nhan duoc
    buf[ret] = 0;
    printf("Recviced: %s\n", buf);

    // Nhap du lieu tu ban phim va gui cho server
    while (true)
    {
        printf("Enter a mesage: \n");
        gets_s(buf);

        if (strcmp(buf, "exit") == 0)
            break;

        send(client, buf, strlen(buf), 0);
    }

    // Dong socket va giai phong winsock
    closesocket(client);
    WSACleanup();
}
