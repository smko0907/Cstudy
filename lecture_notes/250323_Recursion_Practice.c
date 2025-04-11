// ---------------------- GCD, LCM --------------------------

//#include <stdio.h>
//#include <stdlib.h>
//int gcd(int A, int B) {
//    if (A % B == 0) return B; 
//    else return gcd(B, A % B);
//}
//int lcm(int A, int B) {
//    return A * B / gcd(A, B);
//}
//
//int main() {
//    // 6 , 132
//    printf("1. 12 , 66 -> GCD : %5d,  LCM : %5d \n",
//        gcd(12, 66), lcm(12, 66));
//
//    // 143 , 5549544
//    printf("1. 56056 , 14157 -> GCD : %5d,  LCM : %5d \n",
//        gcd(56056, 14157), lcm(56056, 14157));
//}

// ------------------------ Array Sum ---------------------

#include <stdio.h>
int arySum(int* aryName, int size) { // 배열 원소의 합
    // 종단 조건
    if (size == 1) return aryName[0];
    else return aryName[size - 1] + arySum(aryName, size - 1);
}

int main() {
    int i = 0;
    int value[150];
    for (i = 0; i < 150; i++)value[i] = i + 1;
    printf("Sum:%d\n", arySum(value, 10)); // 55
    // value 배열의 0번방부터 9번 방까지
    // 총 10개의 값을 모두 더한 결과를 반환 값으로 출력
    return 0;
}
