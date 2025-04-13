// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch04/CircularQueue.h


//-------------------------------------------------------------
// �ڵ� 4.1 �迭�� �̿��� ���� ť�� ����

// ���� ť�� ������(Element�� MAX_SIZE�� �̸� ���ǵǾ� �־�� ��)
Element data[MAX_SIZE]; // ����� �迭
int front; // ���� �ε���
int rear; // �Ĵ� �ε���

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}
// ���� ť�� �ֿ� �����
void init_queue()
{
    front = rear = 0;
}
int is_empty()
{
    return front == rear;
}
int is_full()
{
    return front == (rear + 1) % MAX_SIZE;
}
void enqueue(Element val)
{
    if (is_full())
        error("Overflow Error!");
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = val;
}
// ����ť�� ���� ����
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    front = (front + 1) % MAX_SIZE;
    return data[front];
}
// ����ť�� Ž��(peek) ����
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return data[(front + 1) % MAX_SIZE];
}

// ������ ��ȭ��ȣ ���� �Լ�
void generate_random_phone(char* phone) {
    int middle = rand() % 10000;
    int last = rand() % 10000;

    sprintf(phone, "010-%04d-%04d", middle, last);
}
