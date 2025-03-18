
#define _CRT_SECURE_NO_WARNINGS  //scanf_s() �Ǵ� printf_s()�� ������� �ʾƼ� �߻��ϴ� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int Factorial(int n);
int i=0;             // �������� i�� ������ �ǹ��ұ�? �����غ���... 

int main(void)
{
	clock_t start, finish;
	double duration;
	int num, result;

	FILE* fp; 

	while (1)
	{
		start = clock(); // �ð����� ����
		i++;
		fprintf(stdout, "���丮�� �Է�(���): ");
		fscanf(stdin, "%d", &num);

		if (num < 0)
		{
			printf("����� �Է��ϼ���.\n");
			continue;
		}
				
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		fp = fopen("06 output.txt", "a+");  // ������ ����� ����, ���� ������Ʈ ������ ����...���� ������ ����(a), �ؽ�Ʈ(t)
		result = Factorial(num);          // ���丮�� ����ð�
		finish = clock();                 // �ð����� �Ϸ�
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		fprintf(fp, "%03d--%d!=%d --> ����ð� %lf�� \n", i, num, result, duration);     // ����(fp)�� �����͸� ���
		fprintf(stdout, "%03d--%d!=%d --> ����ð� %lf�� \n", i, num, result, duration);  // �����(stdout)�� �����͸� ���
		fprintf(fp, "-----------------------------------------------\n");                // ����(fp)�� �����͸� ���

		fclose(fp);
		system("notepad.exe 06 output.txt");  // �ڵ����� �޸����� ����
		//system("cmd");					                     		
	}
	
	return 0;
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ���丮�� �Լ�
  1. ��          ��: int n 
  2. ó��(�˰���): �Է��� 0�̸� 1��, �Է��� 0�� �ƴϸ� ����Լ� ȣ��
  3. ��          ��: int �� ��ȯ
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Factorial(int n)  
{
	if (n == 0)
		return 1;
	else
		return n * Factorial(n - 1);
}