const enum accessTypeM { READ, WRITE };
enum accessSize { BYTE, HALF_WORD, WORD };

static const int M_SIZE = 0x100000;
unsigned char progMEM[0x100000], dataMEM[0x100000], stackMEM[0x100000];

int MEM(unsigned int A, int V, int nRW, int S);
void resetMem(void);