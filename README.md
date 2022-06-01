# 8teamTermProject
컴퓨터 구조 8팀

* master branch에 있던 코드들을 토대로 통합한 코드들이 있습니다.

## 파일 관계
### register.c
+  "register.h"를 include합니다.
+  레지스터와 관련된 변수, 함수 등이 있습니다. 
### register.h 
+ R_SIZE, accessTypeR, REGISTER_ENUM, R[32], REG(), resetRegister() 가 선언되어 있습니다.
### memory.c 
+ "memory.h"를 include합니다.
+  메모리와 관련된 변수, 함수 등이 있습니다.
### memory.h 
+ M_SIZE, accessTypeM, accessSize, progMEM[0x100000], dataMEM[0x100000], stackMEM[0x100000], MEM(), resetMem() 가 선언되어 있습니다.
### ALU.c 
+ "ALU.h" 를 include합니다.
+ ALU 연산을 하여 연산 결과를 리턴해주는 함수 ALU() 가 있습니다.
### ALU.h 
+ fctType, ALU() 가 선언되어 있습니다.
### instructions.c 
+ "instructions.h" 를 include합니다.
+  addi(), slti() 등 MIPS 명령어들을 실행시키는 함수들이 있습니다.
### instructions.h
+ "ALU.h", "memory.h", "register.h" 를 include합니다.
+ PC, SP, HI, LO를 extern으로 받고 addi(), slti() 등의 함수들을 선언합니다.
### commands.c 
+ "commands.h" 를 include합니다.
+  go(), step(), loading() 등 Simulator에서 사용하는 명령어들을 실행하는 함수들과 그러한 함수들이 사용하는 getOp(), invertEndian() 등의 함수들이 있습니다.
### commands.h
+ "instructions.h" 를 include합니다.
+  IR, PC, SP를 extern으로 받습니다. go(), step(), getOp() 등의 함수들이 선언되어 있습니다.
### main.c 
+ "commands.h" 를 include합니다.
+ 사용자로부터 시뮬레이터 명령어를 입력받아 오류 메시지를 출력하거나 commands.h에 선언된 함수들을 실행하는 main() 함수가 있습니다.


## 프로그램 사용 방법
프로그램을 실행시키면
```
명령어를 입력하세요: 
```
라는 문구가 나타납니다. 이때 사용할 수 있는 명령어들은 다음과 같습니다.
### l \<실행 파일이름\>
* 실행 파일이 시뮬레이터의 메모리에 올라가고 PC, SP가 초기화됩니다. 
* 실행 파일이 메모리에 올라간 후 PROG WORD 와 DATA WORD 를 읽어서 address와 값을 16진수로 나타내고 사용자 명령어를 받는 상태로 돌아갑니다.
* 실행 파일이름을 같이 입력하지 않았을 경우 파일 이름을 같이 입력해달라는 오류 메시지가 출력되고 다시 명령어를 입력하라는 문구가 나타납니다. 

### j \<프로그램 시작 위치\>
* PC를 입력한 16진수 주소 값으로 설정합니다. 
* `l` 명령어로 실행 파일을 loading한 다음 `j` 명령어를 사용하지 않을 경우 PC는 0x400000 입니다.
* 프로그램 시작 위치를 같이 입력하지 않았을 경우 PC 주소를 같이 입력해달라는 오류 메시지가 출력되고 사용자 명령어를 받는 상태로 돌아갑니다.

### g
* 현재 PC 위치에서 시뮬레이터가 명령어를 끝까지 처리하도록 합니다.
* 처리하는 명령어를 디코딩해서 보여주고 레지스터나 메모리 변화를 보여줍니다. syscall 10을 만나면 Exit program 이라는 문구를 출력하고 다시 사용자 명령어를 받는 상태로 돌아갑니다.

### s
* 명령어 하나를 처리하고 사용자 명령을 받는 상태로 중지합니다.
* 처리한 명령어를 디코딩해서 보여주고 레지스터나 메모리의 변화를 알려줍니다.

### m \<start\> \<end\>
* 16진수로 메모리의 주소를 start와 end로 각각 입력받아 start~end 범위의 메모리 내용을 출력합니다.
* `m` 만을 입력하면 start 와 end 주소를 같이 입력하라는 오류 메시지를, `m <start>` 만 입력하면 end 주소를 입력하라는 오류 메시지를 출력하고 사용자 명령어를 받는 상태로 돌아갑니다.

### r
* 현재 레지스터의 내용을 모두 출력합니다.
* PC, HI, LO, R[0] ~ R[31] 의 값을 모두 출력합니다.
  
### x
* 시뮬레이터 프로그램을 종료합니다.
  
### sr \<register number\> \<value\>
*  register number를 10진수로, value를 16진수로 받아 특정 레지스터의 값을 설정합니다.
* `sr` 만 입력한 경우 레지스터 번호와 설정할 값을 같이 입력해달라는 오류 메시지를, `sr <register number>` 만 입력한 경우에는 설정할 값을 입력헤달라는 오류 메시지를 출력하고 사용자 명령어를 받는 상태로 돌아갑니다.

### sm \<location\> \<value\>
* memory location과 value를 16진수로 받아 메모리 특정 주소의 값을 설정합니다.
* `sm` 만 입력한 경우 메모리 주소와 설정할 값을 같이 입력해달라는 오류 메시지를, `sm <location>` 만 입력한 경우에는 설정할 값을 입력헤달라는 오류 메시지를 출력하고 사용자 명령어를 받는 상태로 돌아갑니다.
  
