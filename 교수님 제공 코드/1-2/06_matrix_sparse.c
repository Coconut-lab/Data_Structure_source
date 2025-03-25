// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/06_matrix_sparse.c

//-------------------------------------------------------------
// �ڵ� 2.6 ��� ����� ǥ��
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
    int		row;		// �� ��ȣ
    int	    col;		// �� ��ȣ
    int	    value;		// ��� ����� ��
} Elem;         		// �ϳ��� ��� ���

void print_mat2(Elem m[], int len, char* str)
{
    printf("%s: ", str);
    for (int i = 0; i < len; i++)
        printf(" (%d,%d,%d)", m[i].row, m[i].col, m[i].value);
    printf("\n");
}
void transpose_mat2(Elem m[], int len)
{
    for (int i = 0; i < len; i++) {
        int tmp = m[i].row;        // ����ü ����(���ڵ� ����)�� ���� �ʵ尪 ����
        m[i].row = m[i].col;       // ����ü ����(���ڵ� ����)�� ���� �ʵ尪 ����
        m[i].col = tmp;            // ����ü ����(���ڵ� ����)�� ���� �ʵ尪 ����
    }
}

void main()
{
    Elem mat[5] = { {0, 3, 11}, {2, 5, 42}, {3, 1, 33}, {4, 4, 87}, {5, 4, 55} };
    print_mat2(mat, 5, "��� ���");
    transpose_mat2(mat, 5);
    print_mat2(mat, 5, "��ġ ���");
}

