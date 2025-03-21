#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

int main() {

    checkLeak();

    int n = 10;
    // 힙 메모리에 n* sizeof(char) 만크의 공간을 동적으로 할당
    char* ary1 = malloc(n * sizeof(char)); //char ary1[1];
    for (int i = 0; i < n; i++){
        ary1[i] = 'a' + i;
    }
    ary1[n - 1] = '\0';
    printf("%s", ary1);
    printf("\n\n\n\n");
    free(ary1); // 메모리 누수 방지를 위한 메모리 해제 작업

    int m = 20;
    int* ary2 = calloc(m, sizeof(int)); // 4byte * 20 해서 80byte 메모리 할당됨. 해제 필요.
    for (int i = 0; i < m; i++){
        printf("%3d", ary2[i]);
    }
    print("\n\n");

    int Q = 30;
    ary2 = realloc(ary2, Q * sizeof(int));
    for (int i = 0; i < Q; i++){
        printf("%3d", ary2[i]);
    }
    print("\n\n\n\n");
    free(ary2); // 메모리 해제

}