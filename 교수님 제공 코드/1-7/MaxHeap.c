// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch07/MaxHeap.c


//--------------------------------------------------------------------
// �ڵ� 7.10 �ִ� ���� ����� �׽�Ʈ ���α׷�


#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100   // ���� ���� �迭�� ũ��
#define PARENT(i) (i/2) // i�� �θ� �ε���
#define LEFT(i) (i*2)   // i�� ���� �ڽ� �ε���
#define RIGHT(i) (i*2+1)// i�� ������ �ڽ� �ε���

typedef int HNode;      // ���� ������ �������� �ڷ���
HNode A[MAX_HSIZE];     // ���� �����ϴ� �迭
int heap_size = 0;      // ���� ��ü ��� ��
#define KEY(i) (A[i])   // i�� Ŷ��

void init_heap() { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap() { return (heap_size == MAX_HSIZE - 1); }
HNode heap_peek() { return A[1]; }

void heap_push(HNode n)
{
    if (is_full_heap())         // ���� ��ȭ ����
        return;
    heap_size += 1;             // ��� �ϳ� �߰�
    A[heap_size] = n;           // ���� ��ġ�� ��� ����
    int i = heap_size;          // ���� ��ġ���� �� �� ����
    while (i != 1) {
        if (KEY(i) > KEY(PARENT(i))) {
            A[i] = A[PARENT(i)];// i�� �θ� ��ȯ
            A[PARENT(i)] = n;
            i = PARENT(i);      // �� ���� �ö�
        }
        else break;             // ���ڸ� ã��
    }
}
HNode heap_pop()
{
    if (is_empty_heap())        // ���� ���� ����
        return -1;
    HNode root = A[1];          // ���� ��Ʈ ���
    HNode last = A[heap_size];  // ���� ���� ���
    A[1] = last;                // ���� ��带 �ϴ� ��Ʈ�� ����
    heap_size -= 1;             // ��� �ϳ� ����
    int i = 1;                  // ��Ʈ���� �ٿ� �� ����

    while (LEFT(i) <= heap_size) {
        int child = (LEFT(i) < heap_size && KEY(LEFT(i)) > KEY(RIGHT(i)))
            ? LEFT(i) : RIGHT(i);
        if (KEY(i) > KEY(child)) break; // �� �ڸ��� ã����
        A[i] = A[child];                // i�� �� ū �ڽ� ��ȯ
        A[child] = last;
        i = child;                      // �� ���� ������
    }
    return root;
}
// �� Ʈ�� ��� �Լ�.
void print_heap()
{
    for (int i = 1; i <= heap_size; i++)
        printf("%2d", A[i]);
    printf("\n");
}

//--------------------------------------------------------------------
// �ڵ� 7.11 �迭�� �ִ� ������ �˻��ϱ�

int is_max_heap(HNode arr[], int len)
{
    for (int i = 1; i <= len / 2; i++)
        if (arr[i] < arr[LEFT(i)] || arr[i] < arr[RIGHT(i)])
            return 0;   // ũ�� ������ ���� ���� -> �ִ� ���� �ƴ�
    return 1;           // ��� ��忡�� ũ�� ���� ���� -> �ִ��� ����
}
//--------------------------------------------------------------------

// �׽�Ʈ ���α׷�
void main()
{
    int data[] = { 2, 5, 4, 8, 9, 3, 7, 3 };
    init_heap();
 
    printf("\n�ִ� �� ���� ���� �׽�Ʈ\n");
    for (int i = 0; i < 8; i++) {
        heap_push(data[i]);
        printf("%2d ---> ", data[i]);
        print_heap();
    }
    printf("\n�ִ� �� ���� ���� �׽�Ʈ\n");
    while (!is_empty_heap()) {
        printf("%2d <--- ", heap_pop());
        print_heap();
    }
    printf("\n");


    // �ڵ� 7.11 �׽�Ʈ
    int a[] = { 0, 9, 7, 6, 5, 4, 3, 2, 2, 1, 3 }; // �ִ��� ����
    int b[] = { 0, 9, 7, 6, 5, 3, 3, 2, 2, 1, 4 }; // �ִ��� ����
    printf("a[]: �ִ��� %s\n", is_max_heap(a, 11) ? "����" : "�ƴ�");
    printf("b[]: �ִ��� %s\n", is_max_heap(b, 11) ? "����" : "�ƴ�");
}


#ifdef XXX
#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100	// ��Ʈ�� ��带 ������ �迭�� ũ��
#define PARENT(i) (i/2)	    // i�� �θ� �ε���
#define LEFT(i)   (i*2)		// i�� ���� �ڽ� �ε���
#define RIGHT(i)  (i*2+1)	// i�� ������ �ڽ� �ε���

// ���� ������ ----------------------------------------
typedef int HNode;		// HNode�� �ڷ��� ����
HNode A[MAX_HSIZE];     // ���� �����ϴ� �迭
int heap_size = 0;      // ���� ��ü ��� ��

#define KEY(i)  (A[i])	// �ε��� i�� Ŷ��

void init_heap()    { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap()  { return (heap_size == MAX_HSIZE - 1); }
HNode heap_peek()   { return A[1]; }


void heap_push(HNode n)
{
    if (is_full_heap())             // ���� ���� �� ����
        return;

    heap_size += 1;				    // ��� �ϳ� �߰�
    int i = heap_size;			    // �߰���(������) ����� �ε���
    A[i] = n;				        // ���� ��ġ�� ��� ����

    while (i != 1) {
        if (KEY(i) > KEY(PARENT(i))) {
            A[i] = A[PARENT(i)];	// i�� �θ� ��ȯ
            A[PARENT(i)] = n;
            i = PARENT(i);			// �� ���� �ö�
        }
        else break;                 // ���ڸ� ã��
    }
}

HNode heap_pop()
{
    if (is_empty_heap())            // ���� ���� ����
        return -1;

    HNode	root = A[1];			// ���� ��Ʈ ���
    HNode	last = A[heap_size];	// ���� ���� ���
    A[1] = last;	                // ���� ��带 �ϴ� ��Ʈ�� ����
    heap_size -= 1;					// ��� �ϳ� ����
    int		i = 1;		            // ��Ʈ���� �ٿ��� ����

    while (LEFT(i) <= heap_size) {
        int child = (LEFT(i) < heap_size && KEY(LEFT(i)) > KEY(RIGHT(i)))
                    ? LEFT(i) : RIGHT(i);

        if (KEY(i) > KEY(child)) break; // �� �ڸ��� ã����
        A[i] = A[child];		    // i�� �� ū �ڽ� ��ȯ
        A[child] = last;
        i = child;					// �� ���� ������
    }
    return root;
}

void print_heap()
{
    for (int i = 1; i <= heap_size; i++)
        printf("%2d", A[i]);
    printf("\n");
}

int is_max_heap(HNode arr[], int len)
{
    for (int i = 1; i <= len / 2; i++)
        if (arr[i] < arr[LEFT(i)] || arr[i] < arr[RIGHT(i)])
            return 0;   // ũ�� ������ ���� ���� -> �ִ� ���� �ƴ�
    return 1;           // ��� ��忡�� ũ�� ���� ���� -> �ִ��� ����
}



void main()
{
	int data[] = { 2, 5, 4, 8, 9, 3, 7, 3 };
    init_heap();

    printf("�ִ� �� ���� ���� �׽�Ʈ\n");
    for (int i = 0; i < 8; i++) {
		heap_push(data[i]);
		printf("%2d ---> ", data[i]);
		print_heap();
	}
    printf("\n�ִ� �� ���� ���� �׽�Ʈ\n");
	while (!is_empty_heap()) {
		printf("%2d <--- ", heap_pop());
		print_heap();
	}

    int a[] = { 0, 9, 7, 6, 5, 4, 3, 2, 2, 1, 3 };	// �˻� ����: �ִ��� ����
    int b[] = { 0, 9, 7, 6, 5, 3, 3, 2, 2, 1, 4 };	// �˻� ����: �ִ��� ����
    printf("a[]: �ִ��� %s\n", is_max_heap(a, 11) ? "����" : "�ƴ�");
    printf("b[]: �ִ��� %s\n", is_max_heap(b, 11) ? "����" : "�ƴ�");
}
#endif
