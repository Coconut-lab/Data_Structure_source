// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch05/CirLinkedQueue.h


//-------------------------------------------------------------
// �ڵ� 5.8 ����� ť�� ����


// ť�� ������(Element�� �̸� ���ǵǾ� �־�� ��. MAX_SIZE�� �ʿ� ����)
typedef struct Node { // �ڱ����� ����ü
    Element data; // ������ �ʵ�(���� ���)
    struct Node* link; // ��ũ �ʵ�
} Node;
Node* rear = NULL;

Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e; // ������ �ʱ�ȭ
    p->link = NULL; // ��ũ �ʱ�ȭ
    return p;
}
Element free_node(Node* p)
{
    Element e = p->data;    // ������ ����
    free(p);                // ���� ����
    return e;               // ������ ��ȯ
}

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

int is_empty() { return rear == NULL; }
int is_full() { return 0; }
void init_queue() { rear = NULL; }
// ���� ����
void enqueue(Element e)
{
    Node* p = alloc_node(e); // �׸� 5.17�� (1)
    if (is_empty()) { // ���� ������ ����
        rear = p;
        p->link = p;
    }
    else { // ������ �ƴ� ���� ����
        p->link = rear->link; // �׸� 5.17�� (2)
        rear->link = p; // �׸� 5.17�� (3)
        rear = p; // �׸� 5.17�� (4)
    }
}
// ���� ����
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = rear->link; // �׸� 5.18�� (1)
    if (rear == p) // ��尡 �ϳ��� ���
        rear = NULL;
    else // ��尡 �� �̻��� ���
        rear->link = p->link; // �׸� 5.18�� (2)
    return free_node(p); // �׸� 5.18�� (3)
}
// Ž��(peek) ����
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return rear->link->data; // ���� ����� ������ ��ȯ
}
// ��� ��� ����(���� ����) ����
void destroy_queue()
{
    while (is_empty() == 0) dequeue();
}


//-------------------------------------------------------------
// �ڵ� 5.10 ����� ť�� size() ����

int size()
{
    if (is_empty()) // ������ ���� 0 ��ȯ
        return 0;
    int count = 1;
    for (Node* p = rear->link; p != rear; p = p->link)
        count++;
    return count;
}
