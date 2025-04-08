#include <stdio.h>
#include <math.h>

int main() {
    double initialAmount;    // �ʱ� ��缺 ������ ��(g)
    double halfLife;         // �ݰ���(��)
    double time;             // ��� �ð�(��)
    double decayConstant;    // �ر� ���(lambda)
    double remainingAmount;  // ���� ��缺 ������ ��(g)
    double activityInitial;  // �ʱ� ���� Ȱ����(Bq)
    double activityFinal;    // ���� ���� Ȱ����(Bq)

    printf("�ʱ� ��缺 ������ ��(g)�� �Է��ϼ���: ");
    scanf("%lf", &initialAmount);

    printf("�ݰ���(��)�� �Է��ϼ���: ");
    scanf("%lf", &halfLife);

    printf("��� �ð�(��)�� �Է��ϼ���: ");
    scanf("%lf", &time);

    decayConstant = log(2) / halfLife;

    remainingAmount = initialAmount * exp(-decayConstant * time);

    activityInitial = initialAmount * decayConstant;
    activityFinal = remainingAmount * decayConstant;

    printf("\n===== ���� �ر� ��� ��� =====\n");
    printf("�ʱ� ��缺 ������ ��: %.6f g\n", initialAmount);
    printf("�ݰ���: %.2f ��\n", halfLife);
    printf("�ر� ���(��): %.8f /��\n", decayConstant);
    printf("��� �ð�: %.2f ��\n", time);
    printf("���� ��缺 ������ ��: %.6f g\n", remainingAmount);
    printf("���� ����: %.2f%%\n", (1 - remainingAmount/initialAmount) * 100);
    printf("\n");
    printf("�ʱ� ���� Ȱ����(����): %.6e Bq\n", activityInitial);
    printf("���� ���� Ȱ����(����): %.6e Bq\n", activityFinal);

    return 0;
}