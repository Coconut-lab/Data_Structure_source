// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch03/ArrayStack.h

//-------------------------------------------------------------
// �ڵ� 3.1 �迭�� �̿��� ������ ����


// ������ ������(Element�� MAX_SIZE�� �̸� ���ǵǾ� �־�� ��)
Element data[MAX_SIZE]; // ���� ����� �迭
int top; // ���� ��� �ε���
void error(char str[])
{
    printf("error() ȣ�� ���� ����\n");
    printf("%s\n", str);
    printf("error() ȣ�� ���� ����\n");
    exit(1);
}
// ������ �ֿ� �����
void init_stack()
{
    printf("init_stack() ȣ�� ���� ����\n");
    top = -1;
    printf("init_stack() ȣ�� ���� ����\n");
}
int is_empty()
{
    printf("is_empty() ȣ�� ���� ����\n");
    if (top == -1)
    {
        printf("is_empty() ȣ�� ���� ����\n");
        return 1;
    }
    else 
    {
        printf("is_empty() ȣ�� ���� ����\n");
        return 0;
    }
}
int is_full()
{
    printf("is_full() ȣ�� ���� ����\n");
    printf("is_full() ȣ�� ���� ����\n");
    return (top == (MAX_SIZE - 1));
}
void push(Element e)
{
    printf("push() ȣ�� ���� ����\n");
    if (is_full())
        error("Overflow Error!");
    else data[++top] = e;
    printf("push() ȣ�� ���� ����\n");
}
Element pop()
{
    printf("pop() ȣ�� ���� ����\n");
    if (is_empty())
        error("Underflow Error!");
    printf("pop() ȣ�� ���� ����\n");
    return data[top--];
}
Element peek()
{
    printf("peek() ȣ�� ���� ����\n");
    if (is_empty())
        error("Underflow Error!");
    printf("peek() ȣ�� ���� ����\n");
    return data[top];
}

int size()
{
    printf("size() ȣ�� ���� ����\n");
    printf("size() ȣ�� ���� ����\n");
    return top + 1;
}
