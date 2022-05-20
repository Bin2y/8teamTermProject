## Step()
현재 op, fn에 따라 분기하는 부분만 구현됨
### 앞으로 구현해야  것
* goto STOP; 부분이 우리가 원하는 동작을 하도록 만들기
* 각 명령어 실행

```cpp
#include "stdio.h"

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


void step(void) {
	unsigned int op, fn, rs, rt, rd, offset;
	IR = MEM(PC, 0, 0, 2); PC += 4;
	// instruction decode
	op = getOp(IR);

	if (op == 0) {
		fn = getFn(IR); rs = getRs(IR);
		rt = getRt(IR); rd = getRd(IR);
		if (fn == 32) { // ADD
			Add(rd, rs, rt);
		}
		else if (fn == 34) { // SUB
			Sub(rd, rs, rt);
		}
		else if (fn == 36) { // AND
			And(rd, rs, rt);
		}
		else if (fn == 37) { // OR
			Or(rd, rs, rt);
		}
		else if (fn == 38) { // XOR
			Xor(rd, rs, rt);
		}
		else if (fn == 39) { // NOR
			Nor(rd, rs, rt);
		}
		else if (fn == 42) { // SLT
			Slt(rd, rs, rt);
		}
		else if (fn == 0) { // SLL
			sh = getSh(IR);
			Sll(rd, sh, rt);
		}
		else if (fn == 2) { // SRL
			sh = getSh(IR);
			Srl(rd, sh, rt);
		}
		else if (fn == 3) { // SRA
			sh = getSh(IR);
			Sra(rd, sh, rt);
		}
		else if (fn == 24) { // MUL
			Mult(rs, rt);
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

}
```
