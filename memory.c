#include "memory.h"
#include <stdio.h>

int MEM(unsigned int A, int V, int nRW, int S)
{
    unsigned int sel = A >> 20;
    unsigned int offset = A & 0xFFFFF;
    unsigned char* pM;

    // 메모리 종류 선택
    if (sel == 0x004)
        pM = progMEM; // program memory
    else if (sel == 0x100)
        pM = dataMEM; // data memory
    else if (sel == 0x7FF)
        pM = stackMEM; // stack
    else
    {
        printf("[ERROR] 잘못된 메모리 접근\n");
        return -1;
    }

    // 워드 사이즈 선택
    int size = 0;
    if (S == BYTE)
        size = 1;
    else if (S == HALF_WORD)
        size = 2;
    else if (S == WORD)
        size = 4;

    if (nRW == 0)
    { // 메모리 읽기
        int word = 0;

        for (int i = 0; i < size; i++)
            ((unsigned char*)&word)[size - i - 1] = pM[offset + i];

        return word;
    }
    else if (nRW == WRITE)
    { // 메모리 쓰기
        for (int i = 0; i < size; i++)
            pM[offset + (size - i - 1)] = ((unsigned char*)&V)[i];
    }

    return 0;
}



// 메모리 리셋
void resetMem(void)
{
    int i;
    for (i = 0; i < 0x100000; i++)
    {
        progMEM[i] = 0;
        dataMEM[i] = 0;
        stackMEM[i] = 0;
    }
}
