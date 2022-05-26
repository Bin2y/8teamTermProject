static const int R_SIZE = 32;
const enum accessTypeR
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

unsigned int R[32]; // register

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);

void resetRegister();
