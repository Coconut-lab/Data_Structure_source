#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	char  filename[512] = "notepad.exe 04 output.txt";
	char* command;

	//gets(filename);   
	command = filename;
	system(command);   // 	system("notepad.exe 04 output.txt");  system("notepad.exe D:\\04 output.txt");
	
	return 0;
}