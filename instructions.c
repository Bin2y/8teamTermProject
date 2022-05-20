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


// Add ~ Mult : ALU.c 와 register.c 사용
void add(int rd, int rs, int rt) {
	R[rd] = ALU(ADD, R[rs], R[rt]); 
}
void sub(int rd, int rs, int rt) {
	R[rd] = ALU(SUB, R[rs], R[rt]); 
}
void and(int rd, int rs, int rt) {
	R[rd] = ALU(AND, R[rs], R[rt]);
}
void or(int rd, int rs, int rt) {
	R[rd] = ALU(OR, R[rs], R[rt]);
}
void xor(int rd, int rs, int rt) {
	R[rd] = ALU(XOR, R[rs], R[rt]);
}
void nor(int rd, int rs, int rt) {
	R[rd] = ALU(NOR, R[rs], R[rt]);
}
void slt(int rd, int rs, int rt) {
	R[rd] = ALU(SLT, R[rs], R[rt]);
}
void sll(int rd, int sh, int rt) {
	R[rd] = ALU(SLL, sh, R[rt]);
}
void srl(int rd, int sh, int rt) {
	R[rd] = ALU(SRL, sh, R[rt]);
}
void sra(int rd, int sh, int rt) {
	R[rd] = ALU(SRA, sh, R[rt]);
}
void mult(int rs, int rt) {
	long long result;
	result = ALU(MUL, R[rs], R[rt]);
	HI = result >> 32; // register에서 정의된 변수 HI
	LO = result & 0x00000000FFFFFFFF; // register에서 정의된 변수 LO
}


