// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch10/bin_search.c

#include <stdio.h>


//--------------------------------------------------------------------
// �ڵ� 10.3 ���� Ž��(��ȯ ����)


int binary_search(int A[], int key, int low, int high)
{
    if (low <= high) {              // Ž���� ���ڵ尡 ������
        int mid = (low + high) / 2; // �߾� �ε��� ���
        printf("->%d", A[mid]);
        if (key == A[mid])          // Ž�� ����
            return mid;
        else if (key < A[mid])      // ����(left~middle-1)�� �ٽ� Ž��
            return binary_search(A, key, low, mid - 1);
        else                        // ������(middle+1~right)�� �ٽ� Ž��
            return binary_search(A, key, mid + 1, high);
    }
    return -1;                      // Ž�� ����
}


//--------------------------------------------------------------------
// �ڵ� 10.4 ���� Ž��(�ݺ� ����)


int binary_search_iter(int A[], int key, int low, int high)
{
    while (low <= high) {           // Ž���� ���ڵ尡 ������
        printf(".");
        int mid = (low + high) / 2; // �߾� �ε��� ���
        if (key == A[mid])          // Ž�� ����
            return mid;
        else if (key < A[mid])      // ����(left~middle-1)�� �ٽ� Ž��
            high = mid - 1;
        else                        // ������(middle+1~right)�� �ٽ� Ž��
            low = mid + 1;          // mid+1 ~ high ���� �˻�
    }
    return -1;                      // Ž�� ����
}


//--------------------------------------------------------------------
// ���� Ž��


int binary_search_interpolation(int A[], int key, int low, int high)
{
    if (low <= high) {				// �ϳ� �̻��� �׸��� �־�� Ž��
	int mid = (int)((float)(key - A[low]) /
		(A[high] - A[low]) * (high - low)) + low;
        printf("->%d", A[mid]);

	if (key == A[mid])			// Ž�� ����
	    return mid;
	else if (key < A[mid])		// ���� �κи���Ʈ Ž�� 
	    return binary_search_interpolation(A, key, low, mid - 1);
	else						// ������ �κи���Ʈ Ž�� 
	    return binary_search_interpolation(A, key, mid + 1, high);
    }
    return -1;        				// Ž�� ����
}

void main()
{
    int	list[16] = { 8, 11, 12, 15, 16, 19, 20, 23, 25, 28, 29, 31, 33, 35, 38, 40 };
    int key = 28;
    printf("  %d ����Ž��(��ȯ): %d\n", key, binary_search(list, key, 0, 15));
    printf("  %d ����Ž��(����): %d\n", key, binary_search_interpolation(list, key, 0, 15));
    printf("\n");
}


