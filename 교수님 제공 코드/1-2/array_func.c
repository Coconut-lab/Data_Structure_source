// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/array_func.c

//-------------------------------------------------------------
// �ڵ� 2.3 �Լ��� �Ű������� �迭 ����

#include <stdio.h>
void reset_variable(int a) {
    a = 0;
}
void reset_array(int a[], int len) {
    for (int i = 0; i < len; i++) a[i] = 0;
}

void main()
{
	int A[3] = { 10, 20, 30 }, x = 2024;

    reset_variable(x);		// ���� x�� 0���� �ʱ�ȭ -> ����
    reset_array(A, 3);		// ���̰� 3�� �迭 A�� 0���� �ʱ�ȭ -> ����

	printf("���� �ʱ�ȭ: x=%d\n", x);
	printf("�迭 �ʱ�ȭ: ");
	for (int i=0; i < 3 ; i++)
		printf("A[%d]=%d ", i, A[i]);
    printf("\n");
}