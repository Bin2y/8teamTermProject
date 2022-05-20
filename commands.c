unsigned int IR; // step() 에서 사용하는 변수

unsigned int getOp(unsigned int IR) {
	return (IR & 0xFC000000) >> 26;
}
unsigned int getFn(unsigned int IR) {
	return (IR & 0x0000003F);
}
unsigned int getRs(unsigned int IR) {
	return (IR & 0x03E00000) >> 21;
}
unsigned int getRt(unsigned int IR) {
	return (IR & 0x001F0000) >> 16;
}
unsigned int getRd(unsigned int IR) {
	return (IR & 0x0000F800) >> 11;
}

unsigned int getSh(unsigned int IR) {
	return (IR & 0x000007C0) >> 6;
}

unsigned int getOffset(unsigned int IR) { // 16비트, I type - addi, lw, sw, lb, sb, andi, beq, blt, slti, ...
	return (IR & 0x0000FFFF);
}

unsigned int getJOffset(unsigned int IR) { // 26비트, J type - j
	return (IR & 0x03FFFFFF);
}


int step(void) {
	unsigned int op, fn, rs, rt, rd, offset;
	IR = MEM(PC, 0, 0, 2); PC += 4;
	// instruction decode
	op = getOp(IR);

	if (op == 0) {
		fn = getFn(IR); rs = getRs(IR);
		rt = getRt(IR); rd = getRd(IR);
		if (fn == 32) { // ADD
			return add(rd, rs, rt);
		}
		else if (fn == 34) { // SUB
			return sub(rd, rs, rt);
		}
		else if (fn == 36) { // AND
			return and(rd, rs, rt);
		}
		else if (fn == 37) { // OR
			return or(rd, rs, rt);
		}
		else if (fn == 38) { // XOR
			return xor(rd, rs, rt);
		}
		else if (fn == 39) { // NOR
			return nor(rd, rs, rt);
		}
		else if (fn == 42) { // SLT
			return slt(rd, rs, rt);
		}
		else if (fn == 0) { // SLL
			sh = getSh(IR);
			return sll(rd, sh, rt);
		}
		else if (fn == 2) { // SRL
			sh = getSh(IR);
			return srl(rd, sh, rt);
		}
		else if (fn == 3) { // SRA
			sh = getSh(IR);
			return sra(rd, sh, rt);
		}
		else if (fn == 24) { // MUL
			return mult(rs, rt);
		}
		else if (fn == 8) { // jr

		}
		else if (fn == 16) { // mfhi

		}
		else if (fn == 18) { // mflo

		}
		else if (fn == 12) { // syscall

		}
		else {
			printf("Undefined Inst...");
			goto STOP; // stop?
		}
	}
	else if (op == 1) { // bltz
		offset = getOffset(IR);

	}
	else if (op == 2) { // j

	}
	else if (op == 3) { // jal

	}
	else if (op == 4) { // beq

	}
	else if (op == 5) { // bne

	}
	else if (op == 8) { // addi

	}
	else if (op == 10) { // slti

	}
	else if (op == 12) { // andi

	}
	else if (op == 13) { // ori

	}
	else if (op == 14) { // xori

	}
	else if (op == 15) { // lui
		
	}
	else if (op == 32) { // lb

	}
	else if (op == 35) { // lw

	}
	else if (op == 36) { // lbu

	}
	else if (op == 40) { // sb

	}
	else if (op == 43) { // sw

	}
	else {
	printf("Undefined Inst...");
	goto STOP; 
	}
	
	return 1;

}

unsigned int invertEndian(unsigned int data)
{
	unsigned char c[4];

	c[3] = (unsigned char)data; data = data >> 8;
	c[2] = (unsigned char)data; data = data >> 8;
	c[1] = (unsigned char)data; data = data >> 8;
	c[0] = (unsigned char)data;

	return *(unsigned int*)c;
}

// memory.c 사용, register.c 사용 
// 바이너리 파일을 읽어서 memory에 loading 하고  PC, SP를 초기화하는 함수
void loading(char* bFileName) { 
	FILE* bFile;
	errno_t err;

	unsigned int data;
	unsigned int addr;

	unsigned int iCount; // # of instructions
	unsigned int dCount; // # of data

	err = fopen_s(&bFile, bFileName, "rb");
	if (err) {
		printf("[DEBUG] 바이너리 파일을 열 수 없음\n");
		return;
	}

	fread(&data, sizeof(data), 1, bFile);
	iCount = invertEndian(data); 
	fread(&data, sizeof(data), 1, bFile);
	dCount = invertEndian(data);

	resetMem();
	
	addr = 0x00400000;
	for (int i = 0; i < (int)iCount; i++) {
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		printf("\n");
		MEM(addr, data, WRITE, WORD);
		addr += 4;
	}

	addr = 0x10000000;
	for (int i = 0; i < (int)dCount; i++) {
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		MEM(addr, data, WRITE, WORD);
		addr += 4;
	}

	PC = 0x00400000;
	SP = 0x80000000;

	// 디버깅을  위한 코드
	addr = 0x00400000;
	for (int i = 0; i < (int)iCount; i++) {
		data = MEM(addr, 0, READ, WORD);
		printf("(test) PROG WORD RD: A=%08x, %02x\n", addr, data);
		addr += 4;
	}
	printf("\n");
	addr = 0x10000000;
	for (int i = 0; i < (int)dCount; i++) {
		data = MEM(addr, 0, READ, WORD);
		printf("(test) DATA WORD RD: A=%08x, %02x\n", addr, data);
		addr += 4;
	}
	
}

// 9주차 강의 자료에 있는 코드
void setPC(unsigned int val) {
	PC = val;
	return;
}

void jump(int address) {
	if (address < 0x400000 || address >= 0x10000000) {
		printf("[ERROR] 잘못된 주소 입력 (Program 주소는 0x400000 ~ 0x10000000)\n");
	}
	else {
		printf("[Jump program] PC 주소: 0x%X\n", address);
		setPC(address);
	}
}
