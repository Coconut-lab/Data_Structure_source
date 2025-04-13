#include <stdio.h>
#include <math.h>

int main() {
    double initialAmount;    // �ʱ� ��缺 ������ ��(g)
    double halfLife;         // �ݰ���(��)
    double time;             // ��� �ð�(��)
    double decayConstant;    // �ر� ���(lambda)
    double remainingAmount;  // ���� ��缺 ������ ��(g)

    printf("�ʱ� ��缺 ������ ��(g)�� �Է��ϼ���: ");
    scanf("%lf", &initialAmount);

    printf("�ݰ���(��)�� �Է��ϼ���: ");
    scanf("%lf", &halfLife);

    printf("��� �ð�(��)�� �Է��ϼ���: ");
    scanf("%lf", &time);

    decayConstant = log(2) / halfLife;

    remainingAmount = initialAmount * exp(-decayConstant * time);

    printf("\n===== ���� �ر� ��� ��� =====\n");
    printf("�ʱ� ��缺 ������ ��: %.6f g\n", initialAmount);
    printf("�ݰ���: %.2f ��\n", halfLife);
    printf("�ر� ���(��): %.8f /��\n", decayConstant);
    printf("��� �ð�: %.2f ��\n", time);
    printf("���� ��缺 ������ ��: %.6f g\n", remainingAmount);
    printf("\n");

    return 0;
}