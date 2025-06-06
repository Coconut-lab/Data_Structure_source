// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch10/hash_lp.c

//--------------------------------------------------------------------
// �ڵ� 10.5 ���� �����


#include <stdio.h>
typedef int Entry;  // ���̺� ������ ��Ʈ��
#define M   13      // �ؽ� ���̺��� ũ��
Entry table[M];     // �ؽ� ���̺�
int hashFn(Entry key) { return key % M; }

void init_lp() {                // ���̺� �ʱ�ȭ �Լ�
    for (int i = 0; i < M; i++) // ��� ��Ŷ�� 0(��� �� ��)���� �ʱ�ȭ
        table[i] = 0;

    // �ε��� ��¿� �ڵ� �߰�
    printf("�ε���");			// �ε��� ��¿� �ڵ�
    for (int i = 0; i < M; i++)
        printf("%5d", i);
    printf("\n");

}
void print_lp(const char* msg)  // ���̺� ����� ���� �Լ�
{
    printf("%s: ", msg);
    for (int i = 0; i < M; i++)
        printf("[%2d] ", table[i]);
    printf("\n");
}

void insert_lp(Entry key) {
    int i = hashFn(key);        // �ؽ� �ּ� ���
    for (int k = 0; k < M; k++) {
        if (table[i] == 0 || table[i] == -1) {
            table[i] = key;
            return;
        }
        i = (i + 1) % M;        // ������ ������ ��ġ
    }
}

int search_lp(Entry key) {
    int i = hashFn(key);        // �ؽ� �ּ� ���
    for (int k = 0; k < M; k++) {
        if (table[i] == key) return i;
        if (table[i] == 0) return -1;
        i = (i + 1) % M;        // ������ ������ ��ġ
    }
    return -1;                  // ��� ���̺��� �˻������� Ž�� ����: -1 ��ȯ
}

int delete_lp(Entry key) {
    int i = hashFn(key);        // �ؽ� �ּ� ���
    for (int k = 0; k < M; k++) {
        if (table[i] == key) {
            table[i] = -1;
            return i;
        }
        if (table[i] == 0)      // Ž�� ����: -1 ��ȯ
            return -1;
        i = (i + 1) % M;        // ������ ������ ��ġ
    }
    return -1;                  // ��� ���̺��� �˻������� Ž�� ����: -1 ��ȯ
}

void main()
{
    Entry data[9] = { 45, 27, 88, 9, 71, 60, 46, 38, 24 };
    init_lp();
    print_lp("������");
    for (int i = 0; i < 9; i++) {
        insert_lp(data[i]);
        print_lp(" ");
    }
    printf("46Ž��: %d\n", search_lp(46));
    printf("39Ž��: %d\n", search_lp(39));
    delete_lp(60); print_lp("60����");
    delete_lp(46); print_lp("46����");
}
