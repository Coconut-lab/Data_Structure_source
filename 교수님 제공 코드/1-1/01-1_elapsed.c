#define _CRT_SECURE_NO_WARNINGS
// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch01/01_elapsed.c

//-------------------------------------------------------------
// 코드 1.2 1부터 1억까지의 합을 구하는 데 걸리는 시간 측정
#define MAX1 10
#define MAX2 100000000

int calc_sum(int n);    // 함수의 리스트

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE* fp1 = fopen("01_output.txt", "a+");
    clock_t start, finish;
    double  duration;

    fprintf(stdout ,"1부터 10까지의 합은 %d입니다.\n", calc_sum(MAX1));
    fprintf(fp1, "1부터 10까지의 합은 %d입니다.\n", calc_sum(MAX1));

    start = clock();			// 시작 시각
    calc_sum(MAX2);		// 실행시간을 측정하고자 하는 코드를 넣는 부분
    finish = clock();			// 종료 시각

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    fprintf(stdout, "1부터 1억까지의 합을 구하는데 걸리 시간: %lf 초\n", duration);
    fprintf(fp1, "1부터 1억까지의 합을 구하는데 걸리 시간: %lf 초\n", duration);

    fprintf(fp1, "-------------------------------------------------\n");

    fclose(fp1);
    system("open -a TextEdit 01_output.txt");

    return 0;
}

int calc_sum(int n)
{
    int i, sum = 0;
    for (i = 1; i <= n; i++)
        sum = sum + i;
    return sum;
}