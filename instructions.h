#include "ALU.h"
#include "memory.h"
#include "register.h"
extern unsigned int PC;
extern int HI;
extern int LO;

int addi(int rt, int rs, int val);
int slti(int rt, int rs, int val);
int andi(int rt, int rs, int val);
int ori(int rt, int rs, int val);
int xori(int rt, int rs, int val);
int lui(int rt, int val);
int lb(int rt, int val, int rs);
int lw(int rt, int val, int rs);
int lbu(int rt, int val, int rs);
int sb(int rt, int val, int rs);
int sw(int rt, int val, int rs);
int add(int rd, int rs, int rt);
int sub(int rd, int rs, int rt);
int and(int rd, int rs, int rt);
int or (int rd, int rs, int rt);
int xor(int rd, int rs, int rt);
int nor(int rd, int rs, int rt);
int slt(int rd, int rs, int rt);
int sll(int rd, int sh, int rt);
int srl(int rd, int sh, int rt);
int sra(int rd, int sh, int rt);
int mult(int rs, int rt);
int j(int address);
int jal(int address);
int bltz(int rs, int rt, int val);
int beq(int rs, int rt, int val);
int bne(int rs, int rt, int val);
int mfhi(int rd);
int mflo(int rd);
int jr(int rs);
int syscall();
