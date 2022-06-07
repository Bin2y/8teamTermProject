#include "commands.h"
#include <stdio.h>

unsigned int getOp(unsigned int IR)
{
	return (IR & 0xFC000000) >> 26;
}
unsigned int getFn(unsigned int IR)
{
	return (IR & 0x0000003F);
}
unsigned int getRs(unsigned int IR)
{
	return (IR & 0x03E00000) >> 21;
}
unsigned int getRt(unsigned int IR)
{
	return (IR & 0x001F0000) >> 16;
}
unsigned int getRd(unsigned int IR)
{
	return (IR & 0x0000F800) >> 11;
}

unsigned int getSh(unsigned int IR)
{
	return (IR & 0x000007C0) >> 6;
}

unsigned int getOffset(unsigned int IR)
{ 
	return (int)(IR << 16) >> 16;
}

unsigned int getJOffset(unsigned int IR)
{
	return (int)(IR << 6) >> 6;
}


void go(void)
{
	int flag;
	while (1) {
		flag = step();
		if (flag == 1) {
			break;
		}
	}

}

int step(void)
{
	unsigned int op = 0, fn = 0, rs = 0, rt = 0, rd = 0, sh = 0, offset = 0, joffset = 0;
	IR = MEM(PC, 0, 0, 2);
	PC += 4;
	// instruction decode
	op = getOp(IR);
	fn = getFn(IR);
	rs = getRs(IR);
	rt = getRt(IR);
	rd = getRd(IR);
	sh = getSh(IR);
	offset = getOffset(IR);
	joffset = getJOffset(IR);
	if (op == 0)
	{
		
		if (fn == 32)
		{ // ADD
			printf("[DEBUG] add %d %d %d\n", rd, rs, rt);
			return add(rd, rs, rt);
		}
		else if (fn == 34)
		{ // SUB
			printf("[DEBUG] sub %d %d %d\n", rd, rs, rt);
			return sub(rd, rs, rt);
		}
		else if (fn == 36)
		{ // AND
			printf("[DEBUG] and %d %d %d\n", rd, rs, rt);
			return and (rd, rs, rt);
		}
		else if (fn == 37)
		{ // OR
			printf("[DEBUG] or %d %d %d\n", rd, rs, rt);
			return or (rd, rs, rt);
		}
		else if (fn == 38)
		{ // XOR
			printf("[DEBUG] xor %d %d %d\n", rd, rs, rt);
			return xor (rd, rs, rt);
		}
		else if (fn == 39)
		{ // NOR
			printf("[DEBUG] nor %d %d %d\n", rd, rs, rt);
			return nor(rd, rs, rt);
		}
		else if (fn == 42)
		{ // SLT
			printf("[DEBUG] slt %d %d %d\n", rd, rs, rt);
			return slt(rd, rs, rt);
		}
		else if (fn == 0)
		{ // SLL
			sh = getSh(IR);
			printf("[DEBUG] sll %d %d %d\n", rd, sh, rt);
			return sll(rd, sh, rt);
		}
		else if (fn == 2)
		{ // SRL
			sh = getSh(IR);
			printf("[DEBUG] srl %d %d %d\n", rd, sh, rt);
			return srl(rd, sh, rt);
		}
		else if (fn == 3)
		{ // SRA
			sh = getSh(IR);
			printf("[DEBUG] sra %d %d %d\n", rd, sh, rt);
			return sra(rd, sh, rt);
		}
		else if (fn == 24)
		{ // MUL
			printf("[DEBUG] mult %d %d\n", rd, rt);
			return mult(rs, rt);
		}
		else if (fn == 8)
		{ // jr
			printf("[DEBUG] jr %d\n", rs);
			return jr(rs);
		}
		else if (fn == 16)
		{ // mfhi
			printf("[DEBUG] mfhi %d\n", rd);
			return mfhi(rd);
		}
		else if (fn == 18)
		{ // mflo
			printf("[DEBUG] mflo %d\n", rd);
			return mflo(rd);
		}
		else if (fn == 12)
		{ // syscall
			printf("[DEBUG] syscall\n");
			return syscall();;
		}
		else
		{
			printf("[ERROR] Undefined Inst...\n");
			//goto STOP; // stop?
			return 1;
		}
	}
	else if (op == 1)
	{ // bltz
		printf("[DEBUG] bltz %d %d %d\n", rs, rt, offset);
		return bltz(rs, rt, offset);
	}
	else if (op == 2)
	{ // j
		printf("[DEBUG] j %d\n", joffset);
		return j(joffset);
	}
	else if (op == 3)
	{ // jal
		printf("[DEBUG] jal %d \n", joffset);
		return jal(joffset);
	}
	else if (op == 4)
	{ // beq
		printf("[DEBUG] beq %d %d %d\n", rs, rt, offset);
		return beq(rs, rt, offset);
	}
	else if (op == 5)
	{ // bne
		printf("[DEBUG] bne %d %d %d\n", rs, rt, offset);
		return bne(rs, rt, offset);
	}
	else if (op == 8)
	{ // addi
		printf("[DEBUG] addi %d %d %d\n", rt, rs, offset);
		return addi(rt, rs, offset);
	}
	else if (op == 10)
	{ // slti
		printf("[DEBUG] slti %d %d %d\n", rt, rs, offset);
		return slti(rt, rs, offset);
	}
	else if (op == 12)
	{ // andi
		printf("[DEBUG] andi %d %d %d\n", rt, rs, offset);
		return andi(rt, rs, offset);
	}
	else if (op == 13)
	{ // ori
		printf("[DEBUG] ori %d %d %d\n", rt, rs, offset);
		return ori(rt, rs, offset);
	}
	else if (op == 14)
	{ // xori
		printf("[DEBUG] xori %d %d %d\n", rt, rs, offset);
		return xori(rt, rs, offset);
	}
	else if (op == 15)
	{ // lui
		printf("[DEBUG] lui %d %d\n", rt, offset);
		return lui(rt, offset);
	}
	else if (op == 32)
	{ // lb
		printf("[DEBUG] lb %d %d %d\n", rt, offset, rs);
		return lb(rt, offset, rs);
	}
	else if (op == 35)
	{ // lw
		printf("[DEBUG] lw %d %d %d\n", rt, offset, rs);
		return lw(rt, offset, rs);
	}
	else if (op == 36)
	{ // lbu
		printf("[DEBUG] lbu %d %d %d\n", rt, offset, rs);
		return lbu(rt, offset, rs);
	}
	else if (op == 40)
	{ // sb
		printf("[DEBUG] sb %d %d %d\n", rt, offset, rs);
		return sb(rt, offset, rs);
	}
	else if (op == 43)
	{ // sw
		printf("[DEBUG] sw %d %d %d\n", rt, offset, rs);
		return sw(rt, offset, rs);
	}
	else
	{
		printf("[ERROR] Undefined Inst...\n");
		//goto STOP;
		return 1;
	}
	return 1;
}

unsigned int invertEndian(unsigned int data)
{
	unsigned char c[4];

	c[3] = (unsigned char)data;
	data = data >> 8;
	c[2] = (unsigned char)data;
	data = data >> 8;
	c[1] = (unsigned char)data;
	data = data >> 8;
	c[0] = (unsigned char)data;

	return *(unsigned int*)c;
}

// memory.c 사용, register.c 사용
// 바이너리 파일을 읽어서 memory에 loading 하고  PC, SP를 초기화하는 함수
void loading(char* bFileName)
{
	FILE* bFile;
	errno_t err;

	unsigned int data;
	unsigned int addr;

	unsigned int iCount; // # of instructions
	unsigned int dCount; // # of data

	err = fopen_s(&bFile, bFileName, "rb");
	if (err)
	{
		printf("[ERROR] 바이너리 파일을 열 수 없음\n");
		return;
	}

	fread(&data, sizeof(data), 1, bFile);
	iCount = invertEndian(data);
	fread(&data, sizeof(data), 1, bFile);
	dCount = invertEndian(data);

	resetMem();
	resetRegister();

	addr = 0x00400000;
	for (int i = 0; i < (int)iCount; i++)
	{
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		printf("\n");
		MEM(addr, data, WRITE, WORD);
		addr += 4;
	}

	addr = 0x10000000;
	for (int i = 0; i < (int)dCount; i++)
	{
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		MEM(addr, data, WRITE, WORD);
		addr += 4;
	}

	PC = 0x00400000;

	// 디버깅을  위한 코드
	addr = 0x00400000;
	for (int i = 0; i < (int)iCount; i++)
	{
		data = MEM(addr, 0, READ, WORD);
		printf("PROG WORD RD: A=%08x, %02x\n", addr, data);
		addr += 4;
	}
	printf("\n");
	addr = 0x10000000;
	for (int i = 0; i < (int)dCount; i++)
	{
		data = MEM(addr, 0, READ, WORD);
		printf("DATA WORD RD: A=%08x, %02x\n", addr, data);
		addr += 4;
	}
}

void setPC(unsigned int val)
{
	PC = val;
	return;
}

void jump(int address)
{
	if (address < 0x400000 || address >= 0x10000000)
	{
		printf("[ERROR] 잘못된 주소 입력 (Program 주소는 0x400000 ~ 0x10000000)\n");
	}
	else
	{
		setPC(address);
		printf("[Jump program] PC 주소: 0x%X\n", address);
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
		printf("R[%d] : 0x%8x\n", i, v); // test용으로 설정해놓은 값
	}
}

void setRegister(unsigned int num, int val)
{
	REG(num, val, WR);
}


// 메모리 보기
void viewMemory(unsigned int start, unsigned int end)
{
	for (unsigned int i = start; i <= end; i += 4)
	{
		int v = MEM(i, 0, READ, WORD);
		printf("0x%8x : 0x%9x |\n", i, v);
	}
}
// 메모리 세팅
void setMemory(unsigned int address, int value)
{
	MEM(address, value, WRITE, WORD);
}
