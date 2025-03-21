#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

typedef struct CLASS {  //반 점수 자료형 정의
    int StudentNumber; // 학생 수 
    int* StudentScore; // 학생 별 성적
    double ClassAverage; // 반 평균
} CLASS;

int main(){
    checkLeak();
    int n = 0;
    printf("분 반 수를 입력하세요. : ");
    scanf("%d", &n);

    CLASS* c = calloc(n, sizeof(CLASS)); // CLASS c[n] = { 0 };

    for (int i = 0; i < n; i++) {
        printf("%3d반의 학생 수를 입력하세요. : ", i + 1);
        scanf("%d", &c[i].StudentNumber);

        c[i].StudentScore = malloc(c[i].StudentNumber * sizeof(int));
        // int studentscore[studentNumber];
        for (int p = 0; p < c[i].StudentNumber; p++){
            c[i].StudentScore[p] = rand() % 100 + 1; // random 1 ~ 100 
            c[i].ClassAverage += (double)c[i].StudentScore[p] / c[i].StudentNumber;
        }
    }

    printf("%8s %8s %8s\n", "반", "학생수", "평균");
    for (int i = 0; i < n; i++)
        printf("%6d반 %8d %8.21f점\n", i + 1, c[i].StudentNumber, c[i].ClassAverage");

    printf("\n\n\n");
    
    // 역순으로 해제 작업
    for (int i = 0; i < n; i++)
            free(c[i].StudentScore);  //원점수 배열 해제. 23번줄에서 할당받은거 전부 해제.
    free(c); //모든 반 구조체 해제. 17번줄에서 할당받은 클래스 배열도 해제.
}