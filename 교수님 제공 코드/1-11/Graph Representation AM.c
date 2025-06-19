// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch08/GraphRepAM.c


//--------------------------------------------------------------------
// �ڵ� 8.1 ���� ����� �̿��� �׷��� ǥ��


#include <stdio.h>
#include <stdlib.h>
#define MAX_VSIZE 100   // �ִ� ���� ��
typedef char VElement;  // VElement�� �ڷ��� ����

int vsize = 5; // �׷����� ���� ��
VElement vdata[MAX_VSIZE] = { 'U', 'V', 'W', 'X', 'Y' };
int adj[MAX_VSIZE][MAX_VSIZE] = {
    { 0, 1, 1, 0, 0 },
    { 1, 0, 1, 1, 0 },
    { 1, 1, 0, 0, 1 },
    { 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
};

int degree(int v)
{
    int count = 0;
    for (int i = 0; i < vsize; i++)
        if (adj[v][i] == 1) count++;
    return count;
}

void main()
{
    printf("�׷����� ������� ǥ��\n");
    for (int i = 0; i < vsize; i++) {
        printf("���� %c(����=%d): ", vdata[i], degree(i));
        for (int j = 0; j < vsize; j++)
            printf("%2d", adj[i][j]);
        printf("\n");
    }
}
