// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch09/sort_qsort.c


//--------------------------------------------------------------------
// �ڵ� 9.7 �� ���� ���̺귯�� �Լ� ��� ��


#include <stdio.h>
#include <stdlib.h>

int compare(const void *arg1, const void *arg2)
{
    if (*(double *)arg1 > *(double *)arg2) return 1; // arg1�� �� ũ�� 1
    else if (*(double *)arg1 < *(double *)arg2) return -1; // arg2�� �� ũ�� -1
    else return 0;  // ������ 0
}
void main()
{
    double list[9] = { 2.1, 0.9, 1.6, 3.8, 1.2, 4.4, 6.2, 9.1, 7.7 };

    printf("���� ��: ");
    for (int i=0; i < 9; i++)
        printf("%4.1f ", list[i]);

    // ù��° ���� => DB, �ι�° ���� => ����, ����° ���� => ũ�� �׹�° ���� => �Լ��� �ּ�
    qsort((void *)list, 9, sizeof(double), compare); // stdlib.h�� qsort() �Լ� ���, ���̺귯�� ���
    printf("\n���� ��: ");
    for (int i=0; i<9; i++)
        printf("%4.1f ", list[i]);
    printf("\n");
}
