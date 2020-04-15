// PI_Thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <Windows.h>

DWORD WINAPI helloFunc(LPVOID p)
{
    int* pi = (int*)p;
    printf("Hello Thread %d\n", *pi);
    return 0;
}

int main()
{
    int pra[16];
    HANDLE hThread[16];
    for (int i = 0; i < 4; i++)
    {
        pra[i] = i;
        hThread[i] = CreateThread(0, 0, helloFunc, &pra[i], 0, 0);
        Sleep(1);
    }

    WaitForMultipleObjects(4, hThread, TRUE, INFINITE);
}
