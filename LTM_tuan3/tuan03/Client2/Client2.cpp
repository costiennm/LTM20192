// Client2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
    // Khoi tao winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket client
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Phan giai ten mien
    SOCKADDR_IN addr;
    addrinfo* info;

    int ret = getaddrinfo("bunoc.net", "http", NULL, &info);
    if (ret != 0)
    {
        printf("Khong phan giai duoc ten mien.");
        return 1;
    }

    // Copy dia chi tu info sang addr
    memcpy(&addr, info->ai_addr, info->ai_addrlen);

    // Ket noi den server
    ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        printf("Ket noi khong thanh cong.");
        return 1;
    }

    const char* msg = "HEAD /test.jpg HTTP/1.1\r\nHost: bunoc.net\r\n\r\n";
    send(client, msg, strlen(msg), 0);

    char buf[2048];
    while (true)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        if (ret < sizeof(buf))
            buf[ret] = 0;

        printf("%s", buf);

        // Lay kich thuoc file
        char* post1 = strstr(buf, "Content-Length");
        if (post1 != NULL)
        {
            char* post2 = strstr(post1, "\r\n");
            post1[post2 - post1] = 0;
            
            printf("%s", post1);
            int filesize = atoi(post1 + 16);
            printf("\nFile size: %d bytes", filesize);
        }
    }



    closesocket(client);
    WSACleanup();
}
