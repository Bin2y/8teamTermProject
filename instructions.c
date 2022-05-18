// addi,slti,andi,ori,xori
// lb,lw,lbu,sb,sw

int andi(int rt, int rs, int val) // andi(destination, start, value)
{
  R[rt] = ALU(add, R[rs], val);
  return 0;
}

int slti(int rt, int rs, int val)
{
  R[rt] = ALU(SLT, R[rs], val);
  return 0;
}

int andi(int rt, int rs, int val)
{
  R[rt] = ALU(AND, R[rs], val);
  return 0;
}

int ori(int rt, int rs, int val)
{
  R[rt] = ALU(OR, R[rs], val);
  return 0;
}

int xori(int rt, int rs, int val)
{
  R[rt] = ALU(XOR, R[rs], val);
  return 0;
}

int lb(int rt, int val, int rs)
{
  R[rt] = MEM(R[rs] + val, 0, RD, BYTE);
  return 0;
}

int lw(int rt, int val, int rs)
{
  R[rt] = MEM(R[rs] + val, 0, RD, WORD);
  return 0;
}

int lbu(int rt, int val, int rs)
{
  R[rt] = MEM(R[rs] + val, 0, RD, BYTE);
  return 0;
}

int sb(int rt, int val, int rs)
{
  MEM(R[rs] + val, R[rt], WR, BYTE);
  return 0;
}

int sw(int rt, int val, int rs)
{
  MEM(val + R[rs], R[rt], WR, WORD);
  return 0;
}