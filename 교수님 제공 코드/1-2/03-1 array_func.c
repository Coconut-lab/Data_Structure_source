#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX1 3
#define MAX2 3
int main()
{
	int array[MAX1][MAX2];
	int i, j;
	int* p1 = array;        // 포인터
	int(*p2)[MAX2]=array;   // 배열포인터

	for(i=0; i<MAX1; i++)
	{
		for (j = 0; j < MAX2; j++)
		{
			array[i][j] = j;
		}		
	}

	for (i = 0; i < (MAX1*MAX2); i++)
	{
		printf("p1[%d]=%d\n",i, p1[i]);
	}
	printf("\n");
	
	for (i = 0; i < MAX1; i++)
	{
		for (j = 0; j < MAX2; j++)
		{
			printf("p2[%d][%d]=%d\n", i, j, p2[i][j]);
		}
		printf("\n");
	}

}