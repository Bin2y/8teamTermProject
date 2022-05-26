#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
// as_ex01_arith.bin
// as_ex02_logic.bin
// as_ex03_ifelse.bin
// as_ex04_fct.bin

// console i/o �����. 
int main(void) {
	char inputStr[100];
	char* token = NULL;
	char* context = NULL; // strtok_s ���� ���
	char* ptr = NULL; // strtoul ���� ���

	while (1) {
		
		printf("��ɾ �Է��ϼ���: ");
		gets(inputStr);
		
		token = strtok_s(inputStr, " ", &context);
		if (token == NULL) {
			printf("[ERROR] �߸��� ��ɾ� �Է�\n");
			continue;
		}
		// Load program
		if (strcmp(token, "l") == 0) {
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] ���� �̸��� ���� �Է����ּ���.\n");
				continue;
			}
			printf("[Load program] ���� �̸�: %s\n", token);
			loading(token);
		}
		// Jump program
		else if (strcmp(token, "j") == 0) {
			int address;
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] PC �ּҸ� ���� �Է����ּ���.\n");
				continue;
			}
			address = strtoul(token, &ptr, 16); // �ּҸ� 16������ �Է¹ޱ�
			printf("[Jump program] PC: 0x%X\n", address);
			jump(address);
		}
		// Go program
		else if (strcmp(token, "g") == 0) {
			printf("[Go program]\n");
			go();
		}
		// Step
		else if (strcmp(token, "s") == 0) {
			printf("[Step]\n");
			step();
		}
		// View memory
		else if (strcmp(token, "m") == 0) {
			int start, end;		// start, end �ּ� ���� 16������ �Է�
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] start �ּҿ� end �ּҸ� ���� �Է����ּ���.\n");
				continue;
			}
			start = strtoul(token, &ptr, 16);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] end �ּҸ� ���� �Է����ּ���.\n");
				continue;
			}
			end = strtoul(token, &ptr, 16);
			printf("[View memory] start: 0x%X, end: 0x%X\n", start, end);
			viewMemory(start, end);
		}
		// View register
		else if (strcmp(token, "r") == 0) {
			printf("[View register]\n");
			viewRegister();
		}
		// Program exit
		else if (strcmp(token, "x") == 0) {
			printf("[Program exit]\n");
			break;
		}
		// Set register
		else if (strcmp(token, "sr") == 0) {
			int regnum, value; // �������� ��ȣ�� 10������, ������ ���� 16������
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] �������� ��ȣ�� ������ ���� ���� �Է����ּ���.\n");
				continue;
			}
			regnum = strtoul(token, &ptr, 10);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] ������ ���� ���� �Է����ּ���.\n");
				continue;
			}
			value = strtoul(token, &ptr, 16);

			printf("[Set register] R[%d] �� %d �� ����\n", regnum, value);
			setRegister(regnum, value);
		}
		// Set memory
		else if (strcmp(token, "sm") == 0) {
			int location, value; // �޸� �ּҿ� ������ ���� 16������
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] �޸� �ּҿ� ������ ���� ���� �Է����ּ���.\n");
				continue;
			}
			location = strtoul(token, &ptr, 16);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] ������ ���� ���� �Է����ּ���.\n");
				continue;
			}
			value = strtoul(token, &ptr, 16);
			printf("[Set memory] Memory 0x%X ������ %d �� ����\n", location, value);
			setMemory(location, value);
		}
		else {
			printf("[ERROR] �߸��� ��ɾ� �Է�\n");
		}
	}
	return 0;
}