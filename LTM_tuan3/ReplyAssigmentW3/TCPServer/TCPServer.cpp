// TCPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable: 4996)

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("So tham so phai la 4\n");
        return 1;
    }
    // Khoi tao winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    // Cho ket noi
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    // Chap nhan ket noi
    SOCKET client = accept(listener, NULL, NULL);

    // Doc cau chao tu file va gui cho client
    FILE* f = fopen(argv[2], "r");
    char buf[256];
    int ret;
    fgets(buf, sizeof(buf), f);
    fclose(f);
    send(client, buf, strlen(buf), 0);

    // Nhan du lieu tu client va luu vao file
    f = fopen(argv[3], "w");
    while (true)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        buf[ret] = 0;
        printf("%s\n", buf);
        fprintf(f, "%s\n", buf);
    }

    fclose(f);
    closesocket(client);
    closesocket(listener);
    WSACleanup();
}
