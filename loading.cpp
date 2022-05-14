#include "stdio.h"
#include "stdlib.h"
#include <iostream>

#define PROG_START	0x00400000
#define PROG_END	0x00500000
#define DATA_START	0x10000000
#define DATA_END	0x10100000
#define STAK_START	0x7FF00000
#define STAK_END	0x80000000

unsigned int PC;
unsigned int SP;

const enum accessType { RD, WR };
enum accessSize { BYTE, HALF, WORD };

const int M_SIZE = 0x100000;
unsigned char progMEM[M_SIZE], dataMEM[M_SIZE], stakMEM[M_SIZE];

int MEM(unsigned int A, int V, int nRW, int S) {

	unsigned int memSelect, offset; // A = memSelect << 20 + offset
	unsigned char* pM;
	//	unsigned char cdata;
	//	unsigned short int sdata;
	//	unsigned int idata;

	if (nRW > 1 || S > 2) {
		printf("Error: Invalid range of nRW or S"); fflush(stdout);
		exit(1);
	}

	memSelect = A >> 20;
	offset = A & 0xFFFFF;
	if (memSelect == 0x004) pM = progMEM;         // program memory
	else if (memSelect == 0x100) pM = dataMEM;  // data memory
	else if (memSelect == 0x7FF) pM = stakMEM;  // stack
	else {
		printf("Error: No memory with address: %08x\n", A); fflush(stdout);
		exit(1);
	}

	if (S == 0) {  // byte
		if (nRW == 0) {	// read
			return pM[offset];
		}
		else {	// write
			pM[offset] = (unsigned char)V;
			return 1;
		}
	}
	else if (S == 1) { // half word
		offset = offset & 0xfffffffe;	// for aligned access
		if (nRW == 0) {	// read
			return (pM[offset] << 8) + pM[offset + 1];
		}
		else {	// write
			pM[offset] = (unsigned char)((V >> 8) & 0xff);
			pM[offset + 1] = (unsigned char)(V & 0xff);
			return 1;
		}
	}
	else if (S == 2) { // word
		offset = offset & 0xfffffffc;	// for aligned access
		if (nRW == 0) {	// read
			return (pM[offset] << 24) + (pM[offset + 1] << 16) + (pM[offset + 2] << 8) + pM[offset + 3];
		}
		else {	// write
			pM[offset] = (unsigned char)((V >> 24) & 0xff);
			pM[offset + 1] = (unsigned char)((V >> 16) & 0xff);
			pM[offset + 2] = (unsigned char)((V >> 8) & 0xff);
			pM[offset + 3] = (unsigned char)(V & 0xff);
			return 1;
		}
	}
	return 0;
}

void resetMem(void)
{
	int i;
	for (i = 0; i < M_SIZE; i++) {
		progMEM[i] = 0;
		dataMEM[i] = 0;
		stakMEM[i] = 0;
	}
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
