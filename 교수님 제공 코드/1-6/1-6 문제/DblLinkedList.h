// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/DblLinkedList.h


//--------------------------------------------------------------------
// �ڵ� 6.7 ���� ���� ����Ʈ ����


// ����Ʈ�� ������(Element�� �̸� ���ǵǾ� �־�� ��)
typedef struct DNode {
    Element data; // ������
    struct DNode* prev; // ���� ���
    struct DNode* next; // �ļ� ���
} DNode;

DNode org;

DNode* alloc_dnode(Element e) {
    DNode* p = (DNode*)malloc(sizeof(DNode));
    p->data = e; // ������ �ʱ�ȭ
    p->prev = NULL; // ������ ��ũ �ʱ�ȭ
    p->next = NULL; // �ļӳ�� ��ũ �ʱ�ȭ
    return p;
}
Element free_dnode(DNode* p) {
    Element e = p->data;
    free(p);
    return e;
}
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

// ����Ʈ�� �����
int is_empty() { return org.next == NULL; }
int is_full() { return 0; }
void init_list() { org.next = NULL; }

// ����Ʈ ��� �� ������ ����
DNode* get_node(int pos) {
    DNode* p = &org;
    for (int i = 0; i <= pos; i++, p = p->next)
        if (p == NULL)
            return NULL;
    return p;
}

Element get_entry(int pos) {
    DNode* p = get_node(pos);
    if (pos < 0 || p == NULL)
        error("Invalid Position Error!");
    return p->data;
}
// ���� ����
void insert(int pos, Element e) {
    DNode* before = get_node(pos - 1);
    if (before == NULL)
        error("Invalid Position Error!");
    DNode* p = alloc_dnode(e);
    p->next = before->next;
    p->prev = before;
    before->next = p;
    if (p->next != NULL)
        p->next->prev = p;
}
// ���� ����
Element delete(int pos) {
    DNode* p = get_node(pos);
    if (pos < 0 || p == NULL)
        error("Invalid Position Error!");
    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;
    return free_dnode(p);
}

void destroy_list() { while (is_empty() == 0) delete(0); }
int size() {
    int count = 0;
    for (DNode* p = org.next; p != NULL; p = p->next)
        count++;
    return count;
}


//--------------------------------------------------------------------
#ifdef XXX
// ����Ʈ�� ��ü ����
void replace(int pos, Element e) {
    DNode* p = get_node(pos);	// ������ ���
    if (p == NULL)
        error("Invalid Position Error!");
    p->data = e;
}

// ����Ʈ�� Ž�� ����(���� Ž��)
int find(Element e) {
    int i = 0;
    for (DNode* p = head(); p != NULL; p = p->next, i++)
        if (p->data == e) return i;
    return -1;
}
#endif
