#include "register.h"
#include <stdio.h>

int PC = 0x400000;
unsigned int IR; // step() 에서 사용하는 변수
int HI = 0;
int LO = 0;


unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW)
{
    if (nRW > 1 || A > 31 || A < 0) // A 0~31
    {
        printf("Error: Invalid range of nRW");
        fflush(stdout);
        //exit(1);
        return 1;
    }

    if (nRW == 0) // read
    {
        return R[A];
    }
    else // write
    {
        R[A] = V;
        return 0;
    }
    return 0;
}

void resetRegister()
{
    for (int i = 0; i < R_SIZE; ++i)
    {
        REG(i, 0, WR);
    }
    R[29] = 0x80000000;

    printf("%d", $zero);
}

