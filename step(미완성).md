## Step()
현재 op, fn에 따라 분기하는 부분만 구현됨
### 앞으로 구현해야  것
* unsigned int getOp(unsigned int IR);
* unsigned int getFn(unsigned int IR);
* unsigned int getRs(unsigned int IR);
* unsigned int getRt(unsigned int IR);
* unsigned int getRd(unsigned int IR);
* unsigned int getOffset(unsigned int IR);
* goto STOP; 부분이 우리가 원하는 동작을 하도록 만들기
* 각 명령어 실행

```python
#include "stdio.h"
#include <iostream>
using namespace std;

void step(void) {
	unsigned int op, fn, rs, rt, rd, offset;
	IR = MEM(PC, 0, 0, 2); PC += 4;
	// instruction decode
	op = getOp(IR);

	if (op == 0) {
		fn = getFn(IR); rs = getRs(IR);
		rt = getRt(IR); rd = getRd(IR);
		if (fn == 32) { // ADD
			R[rd] = ALU(ADD, R[rs], R[rt]);
		}
		else if (fn == 34) { // SUB

		}
		else if (fn == 36) { // AND

		}
		else if (fn == 37) { // OR

		}
		else if (fn == 38) { // XOR

		}
		else if (fn == 39) { // NOR

		}
		else if (fn == 42) { // SLT

		}
		else if (fn == 0) { // SLL

		}
		else if (fn == 2) { // SRL

		}
		else if (fn == 3) { // SRA

		}
		else if (fn == 24) { // MUL

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
			cout << "Undefined Inst...";
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
	cout << "Undefined Inst...";
	goto STOP; 
	}

}
```
