#include <stdlib.h>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

using namespace std;

char str[256];

// Kiem tra ten mien
int test(string str) {
	int i;
	for (i = 0; i < str.length(); i++) {

		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '.' || str[i] == '_');

		else break;
	}
	if (i == str.length()) return 1;
	return 0;
}

int main() {

	printf("Nhap vao ten mien: ");
	fflush(stdin);
	gets_s(str);

	if (test(str) == 0) {
		printf("Ten mien khong dung!");
		return 0;
	}

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	addrinfo* info;
	SOCKADDR_IN addr;
	int ret = getaddrinfo(str, "http", NULL, &info);
	if (ret == 0) {
		memcpy(&addr, info->ai_addr, info->ai_addrlen);
		printf("Phan giai ten mien thanh cong\n");
		printf("Dia chi IP: %s", inet_ntoa(addr.sin_addr));
	}
	else
		printf("Phan giai khong thanh cong!");
	return 0;
}