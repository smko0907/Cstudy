#include <stdio.h>
// 재귀 알고리즘 notes
// DP와 재기는 거의 반대개념.
// 너무 많은 반복문 발생, 혹은 같은 항을 중복으로 계산하는 경우 (파보나치 수열의 계산)에는 
// memorization DP 방법으로. 미리 저장해놓고 다시 접근하는 방식이 더 효율적인것.
// bottom-up, top-down 방식 써도 됨. 


double power(double x, int n); // 함수의 원형
double power_for(double x, int n); // 거듭제곱의 for문 버전
double power_recur_for(double x, int n); // 재귀 함수식 for문 버전

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
    // 종단 조건
    // 계속 무한으로 반복하게 되면 stack overflow 발생하기에 종단 조건 필요.
    if (n == 0) return 1;
    //반복 조건
    if (n % 2 == 0) return power(x * x, n / 2);
    if (n % 2 == 1) return x * power(x * x, (n - 1) / 2);
}
double power_for(double x, int n) {
    // 시간복잡도 O(n)
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
//        printf("원판 1 : %c->%c 이동\n", A, C);
//    else {
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        hanoi(n - 1, A, C, B);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        printf("원판 %d : %c->%c 이동\n", n, A, C);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//        hanoi(n - 1, B, A, C);
//        for (int i = 0; i < n; i++) printf("%d", n); printf("\n");
//    }
//}
//
//int main() {
//    hanoi(4, 'A', 'B', 'C');
//}

