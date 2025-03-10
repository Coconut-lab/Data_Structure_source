#include "ych.h"
#define TEST_SIZE 10000
#define GOAL_DATA 10485760		//������� �ϴ� ���� ������ �뷮

long long Mega = 1048576;
long long Giga = 1073741824;	//1024 * Mega

int main() {
	int* arr = (int*)malloc(sizeof(int) * TEST_SIZE);
	int rand1,k = 0;
	FILE* p1, *p2;
	//TEST_SIZE��ŭ ���� ���� �� 01.txt�� write
	p1 = fopen("01.txt", "w");
	srand(time(NULL));
	for (long i = 0; i < TEST_SIZE;i++) {
		rand1 = rand();
		fprintf(p1,"\n%d", rand1);
	}

	fprintf(stdout, "%d���� ���� ���� �Ϸ�\n", TEST_SIZE);
	fclose(p1);
	system("notepad.exe 01.txt");
	//---------------------------------
	//01.txt read �� �� arr�� ����
	p1 = fopen("01.txt", "r");

	if (p1 == NULL)
		exit(1);

	while(!feof(p1)) {
		fscanf(p1, "\n%d", &arr[k]);
		k++;
	}
	fprintf(stdout, "01.txt read �Ϸ�\n");
	fclose(p1);
	//----------------------------------
	//������ �� �����Ͽ� 02.txt�� write
	p2 = fopen("02.txt", "w");

	qsort(arr, TEST_SIZE, sizeof(int), compare);

	for (k = 0; k < TEST_SIZE; k++) {
		fprintf(p2, "\n%d", arr[k]);
	}
	fprintf(stdout, "�о���� ���� ���� �� 02.txt�� write �Ϸ�\n");
	fclose(p2);
	system("notepad.exe 02.txt");
	//----------------------------------
	//02.txt���� ���� ���θ� �ϳ��� ���ڿ��� ���� �� GOAL_DATA ũ���� �ؽ�Ʈ���� �����
	int data_size = TEST_SIZE * 5, n = TEST_SIZE/10;		//���� �ϳ��� 5����Ʈ
	char tmp[7];
	char* combined_str = (char*)malloc(sizeof(char) * (TEST_SIZE * 6) + 1);		//���� ���� ���ڿ�

	p2 = fopen("03.txt", "w");

	combined_str[0] = '\0';			//���ڿ� �ʱ�ȭ

	for (int l = 0; l < TEST_SIZE; l++) {
		sprintf(tmp, "%05d", arr[l]); // �� ���ڸ� 5�ڸ� ���ڿ��� ��ȯ
		strcat(combined_str, tmp); // ���ڿ� �߰�
	}

	printf("�迭�� �������� ���ڿ��� ��ģ ���: %s\n", combined_str);

	for (int l = 0; l < GOAL_DATA / data_size; l++) {
		fprintf(p2, "%s", combined_str);
	}
	fprintf(stdout, "%d ũ���� ���ڿ� %d �� print\n", data_size, GOAL_DATA / data_size);
	
	for (int l = 0; l < GOAL_DATA % data_size; l++) {
		fprintf(p2, "%c", combined_str[l]);
	}

	fprintf(stdout, "���ĵ� �����ͷ� %dMB ũ���� �ؽ�Ʈ ���� ����", GOAL_DATA / Mega);
	free(combined_str);
	free(arr);
	fclose(p2);
	system("notepad.exe 03.txt");

	return 0;
}