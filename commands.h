#include "instructions.h"
extern unsigned int IR;
extern unsigned int PC;
extern unsigned int SP;

unsigned int getOp(unsigned int IR);
unsigned int getFn(unsigned int IR);
unsigned int getRs(unsigned int IR);
unsigned int getRt(unsigned int IR);
unsigned int getRd(unsigned int IR);
unsigned int getSh(unsigned int IR);
unsigned int getOffset(unsigned int IR);
unsigned int getJOffset(unsigned int IR);
void go(void);
int step(void);
unsigned int invertEndian(unsigned int data);
void loading(char* bFileName);
void setPC(unsigned int val);
void jump(int address);
void viewRegister();
void setRegister(unsigned int num, int val);
void viewMemory(unsigned int start, unsigned int end);
void setMemory(unsigned int address, int value);
