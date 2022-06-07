#include "instructions.h"
#include <stdio.h>

// addi,slti,andi,ori,xori
// lb,lw,lbu,sb,sw

int addi(int rt, int rs, int val) // andi(destination, start, value)
{
    R[rt] = ALU(ADD, R[rs], val);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int slti(int rt, int rs, int val)
{
    R[rt] = ALU(SLT, R[rs], val);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int andi(int rt, int rs, int val)
{
    R[rt] = ALU(AND, R[rs], val);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int ori(int rt, int rs, int val)
{
    R[rt] = ALU(OR, R[rs], val);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int xori(int rt, int rs, int val)
{
    R[rt] = ALU(XOR, R[rs], val);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int lui(int rt, int val)
{
    R[rt] = (val & 0x0000ffff) << 16;
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int lb(int rt, int val, int rs)
{
    R[rt] = MEM(R[rs] + val, 0, READ, BYTE); 
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int lw(int rt, int val, int rs)
{
    R[rt] = MEM(R[rs] + val, 0, READ, WORD);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int lbu(int rt, int val, int rs)
{
    R[rt] = MEM(R[rs] + val, 0, READ, BYTE);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rt, R[rt]);
    return 0;
}

int sb(int rt, int val, int rs)
{
    MEM(R[rs] + val, R[rt], WRITE, BYTE);
    printf("[DEBUG] Memory Changed : 0x%8x = 0x%9x\n",
        R[rs] + val, MEM(R[rs] + val, 0, READ, BYTE));
    return 0;
}

int sw(int rt, int val, int rs)
{
    MEM(val + R[rs], R[rt], WRITE, WORD);
    printf("[DEBUG] Memory Changed : 0x%8x = 0x%9x\n",
        R[rs] + val, MEM(R[rs] + val, 0, READ, WORD));
    return 0;
}

// Add ~ Mult : ALU.c 와 register.c 사용

int add(int rd, int rs, int rt)
{
    R[rd] = ALU(ADD, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int sub(int rd, int rs, int rt)
{
    R[rd] = ALU(SUB, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int and (int rd, int rs, int rt)
{
    R[rd] = ALU(AND, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int or (int rd, int rs, int rt)
{
    R[rd] = ALU(OR, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int xor (int rd, int rs, int rt) {
    R[rd] = ALU(XOR, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
} 
int nor(int rd, int rs, int rt)
{
    R[rd] = ALU(NOR, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int slt(int rd, int rs, int rt)
{
    R[rd] = ALU(SLT, R[rs], R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int sll(int rd, int sh, int rt)
{
    R[rd] = ALU(SLL, sh, R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int srl(int rd, int sh, int rt)
{
    R[rd] = ALU(SRL, sh, R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int sra(int rd, int sh, int rt)
{
    R[rd] = ALU(SRA, sh, R[rt]);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}
int mult(int rs, int rt)
{
    long long result;
    result = ALU(MUL, R[rs], R[rt]);
    HI = result >> 32;                // register에서 정의된 변수 HI
    LO = result & 0x00000000FFFFFFFF; // register에서 정의된 변수 LO
    printf("[DEBUG] Register Changed : HI = 0x%8x\n", HI);
    printf("[DEBUG] Register Changed : LO = 0x%8x\n", LO);
    return 0;
}

// bltz,j,jal,beq,bne
// mfhi,mflo
// jr

int j(int address)
{
    PC = (PC & 0xF0000000) | (address << 2); // register의 PC값
    printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    return 0;
}


int jal(int address) {
    R[$ra] = PC;
    PC = ((PC + 4) & 0xf0000000) | (address << 2);
    printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", $ra, R[$ra]);
    return 0;
}

//int jal(int address)
//{
//    PC = (PC & 0xF0000000) | (address << 2);
//    R[$ra] = PC + 4; // 다음 명령어의 주소를 $ra에 넣음
//    printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
//    printf("[DEBUG] Register Changed : R[%d] = 0x%8x\n", $ra, R[$ra]);
//    return 0;
//}

int bltz(int rs, int rt, int val)
{
    if (R[rs] < R[rt]) {
        PC += val * 4;
        printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    }
    return 0;
}

int beq(int rs, int rt, int val)
{

    if (R[rs] == R[rt]) {
        PC += val * 4;
        printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    }
    return 0;
}

int bne(int rs, int rt, int val)
{

    if (R[rs] != R[rt]) {
        PC += val * 4;
        printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    }
    return 0;
}

int mfhi(int rd)
{
    R[rd] = HI; // register의 HI값
    printf("[DEBUG] Register Changed R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}

int mflo(int rd)
{
    R[rd] = LO; // register의 LO값
    printf("[DEBUG] Register Changed R[%d] = 0x%8x\n", rd, R[rd]);
    return 0;
}

int jr(int rs)
{
    PC = R[rs];
    printf("[DEBUG] PC Changed : PC = 0x%9x\n", PC);
    return 0;
}

int syscall()
{
    if (R[$v0] == 10)
    {
        printf("    syscall 10 : Exit program\n");
        return 1;
    }
    else
        return 0;
}
