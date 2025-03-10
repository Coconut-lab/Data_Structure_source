#include "ych.h"
#define TEST_SIZE 10000
#define GOAL_DATA 10485760		//만들고자 하는 더미 파일의 용량

long long Mega = 1048576;
long long Giga = 1073741824;	//1024 * Mega

int main() {
	int* arr = (int*)malloc(sizeof(int) * TEST_SIZE);
	int rand1,k = 0;
	FILE* p1, *p2;
	//TEST_SIZE만큼 난수 생성 후 01.txt에 write
	p1 = fopen("01.txt", "w");
	srand(time(NULL));
	for (long i = 0; i < TEST_SIZE;i++) {
		rand1 = rand();
		fprintf(p1,"\n%d", rand1);
	}

	fprintf(stdout, "%d개의 난수 생성 완료\n", TEST_SIZE);
	fclose(p1);
	system("notepad.exe 01.txt");
	//---------------------------------
	//01.txt read 한 값 arr에 저장
	p1 = fopen("01.txt", "r");

	if (p1 == NULL)
		exit(1);

	while(!feof(p1)) {
		fscanf(p1, "\n%d", &arr[k]);
		k++;
	}
	fprintf(stdout, "01.txt read 완료\n");
	fclose(p1);
	//----------------------------------
	//저장한 값 정렬하여 02.txt에 write
	p2 = fopen("02.txt", "w");

	qsort(arr, TEST_SIZE, sizeof(int), compare);

	for (k = 0; k < TEST_SIZE; k++) {
		fprintf(p2, "\n%d", arr[k]);
	}
	fprintf(stdout, "읽어들인 파일 정렬 후 02.txt에 write 완료\n");
	fclose(p2);
	system("notepad.exe 02.txt");
	//----------------------------------
	//02.txt에서 난수 전부를 하나의 문자열로 저장 후 GOAL_DATA 크기의 텍스트파일 만들기
	int data_size = TEST_SIZE * 5, n = TEST_SIZE/10;		//난수 하나당 5바이트
	char tmp[7];
	char* combined_str = (char*)malloc(sizeof(char) * (TEST_SIZE * 6) + 1);		//난수 통합 문자열

	p2 = fopen("03.txt", "w");

	combined_str[0] = '\0';			//문자열 초기화

	for (int l = 0; l < TEST_SIZE; l++) {
		sprintf(tmp, "%05d", arr[l]); // 각 숫자를 5자리 문자열로 변환
		strcat(combined_str, tmp); // 문자열 추가
	}

	printf("배열의 난수들을 문자열로 합친 결과: %s\n", combined_str);

	for (int l = 0; l < GOAL_DATA / data_size; l++) {
		fprintf(p2, "%s", combined_str);
	}
	fprintf(stdout, "%d 크기의 문자열 %d 번 print\n", data_size, GOAL_DATA / data_size);
	
	for (int l = 0; l < GOAL_DATA % data_size; l++) {
		fprintf(p2, "%c", combined_str[l]);
	}

	fprintf(stdout, "정렬된 데이터로 %dMB 크기의 텍스트 파일 생성", GOAL_DATA / Mega);
	free(combined_str);
	free(arr);
	fclose(p2);
	system("notepad.exe 03.txt");

	return 0;
}