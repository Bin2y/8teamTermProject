
enum fctType { ADD, SUB, MUL, AND, OR, XOR, NOR, SLL, SRL, SRA, SLT };

// shift 에서 v2가 shift될 값이다. (ex. v2 << v1)
// SLT의 경우 v1 < v2 이면 1, 아니면 0을 return
int ALU(int fct, int v1, int v2) {
	if (fct == ADD) { 
		return v1 + v2;
	}
	else if (fct == SUB) {
		return v1 - v2;
	}
	else if (fct == MUL) { // 연산 결과를 돌려주는 것밖에 할 수 없으므로 hi, lo 에 각각 값을 넣는 일은 반환 값을 받는 쪽에서 해야한다.
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
