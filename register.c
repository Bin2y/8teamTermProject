#include <stdio.h>
#include <stdlib.h>

const int R_SIZE = 32;
enum accessType
{
  RD,
  WR
};
enum REGISTER_ENUM
{
  $zero,
  $at,
  $v0,
  $v1,
  $a0,
  $a1,
  $a2,
  $a3,
  $t0,
  $t1,
  $t2,
  $t3,
  $t4,
  $t5,
  $t6,
  $g7,
  $s0,
  $s1,
  $s2,
  $s3,
  $s4,
  $s6,
  $s7,
  $t8,
  $t9,
  $k0,
  $k1,
  $gp,
  $sp,
  $fp,
  $ra
};
const int PC = 0x4000000;
int HI = 0;
int LO = 0;
unsigned int R[32]; // register
unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW)
{
  if (nRW > 1 || A > 31 || A < 0) // A 0~31
  {
    printf("Error: Invalid range of nRW");
    fflush(stdout);
    exit(1);
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
}

void resetRegister()
{
  for (int i = 0; i < R_SIZE; ++i)
  {
    REG(i, 0, WR);
  }
}

void viewRegister()
{
  printf("pc : %8x\n", PC);
  printf("HI : %8x\n", HI);
  printf("LO : %8x\n", LO);

  for (int i = 0; i < R_SIZE; i++)
  {
    unsigned int v = REG(i, 0, RD);
    printf("R[%d] : %8x\n", i, v); // test용으로 설정해놓은 값
  }
}
int main()
{
  resetRegister();
  viewRegister();
  return 0;
}
