#include <stdio.h>
#include <stdlib.h>

unsigned int invertEndian(unsigned int data)
{
	unsigned char c[4];

	c[3] = (unsigned char)data; data = data >> 8;
	c[2] = (unsigned char)data; data = data >> 8;
	c[1] = (unsigned char)data; data = data >> 8;
	c[0] = (unsigned char)data;

	return *(unsigned int*)c;
}


// 바이너리 파일을 읽어서 memory에 loading 하고  PC, SP 를 초기화하는 함수
void loading(char* bFileName) { 
	FILE* bFile = nullptr;
	errno_t err;

	unsigned int data;
	unsigned int addr;

	unsigned int iCount; // # of instructions
	unsigned int dCount; // # of data

	err = fopen_s(&bFile, bFileName, "rb");
	if (err) {
		printf("Cannot open binary file\n");
		return;
	}

	fread(&data, sizeof(data), 1, bFile);
	iCount = invertEndian(data); 
	fread(&data, sizeof(data), 1, bFile);
	dCount = invertEndian(data);

	resetMem();
	
	addr = PROG_START;
	for (int i = 0; i < (int)iCount; i++) {
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		MEM(addr, data, WR, WORD);
		addr += 4;
	}

	addr = DATA_START;
	for (int i = 0; i < (int)dCount; i++) {
		fread(&data, sizeof(unsigned int), 1, bFile);
		data = invertEndian(data);
		MEM(addr, data, WR, WORD);
		addr += 4;
	}

	PC = PROG_START;
	SP = STAK_END;

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


int main(void) {
	loading("as_ex01_arith.bin");
	return 0;
}

