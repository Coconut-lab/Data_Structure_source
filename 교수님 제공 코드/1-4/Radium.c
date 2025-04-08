#include <stdio.h>
#include <math.h>

int main() {
    double initialAmount; // �ʱ� ���ɷ�
    double halfLife;      // �ݰ��� (�ð� ����)
    double time;          // ��� �ð� (�ݰ���� ������ �ð� ����)
    double remainingAmount; // ���� ���ɷ�

    // ����ڷκ��� �Է� �ޱ�
    printf("�ʱ� ���ɷ��� �Է��ϼ���: ");
    scanf("%lf", &initialAmount);

    printf("�ݰ��⸦ �Է��ϼ��� (�ð� ����): ");
    scanf("%lf", &halfLife);

    printf("��� �ð��� �Է��ϼ��� (�ݰ���� ������ �ð� ����): ");
    scanf("%lf", &time);

    // ���� �ݰ��� ����: N(t) = N0 * (1/2)^(t/T)
    // N(t): �ð� t������ ���ɷ�
    // N0: �ʱ� ���ɷ�
    // t: ��� �ð�
    // T: �ݰ���
    remainingAmount = initialAmount * pow(0.5, time / halfLife);

    printf("\n��� ���:\n");
    printf("�ʱ� ���ɷ�: %.2f\n", initialAmount);
    printf("�ݰ���: %.2f\n", halfLife);
    printf("��� �ð�: %.2f\n", time);
    printf("���� ���ɷ�: %.2f\n", remainingAmount);

    // �� ���� �ݰ��Ⱑ �������� ���
    double numberOfHalfLives = time / halfLife;
    printf("����� �ݰ��� ��: %.2f\n", numberOfHalfLives);

    return 0;
}