#define _CRT_SECURE_NO_WARNINGS //scanf_s() �Ǵ� printf_s()�� ������� �ʾƼ� �߻��ϴ� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	FILE* p1; // �б�� ���� ������ ����
	FILE* p2; // ����� ���� ������ ����

	int hak;
	char adress[40];
	double score;
	
	int data_count = 0;

	p1 = fopen("01 input.txt", "r");   // 1. ���� ������ �����ϸ�,      read  ���� ���� �б�
	p2 = fopen("01 output.txt", "w"); //  2. write ���� ���� ����

	
	if (p1 == NULL)
		printf("���Ͽ��� ����\n");

	while (!feof(p1))
	{
		// ������ �о�鿩�� ����ü ��ҿ� ����
		fscanf(p1, "%d %s %lf", &hak, adress, &score);
		fprintf(stdout,"%d %s %lf\n", hak, adress, score);	
		fprintf(p2,    "%d %s %lf\n", hak, adress, score);
		data_count++;
	}

	fprintf(p2, "------------------------------\n");

	fclose(p1);  // read  ��� ������ ����
	fclose(p2);  // write ��� ������ ����

	system("notepad.exe 01 input.txt");
	system("notepad.exe 01 output.txt");

	return 0;	
}
