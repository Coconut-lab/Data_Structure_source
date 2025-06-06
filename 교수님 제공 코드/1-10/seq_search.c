// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch10/seq_search.c


//--------------------------------------------------------------------
// �ڵ� 10.1 ���� Ž��


#include <stdio.h>
int sequential_search(int A[], int key, int left, int right)
{
    for (int i = left; i <= right; i++)
        if (A[i] == key)    // Ž���� �����ϸ�
            return i;       // �ε��� ��ȯ
    return -1;              // Ž���� �����ϸ� -1 ��ȯ
}


//--------------------------------------------------------------------
// �ڵ� 10.2 ��ȯ�ϱ� ������ �߰��� ���� Ž��

#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))

int sequential_search_transpose(int A[], int key, int left, int right)
{
    for (int i = left; i <= right; i++)
        if (A[i] == key) {          // Ž���� �����ϸ�
            if (i != left) {        // �� �տ� �ִ� ��Ұ� �ƴϸ�
                i -= 1;
                int tmp;
                SWAP(A[i], A[i + 1], tmp);
            }
            return i;
        }
    return -1;
}

void main()
{
    int	table[5] = { 35, 97, 41, 56, 28 };

    printf("���� Ž�� %d --> %d\n", 56, sequential_search(table, 56, 0, 4));
    printf("���� Ž�� %d --> %d\n", 62, sequential_search(table, 62, 0, 4));
    printf("����Ž��(��ȯ) %d --> %d\n", 56, sequential_search_transpose(table, 56, 0, 4));
    printf("����Ž��(��ȯ) %d --> %d\n", 56, sequential_search_transpose(table, 56, 0, 4));
}
