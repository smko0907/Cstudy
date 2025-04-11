// 삽입 정렬

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}

void display(int* pArr, int size) {
	for (int i = 0; i < size; i++) printf("%5d", pArr[i]);
	printf("\n");
}

int* randomize(int size) {
	int* pArr = (int*)calloc(size, sizeof(int)); //동적 할당, 값 0 초기화
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
	return pArr;
}

//void insertion(int* pArr, int size) {
//	for (int i = 1; i < size; i++) {
//		for (int curr = i; curr-1 >=0; curr--) {
//			if (pArr[curr - 1] > pArr[curr])
//				swap(int, pArr[curr - 1], pArr[curr]);
//				printf("정렬중:");
//				display(pArr, size);
//		}
//		printf("n회 정렬 완료:");
//		display(pArr, size); 
//		printf("----------\n");
//	}
//}
// --------------------------------------------
// 아래가 강사님 예시

void insertion(int* pArr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = i; j - 1 >= 0 && (pArr[j - 1] > pArr[j]); j--)
			swap(int, pArr[j - 1], pArr[j]);
		display(pArr, size);
	}
}


int main() {
	int size, * arr = NULL;
	printf("배열 크기 입력 : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** 정렬 전 자료 출력 ***\n");
	display(arr, size);
	insertion(arr, size);
	printf("\n\n*** 정렬 후 자료 출력 ***\n");
	display(arr, size);
	free(arr); //동적 메모리 해제
}
