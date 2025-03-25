// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch03/factorial.c

#include <stdio.h>

//-------------------------------------------------------------
// �ڵ� 3.8 �ݺ� ������ ���丮�� �Լ�
int factorial_iter(int n)
{
    int i, result = 1;
    for (i = 1; i <= n; i++)
        result = result * i;
    return result;
}

//-------------------------------------------------------------
// �ڵ� 3.9 ��ȯ ������ ���丮�� �Լ�
int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

//----------------------------------------------------------------------
// ��ȯ ȣ��� ��ȯ ���� ����� ���� ��ȯ �˰��� ����
int factorial_p(int n)
{
    printf("�Լ� ȣ��: factorial(%d)\n", n);	// ��ȯȣ�� ���� Ȯ���� ���� ��¹�
    int ret;
    if (n == 1) ret = 1;
    else ret = n * factorial_p(n - 1);

    // �Լ��� ��ȯ ��ġ�� �� ������ ��� ���
    printf("�Լ� ��ȯ: factorial(%d) --> %d\n", n, ret);
    return ret;
}
//----------------------------------------------------------------------


void main()
{
    printf("�ݺ� factorial(3) = %d\n", factorial_iter(3));
    printf("��ȯ factorial(3) = %d\n", factorial(3));

    factorial_p(3);
}
