// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch05/LinkedStack.h


//-------------------------------------------------------------
// �ڵ� 5.4 ����� ������ ����


// ������ ������(Element�� �̸� ���ǵǾ� �־�� �ϰ�, MAX_SIZE�� �ʿ� ����)
typedef struct Node {   // �ڱ����� ����ü
    Element data;       // ������ �ʵ�(���� ���)
    struct Node* link;  // ��ũ �ʵ�
} Node;
Node* top = NULL;

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

// ������ �����
int is_empty() { return top == NULL; }
int is_full() { return 0; }
void init_stack() { top = NULL; }
// ���� ����
void push(Element e)
{
    Node* p = alloc_node(e);// �׸� 5.12�� (1)
    p->link = top;          // �׸� 5.12�� (2)
    top = p;                // �׸� 5.12�� (3)
}
// ���� ����
Element pop()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = top;          // �׸� 5.13�� (1)
    top = p->link;          // �׸� 5.13�� (2)
    return free_node(p);    // �׸� 5.13�� (3)
}
// ����(peek) ����
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return top->data;
}
// ������ ��� ��� ����(���� ����)
void destroy_stack()
{
    while (is_empty() == 0) pop();
}

//-------------------------------------------------------------
// �ڵ� 5.6 ����� ������ size()����
int size()
{
    int count = 0;
    for (Node* p = top; p != NULL; p = p->link)
        count++;
    return count;
}
