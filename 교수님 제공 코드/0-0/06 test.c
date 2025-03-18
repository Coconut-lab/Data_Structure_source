
#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int Factorial(int n);
int i=0;             // 전역변수 i가 무엇을 의미할까? 생각해보기... 

int main(void)
{
	clock_t start, finish;
	double duration;
	int num, result;

	FILE* fp; 

	while (1)
	{
		start = clock(); // 시간측정 시작
		i++;
		fprintf(stdout, "팩토리얼 입력(양수): ");
		fscanf(stdin, "%d", &num);

		if (num < 0)
		{
			printf("양수를 입력하세요.\n");
			continue;
		}
				
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		fp = fopen("06 output.txt", "a+");  // 파일을 만들어 오픈, 현재 프로젝트 폴더에 생성...기존 내용을 누적(a), 텍스트(t)
		result = Factorial(num);          // 팩토리얼 수행시간
		finish = clock();                 // 시간측정 완료
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		fprintf(fp, "%03d--%d!=%d --> 수행시간 %lf초 \n", i, num, result, duration);     // 파일(fp)에 데이터를 출력
		fprintf(stdout, "%03d--%d!=%d --> 수행시간 %lf초 \n", i, num, result, duration);  // 모니터(stdout)에 데이터를 출력
		fprintf(fp, "-----------------------------------------------\n");                // 파일(fp)에 데이터를 출력

		fclose(fp);
		system("notepad.exe 06 output.txt");  // 자동으로 메모장을 오픈
		//system("cmd");					                     		
	}
	
	return 0;
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 팩토리얼 함수
  1. 입          력: int n 
  2. 처리(알고리즘): 입력이 0이면 1을, 입력이 0이 아니면 재귀함수 호출
  3. 출          력: int 값 반환
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Factorial(int n)  
{
	if (n == 0)
		return 1;
	else
		return n * Factorial(n - 1);
}