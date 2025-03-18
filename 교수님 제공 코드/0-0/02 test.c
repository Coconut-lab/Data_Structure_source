#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	char filename[512] = {0};
	
	printf("Input_command: ");  
	gets(filename);     // notepad.exe 02 output.txt 문자열 입력, 파일이 존재 하지 않으면 새로 만듬.
	system(filename);   // 같은 코드 -> system("notepad.exe 02 output.txt");

	return 0;
}