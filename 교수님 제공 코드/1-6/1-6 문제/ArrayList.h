// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/ArrayList.h


//--------------------------------------------------------------------
// �ڵ� 6.1 �迭 ������ ����Ʈ


// ����Ʈ�� ������(Element�� MAX_SIZE�� �̸� ���ǵǾ� �־�� ��)
Element data[MAX_SIZE]; // ����� �迭
int size = 0;           // ����� ��
void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

// ����Ʈ�� �����
void init_list() { size = 0; }
int is_empty() { return size == 0; }
int is_full() { return size == MAX_SIZE; }

// ���� ����
void insert(int pos, Element e)
{
    if (is_full())
        error("Overflow Error!");

    if (pos < 0 || pos > size)
        error("Invalid Position Error!");

    for (int i = size - 1; i >= pos; i--)
        data[i + 1] = data[i];
    data[pos] = e;
    size += 1;
}

// ���� ����
Element delete(int pos)
{
    if (is_empty())
        error("Underflow Error!");

    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");

    Element e = data[pos];
    for (int i = pos + 1; i < size; i++)
        data[i - 1] = data[i];
    size -= 1;
    return e;
}

// ���� ����
Element get_entry(int pos)
{
    if (is_empty())
        error("Underflow Error!");
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    return data[pos];
}

//--------------------------------------------------------------------
// �ڵ� 6.3 �迭 ������ ����Ʈ�� �߰� ����

void append(Element e)
{
    insert(size, e);
}
Element pop()
{
    return delete(size - 1);
}
void replace(int pos, Element e)
{
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    data[pos] = e;
}
int find(Element e)
{
    for (int i = 0; i < size; i++)
        if (data[i] == e)
            return i;
    return -1;
}
//--------------------------------------------------------------------



