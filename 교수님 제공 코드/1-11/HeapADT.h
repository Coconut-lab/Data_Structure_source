// HeapADT.h: ���� �����Ϳ� ����(�迭 ����)

// ����: ���뿡 ���� �׻� ������ ���� �����ؾ� ��
// #define HNode	...		// Ʈ�� ��忡 ������ ������ �ڷ���
// #define MAX_HSIZE ...	// ��Ʈ�� ��带 ������ �迭�� ũ��


// #define Compare(n1,n2)	((n1)->data - (n2)->data)

#define Parent(i) (heap[i/2])	// i�� �θ� ��� 
#define Left(i) (heap[i*2])		// i�� ���� �ڽ� ��� 
#define Right(i) (heap[i*2+1])	// i�� ������ �ڽ� ��� 


// ���� ������ ----------------------------------------
HNode heap[MAX_HSIZE];
int heap_size=0;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_heap()	{ heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap()	{ return (heap_size == MAX_HSIZE - 1); }

HNode heap_peek()		{ return heap[1]; }

void heap_push(HNode n)
{
	if (is_full_heap()) 
		error("Overflow Error!");
	
	heap_size += 1;				// ��� �ϳ� �߰�
	int i = heap_size;			// �߰���(������) ����� �ε���

	// �߰��� ����� �켱������ �� ������ ��� ����
	while (i != 1 && Compare(n, Parent(i)) > 0) {
		heap[i] = Parent(i);	// �θ� �����(����)
		i /= 2;					// �� ���� �ö�
	}
	heap[i] = n;				// ������ ��ġ�� �� ��� ����
}

HNode heap_pop()
{
	if (is_empty_heap() != 0)
		error("Underflow Error!");

	HNode	root = heap[1];			// ���� ��Ʈ ���
	HNode	last = heap[heap_size];	// ���� ������ ���
	int		pid = 1, cid = 2;		// ��Ʈ�� ���� �ڽ��� �ε���

	heap_size -= 1;					// ��� �ϳ� ����

	while (cid <= heap_size) {
		// ������ �ڽ��� �켱������ �� ������ cid�� ������ �ڽ��� �ε���
		if (cid<heap_size && Compare(Left(pid), Right(pid))<0)
			cid++;

		// ������ ����� �켱������ �ڽĺ��� ������ --> ���ڸ��� ã��
		if (Compare(last, heap[cid]) >= 0)
			break;

		// �ƴϸ�
		heap[pid] = heap[cid];		// �ڽ��� �θ�� ����ø�
		pid = cid;					// �� ���� ������
		cid *= 2;					// �� ���� ������
	}
	heap[pid] = last;

	return root;
}
