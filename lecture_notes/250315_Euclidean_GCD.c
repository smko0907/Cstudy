#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

int main() {
    checkLeak();

    int A, B;
    scanf("%d %d", &A, &B);

    int cnt = 0;
    int R = A % B;
    while (R != 0) {
        A = B;
        B = R;
        R = A % B;
        cnt++;
    }

    //int t = main(A, B);
    //while (A % t != 0 || B % t != 0) t--, cnt++;

    //printf("%d %d  의 최대공약수 : %d [%4d]\n", A, B, t, cnt);
    // 최대공약수 Greatest Command Divisor
}