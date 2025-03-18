
#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000

typedef struct random_number
{
	int idx;
	int n;
} RN;

int main() 
{
	FILE* file;
	//srand(time(NULL));
	file = fopen("07 output.txt", "w");

	RN* p = (RN*)malloc(sizeof(RN)*MAX);

	for (int i = 1; i <= MAX; i++) 
	{
		(p+i)->idx = i;
		(p+i)->n = rand() % 100 + 1;
		
		printf("%8d %8d\n", (p+i)->idx,(p+i)->n);
		fprintf(file, "%8d %8d\n", (p + i)->idx, (p + i)->n);
	}
	fclose(file);
	system("notepad.exe 07 output.txt");


	return 0;
}