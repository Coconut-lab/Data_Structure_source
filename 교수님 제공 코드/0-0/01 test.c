#define _CRT_SECURE_NO_WARNINGS //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	FILE* p1; // 읽기용 파일 포인터 생성
	FILE* p2; // 쓰기용 파일 포인터 생성

	int hak;
	char adress[40];
	double score;
	
	int data_count = 0;

	p1 = fopen("01 input.txt", "r");   // 1. 기존 파일이 존재하면,      read  모드로 파일 읽기
	p2 = fopen("01 output.txt", "w"); //  2. write 모드로 파일 쓰기

	
	if (p1 == NULL)
		printf("파일오픈 에러\n");

	while (!feof(p1))
	{
		// 내용을 읽어들여서 구조체 요소에 저장
		fscanf(p1, "%d %s %lf", &hak, adress, &score);
		fprintf(stdout,"%d %s %lf\n", hak, adress, score);	
		fprintf(p2,    "%d %s %lf\n", hak, adress, score);
		data_count++;
	}

	fprintf(p2, "------------------------------\n");

	fclose(p1);  // read  모드 포인터 해제
	fclose(p2);  // write 모드 포인터 해제

	system("notepad.exe 01 input.txt");
	system("notepad.exe 01 output.txt");

	return 0;	
}
