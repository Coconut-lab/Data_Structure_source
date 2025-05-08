// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/waiting_list_sim.c


//--------------------------------------------------------------------
// �ڵ� 6.9: ������ ����Ʈ ���α׷�

#include <stdio.h>
#include <stdlib.h>
struct Waiting {    // ���� ������ ť�� ���� ����ü
    int id;         // ����ȣ
    int nperson;    // �ο�
    char info[32];  // ��ȭ��ȣ
};
typedef struct Waiting Element; // Element�� �ڷ��� ����
#include "DblLinkedList.h"      // ���� ���� ����Ʈ ���

// (1) ���ο� ������ ����� ���� reserve(nperson, info) ����
void reserve(int nperson, const char info[])
{
    static int id = 0;
    Element e;
    e.id = ++id;                // ��� ��ȣ �ڵ� �ο�
    e.nperson = nperson;
    strcpy_s(e.info, 32, info);
    insert(size(), e);          // ����Ʈ�� �� �ڿ� �߰�
    printf("<���> ��ȣ %d: �ο� %d�� %s\n", e.id, e.nperson, e.info);
}
// (2) ������ ���� Ȯ���� ���� find(wid) ����
void find(int wid)
{
    int nTeam = 0, nPeople = 0; // ���� �� ���� �ο� ����� ���� ����
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            printf("<Ȯ��> ��ȣ %d�� �� �����: %d�� %d��\n", wid, nTeam, nPeople);
            return;
        }
        nTeam += 1;             // ���� ��
        nPeople += e.nperson;   // ���� ��� �ο�
    }
}
// (3) ������ ��Ҹ� ���� calcel(wid) ����
void cancel(int wid)
{
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            delete(pos);
            printf("<���> %d�� �������� ��ҵǾ����ϴ�.\n", wid);
            return;
        }
    }
}
// (4) ������ ���� �� ĭ �ڷ� �б⸦ ���� delay(id) ����
void delay(int wid)
{
    for (int pos = 0; pos < size() - 1; pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            delete(pos);
            insert(pos + 1, e);
            printf("<����> %d�� �������� �� ĭ ����Ǿ����ϴ�.\n", wid);
            return;
        }
    }
}
// (5) ��ü ������ ����Ʈ ���
void print()
{
    printf("<���>\n");
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        printf(" ��ȣ %2d: %d�� %s\n", e.id, e.nperson, e.info);
    }
    printf("\n");
}
// (6) �մ� �����Ű��
void service()
{
    Element e = delete(0);
    printf("<����> %d�� �մ� ���� (%d��, %s)\n", e.id, e.nperson, e.info);
}
void main()
{
    init_list();
    print();
    reserve(2, "010-xxxx-8762");
    reserve(2, "010-xxxx-3303");
    reserve(5, "010-xxxx-1212");
    reserve(1, "010-xxxx-2305");
    print();

    service();
    print();

    reserve(3, "010-xxxx-4949");
    reserve(4, "010-xxxx-7345");
    print();

    find(4);
    delay(3);
    delay(3);
    print();
    cancel(5);
    print();

    destroy_list();
}


#ifdef XXX
// �� ��� �����ϱ�: replace() ���� �߰��ؾ� ��
void modify()
{
    int	wid;
    printf("�����Ͻ� ������ ��ȣ�� �Է��ϼ���: ");
    scanf_s("%d", &wid);

    for (int pos = 0; pos < size() - 1; pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            printf("����ȣ %2d: %d�� %s\n", e.id, e.nperson, e.info);
            printf("�ο��� ��ȭ��ȣ�� �ٽ� �Է��ϼ���: ");
            scanf_s("%d%s", &e.nperson, e.info, 32);
            replace(pos, e);
            printf("%d�� �������� �����Ǿ����ϴ�.\n", wid);
            return;
        }
    }
}
#endif
