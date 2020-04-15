// Thread1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <Windows.h>

static long num_steps = 100000;
double step, pi;

int i;
double x1, x2, sum, sum1, sum2;
step = 1.0 / (double)num_steps;

DWORD WINAPI Sum1(LPVOID p)
{
    x1 = ((1 + num_steps) * num_steps / 2 + num_steps / 4) * step;
    sum1 = 
    return 0;
}

DWORD WINAPI Sum2(LPVOID p)
{
    x2 = (num_steps * num_steps / 2 + num_steps / 4) * step;
    return 0;
}

int main()
{
    HANDLE hThread1 = CreateThread(0, 0, Sum1, 0, 0, 0);
    HANDLE hThread2 = CreateThread(0, 0, Sum2, 0, 0, 0);

    HANDLE hThreads[2];
    hThreads[0] = hThread1;
    hThreads[1] = hThread2;

    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);


    printf("finish.");
}
