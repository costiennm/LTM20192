// Bai2_TCPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    // Khoi tao winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    
    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chia sever
    double port;
    // printf("Nhap port:\n");
    scanf_s("%lf", &port);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    // Gan dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Cho ket noi
    listen(listener, 5);

    // Chap nhan ket noi
    SOCKET client = accept(listener, NULL, NULL);

    // Doc va gui xau trong file chao.txt cho client
    char buf1[2048];
    int ret1;
    FILE* f1 = fopen("C:\\Bai2_TCPServer\\chao.txt", "rb");

    printf("Sending: ");

    while (1)
    {
        ret1 = fread(buf1, 1, sizeof(buf1), f1);
        if (ret1 <= 0)
            break;

        send(client, buf1, ret1, 0);
    }

    // Nhan du lieu va ghi vao file client.xtx
    char buf2[2048];
    int ret2;
    FILE* f2 = fopen("C:\\Bai2_TCPServer\\client.txt", "wb");


    while (1)
    {
        ret2 = recv(client, buf2, sizeof(buf2), 0);
        if (ret2 <= 0)
            break;

        fwrite(buf2, 1, ret2, f2);
    }

    printf("\nFinished");

    fclose(f1);
    fclose(f2);

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}
