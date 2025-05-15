// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch09/sort_all.c


//--------------------------------------------------------------------
// �ڵ� 9.1 ���� ����(���ڸ� ���� ���)


#include <stdio.h>
#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%3d", arr[i]);
    printf("\n");
}
void print_step(int arr[], int n, int val)
{
    printf("   Step%2d :", val);
    print_array(arr, n);
}

void selection_sort(int* A, int n)
{
	int tmp;							// SWAP()�� ���� �ӽú���
	for (int i = 0; i<n - 1; i++) {
		int least = i;					// �ּ� ����� �ε���
		for (int j = i + 1; j<n; j++)	// A[i+1~n-1]�� �˻��� 
			if (A[j]<A[least])			// �ּ� ��Һ��� ������
                least = j;				// �ּ� ��� ����
		SWAP(A[i], A[least], tmp);		// A[i]�� A[min] ��ȯ 

        print_step(A, n, i+1);			// ����� ���� ��¿� ����
	}
}


//--------------------------------------------------------------------
// �ڵ� 9.2 ���� ����

void insertion_sort(int A[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = A[i];                 // �̸� A[i]�� ������ ��
        int j;
        for (j = i - 1; j >= 0; j--) {  // i-1���� 0���� �ϳ��� ���̸鼭
            if (A[j] > key)             // A[j]�� �� ũ��
                A[j + 1] = A[j];        // A[j]�� �ڷ� �� ĭ �̵�
            else break;                 // �� ��ġ�� ã��. A[j]�� ���� ��ġ
        }
        A[j + 1] = key;
        print_step(A, n, i);
    }
}


//--------------------------------------------------------------------
// �ڵ� 9.3 ���� ����

void bubble_sort(int A[], int n)
{
    int tmp;
    for (int end = n - 1; end > 0; end--) { // ���ĵ��� ���� �κ��� ������ ��ġ
        int bChanged = 0;
        for (int j = 0; j < end; j++)       // �� ���� ��ĵ: 0���� end-1���� ����
            if (A[j] > A[j + 1]) {          // ������ ��Ұ� �����Ǿ� ������
                SWAP(A[j], A[j + 1], tmp);  // ��ȯ
                bChanged = 1;               // ��ȯ�� �߻���
            }
        if (!bChanged) break;               // ��ȯ�� �� ���� �������� ����
        print_step(A, n, n - end);
    }
}


//--------------------------------------------------------------------
// �ڵ� 9.4 �Լ� �����͸� �̿��� ���� ����

int ascend(int x, int y) { return y - x; }	// �������� ���Լ�
int descend(int x, int y) { return x - y; }	// �������� ���Լ�
void insertion_sort_fn(int A[], int n, int(*f)(int, int))
{
    for (int i = 1; i < n; i++) {
        int key = A[i];					// �̸� A[i]�� ������ ��
        int j;
        for (j = i - 1; j >= 0; j--) {	// i-1���� 0���� �ϳ��� ���̸鼭
            if (f(A[j], key) < 0) 		// A[j]�� �� ũ��
                A[j + 1] = A[j];		// A[j]�� �ڷ� �� ĭ �̵�
            else break;		            // ���ڸ��� ã��. A[j] ���� ��ġ.
        }
        A[j + 1] = key;					// A[i]�� j+1�� �־�� ��. �� ��ġ�� ����
        print_step(A, n, i);			// ����� ���� ���
    }
}


//--------------------------------------------------------------------
// �ڵ� 9.6 ���� ����

#define MAX_SIZE	1024
static void merge(int A[], int left, int mid, int right)
{
    static int sorted[MAX_SIZE];		// ���յ� ����Ʈ ������ ���� �ӽù迭
							    // ���� ���ĵ� list�� ����
    int i = left;       // ���� �κ� �迭 A[left~mid]�� ���� ��ġ
    int j = mid+1;      // ������ �κ� �迭 A[mid+1~right]�� ���� ��ġ
    int k = left;       // �ӽ� �迭 B[left~right]�� ���� ��ġ

    while (i <= mid && j <= right) {
        if (A[i] <= A[j])
            sorted[k++] = A[i++];
        else
            sorted[k++] = A[j++];
    }

    while (i <= mid  ) sorted[k++] = A[i++];	// ���ʿ� ���� ���ڵ� ��� ����
    while (j <= right) sorted[k++] = A[j++];	// �����ʿ� ���� ���ڵ� ��� ����

    for (i = left; i <= right; i++)		// �ӽù迭 B�� �Է¹迭 A�� ��� ����
	    A[i] = sorted[i];
}

// ���� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ�
void merge_sort(int A[], int left, int right) {
    if (left<right) {
        int mid = (left + right) / 2;	// ����Ʈ�� �յ� ����
        merge_sort(A, left, mid);		// �κ� ����Ʈ ����
        merge_sort(A, mid + 1, right);	// �κ� ����Ʈ ����
        merge(A, left, mid, right);		// ����
    }
}

//--------------------------------------------------------------------
// �ڵ� 9.7 �� ����

int partition(int A[], int left, int right)
{
    int pivot = A[left];                // �ǹ�
    int low = left + 1;                 // ���� �迭�� ���� �ε���
    int high = right;                   // ������ �迭�� ���� �ε���
    int tmp;
    while (low <= high) {
        while (low <= high && A[low] <= pivot) low++;
        while (low <= high && A[high] > pivot) high--;
        if (low < high)                 // �ε����� �������� �ʾ�����
            SWAP(A[low], A[high], tmp); // ���ǿ� ���� �ʴ� �� ��� ��ȯ
    }
    SWAP(A[left], A[high], tmp);        // high�� �ǹ� ��ȯ
    return high;                        // �ǹ��� �ε��� ��ȯ
}
void quick_sort(int A[], int left, int right)
{
    if (left < right) {                     // ��Ұ� 2�� �̻��� ���
        int q = partition(A, left, right);  // �ǹ��� �߽����� �¿�� ����
        quick_sort(A, left, q - 1);         // ���� �κ� ����
        quick_sort(A, q + 1, right);        // ������ �κ� ����
    }
}

void printArray(int arr[], int n, char* str)
{
    printf("%s =", str);
    print_array(arr, n);
}


void main()
{
//	int 	list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int 	list[9] = { 6, 3, 7, 4, 9, 1, 5, 2, 8 };

    printf(" Original =");
    print_array(list, 9);

 //    selection_sort(list, 7); 			    // ���� ����
	// printArray(list, 7, "Selection");	    // ��� ���

	// insertion_sort(list, 4); 			    // ���� ����
	// printArray(list, 4, "Insertion");

	// bubble_sort(list, 9); 			        // ���� ����
	// printArray(list, 9, "Bubble   ");

//	insertion_sort_fn(list, 7, descend); 	// �������� ��������
//	printArray(list, 7, "Insert-De");

//	insertion_sort_fn(list, 7, ascend); 	// �������� ��������
//	printArray(list, 7, "Insert-As");

//	shell_sort(list, 9); 	                // �� ����
//	printArray(list, 9, "ShellSort");

	// merge_sort(list, 0, 8); 	// �������� �������� �˰���
	// printArray(list, 9, "MergeSort");	// ���� �� �迭 ���

//  quick_sort(list, 0, 6); 	// �������� �������� �˰���
//  printArray(list, 7, "QuickSort");	// ���� �� �迭 ���

}