#include <stdio.h>
// ��� �˰��� notes
// DP�� ���� ���� �ݴ밳��.
// �ʹ� ���� �ݺ��� �߻�, Ȥ�� ���� ���� �ߺ����� ����ϴ� ��� (�ĺ���ġ ������ ���)���� 
// memorization DP �������. �̸� �����س��� �ٽ� �����ϴ� ����� �� ȿ�����ΰ�.
// bottom-up, top-down ��� �ᵵ ��. 


double power(double x, int n); // �Լ��� ����
double power_for(double x, int n); // �ŵ������� for�� ����
double power_recur_for(double x, int n); // ��� �Լ��� for�� ����

int main() {
    printf("1.   2 ^ 5 = %10.2lf \n", power(2, 5));
    printf("2. 5.2 ^ 7 = %10.2lf \n", power(5.2, 7));
    printf("3.  12 ^ 3 = %10.2lf \n\n", power(12, 3));

    printf("1.   2 ^ 5 = %10.2lf \n", power_for(2, 5));
    printf("2. 5.2 ^ 7 = %10.2lf \n", power_for(5.2, 7));
    printf("3.  12 ^ 3 = %10.2lf \n\n", power_for(12, 3));

    printf("1.   2 ^ 5 = %10.2lf \n", power_recur_for(2, 5));
    printf("2. 5.2 ^ 7 = %10.2lf \n", power_recur_for(5.2, 7));
    printf("3.  12 ^ 3 = %10.2lf \n\n", power_recur_for(12, 3));
}
double power(double x, int n) {
    // ���� ����
    // ��� �������� �ݺ��ϰ� �Ǹ� stack overflow �߻��ϱ⿡ ���� ���� �ʿ�.
    if (n == 0) return 1;
    //�ݺ� ����
    if (n % 2 == 0) return power(x * x, n / 2);
    if (n % 2 == 1) return x * power(x * x, (n - 1) / 2);
}
double power_for(double x, int n) {
    // �ð����⵵ O(n)
    double ret = 1;
    for (int i = 0; i < n; i++)
        ret *= x;
    return ret;
}
double power_recur_for(double x, int n) {
    return 0.0;
}

// ------------------------------------------------------------------------------
// Hanoi Top 

//#include <stdio.h>
//
//void hanoi(int n, char A, char B, char C) {
//    if (n == 1)
//        printf("���� 1 : %c->%c �̵�\n", A, C);
//    else {
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        hanoi(n - 1, A, C, B);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        printf("���� %d : %c->%c �̵�\n", n, A, C);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        hanoi(n - 1, B, A, C);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//    }
//}
//
//int main() {
//    hanoi(4, 'A', 'B', 'C');
//}

