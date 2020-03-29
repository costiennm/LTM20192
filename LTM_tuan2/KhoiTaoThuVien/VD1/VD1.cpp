// VD1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    // Khoi tao thu vien Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        printf("Khoi tao thu vien that bai.");
    }
    else
    {
        printf("Khoi tao thu vien thanh cong.");
    }
}

