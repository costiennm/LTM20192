// Server1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")


int main()
{
    // Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket cho ket noi
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    // Gan dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    //Chap nhan ket noi
    printf("Waiting for client...\n");
    SOCKADDR_IN clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    SOCKET client = accept(listener, (SOCKADDR *) &clientAddr, &clientAddrLen);
    printf("Dia chi IP client: %s\n", inet_ntoa(clientAddr.sin_addr));

    printf("Accepted client: %d\n", client);

    char buf[256];

    //Nhan du lieu tu client
    int ret = recv(client, buf, sizeof(buf), 0);
    if (ret <= 0)
    {
        printf("Ket noi da bi dong hoac huy.");
        system("pause");
        return 1;
    }

    //Xu ly du lieu
    if (ret < sizeof(buf))
        buf[ret] = 0;
    printf("Received: %s\n", buf);

    // Doc du lieu tu ban phim va gui sang client
    while (true)
    {
        gets_s(buf);
        if (strcmp(buf, "exit") == 0) break;
        send(client, buf, strlen(buf), 0);
    }

    // Dong socket
    closesocket(client);
    closesocket(listener);

    // Giai phong Winsock
    WSACleanup();
}
