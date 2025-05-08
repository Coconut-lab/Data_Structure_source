// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/DblLinkedDeque.h


//--------------------------------------------------------------------
// �ڵ� 6.8 �������� ����� ���� ����(�Ĵ� ������)


// ���� ������(Element�� �̸� ���ǵǾ� �־�� ��. MAX_SIZE�� �ʿ� ����)
typedef struct DNode {
    Element data;       // ������
    struct DNode* prev; // ���� ���
    struct DNode* next; // �ļ� ���
} DNode;
DNode* front = NULL;    // ����
DNode* rear = NULL;     // �Ĵ�

DNode* alloc_dnode(Element e)
{
    DNode* p = (DNode*)malloc(sizeof(DNode));
    p->data = e;	// ������ �ʱ�ȭ
    p->prev = NULL;	// ������ ��ũ �ʱ�ȭ
    p->next = NULL;	// �ļӳ�� ��ũ �ʱ�ȭ
    return p;
}
Element free_dnode(DNode* p)
{
    Element e = p->data;
    free(p);
    return e;
}
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
};


// ����� ���� �ֿ� �����
int is_empty() { return front == NULL; }
int is_full() { return 0; }
void init_deque() { front = rear = NULL; }
int size()
{
	int count = 0;
	for (DNode* p = front; p != NULL; p = p->next) count++;
	return count;
}
void add_front(Element e)
{
    DNode* p = alloc_dnode(e);
    if (is_empty())
        front = rear = p; 
    else {
	p->next = front;
	front->prev = p;
	front = p;
    }
}
void add_rear(Element e)
{
    DNode* p = alloc_dnode(e);
    if (is_empty())
	front = rear = p;
    else {
	p->prev = rear;
	rear->next = p;
	rear = p;
    }
}

// ���� ���� ����
Element delete_front()
{
    if (is_empty())
	error("Underflow Error!");

    DNode* p = front;			// ������ ���
    if (front == rear)			// ��Ұ� �ϳ��� ���
	front = rear = NULL;
    else {						// ��Ұ� �� �̻��� ���
	front = front->next;
	front->prev = NULL;
    }
    return free_dnode(p);
}

//--------------------------------------------------------------------
// �Ĵ� ���� ����
Element delete_rear()
{
    if (is_empty())
	error("Underflow Error!");

    DNode* p = rear;        // �׸� 6.20�� (1)
    if (front == rear)      // ��Ұ� �ϳ��� ���
        front = rear = NULL;
    else {                  // ��Ұ� �� �̻��� ���
        rear = rear->prev;  // �׸� 6.20�� (2)
        rear->next = NULL;
    }
    return free_dnode(p);   // �׸� 6.20�� (3)
}
//--------------------------------------------------------------------

// Ž��(peek) ����
Element get_front()
{
    if (is_empty())
	error("Underflow Error!");
    return front->data;
}
Element get_rear()
{
    if (is_empty())
	error("Underflow Error!");
    return rear->data;
}

// ť�� ��� ��� ����(���� ����)
void destroy_deque()
{
    while (is_empty() == 0)
	delete_rear();
}
