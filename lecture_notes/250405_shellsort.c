// 쉘 정렬

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}
void display(int* pArr, int size) {
    for (int i = 0; i < size; i++) printf("%5d", pArr[i]);
    printf("\n");
}
void displayGap(int* pArr, int size, int first, int gap) {
    for (int i = 0; i < size; i++) {
        if (i % gap == first) printf("%5d", pArr[i]);
        else printf("%5s", "");
    }
    printf("\n");
}
int* randomize(int size) {
    int* pArr = (int*)calloc(size, sizeof(int)); //동적 할당, 값 0 초기화
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
    return pArr;
}
void insertion_shell(int* pArr, int first, int size, int gap) {
    for (int start = first + gap; start < size; start += gap) {
        for (int cmp = start; cmp - gap >= first && pArr[cmp - gap] > pArr[cmp]; cmp -= gap) {
            swap(int, pArr[cmp - gap], pArr[cmp]);
        }
    }
}
void shell_sort(int* pArr, int size) {
    for (int gap = size / 2; gap; gap /= 2) {
        for (int first = 0; first < gap; first++) {
            insertion_shell(pArr, first, size, gap);
            displayGap(pArr, size, first, gap);
        }
    }
}
int main() {
    int size, * arr = NULL;
    printf("배열 크기 입력 : ");
    scanf("%d", &size);
    arr = randomize(size);
    printf("\n\n*** 정렬 전 자료 출력 ***\n");
    for (int i = 0; i < size; i++) printf("%5d", i); printf("\n");
    display(arr, size);
    shell_sort(arr, size);
    printf("\n\n*** 정렬 후 자료 출력 ***\n");
    display(arr, size);
    free(arr); //동적 메모리 해제
}
