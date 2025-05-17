// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch05/LinkedQueue.h


typedef struct Node {	// �����ʹ� ��忡 ����Ǿ� ������
    Element data;	// ������ 
    struct Node* link;	// ��ũ: ���� ��带 ����Ŵ 
} Node;
Node* front = NULL;	// ����� ť�� ����
Node* rear = NULL;	// ����� ť�� �Ĵ�

// �ܼ� ���� ���� ����� ���� �Ҵ�� ���� �Լ�
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;	    // ������ �ʱ�ȭ
    p->link = NULL;	    // ��ũ �ʱ�ȭ
    return p;
}
Element free_node(Node* p)
{
    Element e = p->data;    // ������ ����
    free(p);                // ��� ���� ����
    return e;               // ����� ������ ��ȯ
}
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
};

int is_empty()		{ return front == NULL; }
int is_full()		{ return 0; }
void init_queue()	{ front = rear = NULL; }
int size()
{
    int count = 0;
    for (Node* p = front; p != NULL; p = p->link) count++;
    return count;
}

//-------------------------------------------------------------
// �ڵ� 5.11 �ܼ� ����(�����) ť�� ����/���� ����

void enqueue(Element e)
{
    Node* p = alloc_node(e);// ������ ��� ����
    if (is_empty())         // ���� ������ �����̸�
        front = rear = p;   // front�� rear�� p�� ����Ŵ
    else {                  // ť�� ���� ���°� �ƴϸ�
        rear->link = p;     // p�� rear�� �ļӳ��� �����ϰ�
        rear = p;           // rear�� �̵�(p�� ����Ű����)
    }
}
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = front;        // ������ ��带 ����Ű�� ������
    front = front->link;    // front�� �� ĭ ����
    if (front == NULL)      // ���� �� ���� ���°� �Ǹ�,
        rear = NULL;        // rear�� NULL�� �ʱ�ȭ
    return free_node(p);    // p�� ���� �����ϰ� ������ ��ȯ
}
//-------------------------------------------------------------

// ť�� Ž��(peek) ����
Element peek()
{
    if (is_empty())
	error("Underflow Error!");
    return front->data;
}

// ť�� ��� ��� ����(���� ����)
void destroy_queue()
{
    while (is_empty() == 0)
	dequeue();
}
