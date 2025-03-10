// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch01/sequential_search.c

#include <stdio.h>


//-------------------------------------------------------------
// �ڵ� 1.3 ���� Ž��

int sequential_search(int A[], int n, int key)
{
    for (int i = 0; i<n; i++)
	if (A[i] == key)
	    return i;		// Ž���� �����ϸ� �ε��� ��ȯ 
    return -1;			// Ž���� �����ϸ� -1 ��ȯ
}

//-------------------------------------------------------------
// �׽�Ʈ ���α׷�
void main()
{
	int arr[10] = { 5, 9, 10, 17, 21, 29, 33, 37, 38, 43 };
	int index;

	index = sequential_search(arr, 10, 5);
	printf(" 5�� ��ġ = %d\n", index);
	index = sequential_search(arr, 10, 43);
	printf("43�� ��ġ = %d\n", index);
	index = sequential_search(arr, 10, 42);
	printf("42�� ��ġ = %d\n", index);

}