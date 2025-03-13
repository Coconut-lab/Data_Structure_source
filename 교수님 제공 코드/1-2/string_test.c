// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/string_test.c

//-------------------------------------------------------------
// �ڵ� 2.2 ���ڿ� �׽�Ʈ

#include <stdio.h>
#include <string.h>             // ���ڿ� ����, ���� ��� ���� �Լ� ����� ����
void main()
{
    char s1[16] = "Hello World";
    char s2[] = "Hello World";
    char s3[16] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0' };
    char s4[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' };
    char s5[20];

    //s4 = s1;                  // ����: ���ڿ��� ���� �����ڷ� ���� �Ұ�
    strcpy_s(s5, 20, s1);       // ���ڿ� s1�� ũ�Ⱑ 20�� ���ڹ迭 s5�� ����

    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("s3: %s\n", s3);
    printf("s4: %s\n", s4);
    printf("s5: %s\n", s5);
    printf("���ڿ� s1�� ����: %zd\n", strlen(s1));
    printf("���ڿ� s2�� ����: %zd\n", strlen(s2));
}
