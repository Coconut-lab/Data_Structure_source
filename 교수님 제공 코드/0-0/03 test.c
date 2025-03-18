#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 3

struct SaleData
{
	int  no; // 순번
	char address[100]; // 주소
	double  total; // 판매량
};

void main()
{
	int i = 0; // 레코드 변수 카운트
	struct SaleData sale[MAX]; // 구조체 배열, 레코드 수

	FILE* p1; // 읽기용
	FILE* p2; // 쓰기용

	p1 = fopen("03 input.txt", "r");   //  read 모드로 03 input.txt 파일에 읽기
	p2 = fopen("03 output.txt", "a+");  //   누적모드로 03 output.txt 파일에 누적


	// 파일 내용의 끝에 도달할 때까지 반복문 수행
	while (!feof(p1))
	{
		// 파일의 내용을 읽어들여서, 구조체 메모리에 저장
		fscanf(p1, "%d %s %lf", &sale[i].no, sale[i].address, &sale[i].total);
		fprintf(stdout, "%d %s %lf\n", sale[i].no, sale[i].address, sale[i].total);
		fprintf(p2, "%d %s %lf\n", sale[i].no, sale[i].address, sale[i].total);    // 쓰기용
		i++;
	}
	fprintf(p2, "--------------------------------------\n");
	fclose(p1); // 03 input.txt  파일 닫기, read 모드 해제
	fclose(p2); // 03 output.txt 파일 닫기, write모드 해제
	
	system("notepad.exe 03 input.txt");
	system("notepad.exe 03 output.txt");

}