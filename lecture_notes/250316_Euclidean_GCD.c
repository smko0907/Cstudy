#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

int main(){
    checkLeak();

    int A, B;
    scanf("%d %d", &A, &B);

    // ---------------------------------
    // A 약수 수량 파악하기
    int countA = 0;
    for (int d = 1; d <= A; d++)
        if (A % d == 0)
            countA++;
    
    // A 약수를 저장할 배열 만들기
    // int list_A[countA];
    int* list_A = malloc(countA * sizeof(int));

    //list_A 약수 저장하기
    for (int d = 1, i = 0; d <= A; d++)
        if (A % d == 0)
            list_A[i++] = d;
    
    for (int i = 0; i < countA; i++)
        printf("%8d", list_A[i]);

    // ---------------------------------
    // B 약수 수량 파악하기
    int countB = 0;
    for (int d = 1; d <= B; d++)
        if (B % d == 0)
            countB++;
    
    // B 약수를 저장할 배열 만들기
    // int list_B[countB];
    int* list_B = malloc(countB * sizeof(int));

    //list_B 약수 저장하기
    for (int d = 1, i = 0; d <= B; d++)
        if (B % d == 0)
            list_B[i++] = d;
    
    for (int i = 0; i < countB; i++)
        printf("%8d", list_B[i]);

    printf("\n\n");

    // -------------------------------
    // 공약수 수량 파악

    int countC = 0;

    for (int iA = 0; iA < countA; iA++)
        for (int iB = 0; iB < countB; iB++)
            if(list_A[iA] == list_B[iB])
                countC++;

    // -------------------------------
    // 공약수 배열 만들기
    int* list_CD = malloc(countC * sizeof(int));

    int iA = 0, iB = 0, iCD = 0;
    while (iA < countA && iB < countB) {
        if (list_A[iA] == list_B[iB]) {
            list_CD[iCD] = list_A[iA];
            iA++, iB++, iCD++;
        }
        else if (list_A[iA] > list_B[iB]) iB++;
        else if (list_A[iA] < list_B[iB]) iA++;
    }

    for (int i = 0; i < count C; i++)
        printf("%8d", list_CD[i]);
    printf("\n\n");


    free(list_A);
    free(list_B);
    free(list_CD);

}