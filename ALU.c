#include "ALU.h"

// shift ���� v2�� shift�� ���̴�. (ex. v2 << v1)
// SLT�� ��� v1 < v2 �̸� 1, �ƴϸ� 0�� return
int ALU(int fct, int v1, int v2) {
	if (fct == ADD) {
		return v1 + v2;
	}
	else if (fct == SUB) {
		return v1 - v2;
	}
	else if (fct == MUL) { // ���� ����� �����ִ� �͹ۿ� �� �� �����Ƿ� hi, lo �� ���� ���� �ִ� ���� ��ȯ ���� �޴� �ʿ��� �ؾ��Ѵ�.
		return v1 * v2;
	}
	else if (fct == AND) {
		return v1 & v2;
	}
	else if (fct == OR) {
		return v1 | v2;
	}
	else if (fct == XOR) {
		return v1 ^ v2;
	}
	else if (fct == NOR) {
		return ~(v1 | v2);
	}
	else if (fct == SLL) {
		return v2 << v1;
	}
	else if (fct == SRL) {
		return (unsigned int)v2 >> v1;
	}
	else if (fct == SRA) {
		return v2 >> v1;
	}
	else if (fct == SLT) {
		if (v1 < v2) return 1;
		else return 0;
	}
	else {
		return -1;
	}
}