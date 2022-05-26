#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
// as_ex01_arith.bin
// as_ex02_logic.bin
// as_ex03_ifelse.bin
// as_ex04_fct.bin

// console i/o 만들기. 
int main(void) {
	char inputStr[100];
	char* token = NULL;
	char* context = NULL; // strtok_s 에서 사용
	char* ptr = NULL; // strtoul 에서 사용

	while (1) {
		
		printf("명령어를 입력하세요: ");
		gets(inputStr);
		
		token = strtok_s(inputStr, " ", &context);
		if (token == NULL) {
			printf("[ERROR] 잘못된 명령어 입력\n");
			continue;
		}
		// Load program
		if (strcmp(token, "l") == 0) {
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] 파일 이름을 같이 입력해주세요.\n");
				continue;
			}
			printf("[Load program] 파일 이름: %s\n", token);
			loading(token);
		}
		// Jump program
		else if (strcmp(token, "j") == 0) {
			int address;
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] PC 주소를 같이 입력해주세요.\n");
				continue;
			}
			address = strtoul(token, &ptr, 16); // 주소를 16진수로 입력받기
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
			int start, end;		// start, end 주소 역시 16진수로 입력
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] start 주소와 end 주소를 같이 입력해주세요.\n");
				continue;
			}
			start = strtoul(token, &ptr, 16);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] end 주소를 같이 입력해주세요.\n");
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
			int regnum, value; // 레지스터 번호는 10진수로, 설정할 값은 16진수로
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] 레지스터 번호와 설정할 값을 같이 입력해주세요.\n");
				continue;
			}
			regnum = strtoul(token, &ptr, 10);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] 설정할 값을 같이 입력해주세요.\n");
				continue;
			}
			value = strtoul(token, &ptr, 16);

			printf("[Set register] R[%d] 를 %d 로 설정\n", regnum, value);
			setRegister(regnum, value);
		}
		// Set memory
		else if (strcmp(token, "sm") == 0) {
			int location, value; // 메모리 주소와 설정할 값을 16진수로
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] 메모리 주소와 설정할 값을 같이 입력해주세요.\n");
				continue;
			}
			location = strtoul(token, &ptr, 16);
			token = strtok_s(NULL, " ", &context);
			if (token == NULL) {
				printf("[ERROR] 설정할 값을 같이 입력해주세요.\n");
				continue;
			}
			value = strtoul(token, &ptr, 16);
			printf("[Set memory] Memory 0x%X 번지를 %d 로 설정\n", location, value);
			setMemory(location, value);
		}
		else {
			printf("[ERROR] 잘못된 명령어 입력\n");
		}
	}
	return 0;
}