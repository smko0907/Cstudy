// 퀵정렬
// O(n log n)  시간복잡도
// 합병 정렬과 비교했을때 따로 배열을 만들지 않기 때문에 공간복잡도는 1로 가장 효율이 좋음.

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define swap(type, x, y) {type t = x; x = y; y = t;}

void display(int* arr, int size) {
	for (int i = 0; i < size; i++) printf("%5d ", arr[i]);
	printf("\n");
}

void display_sort(int* arr, int st, int end) {
	for (int i = 0; i < st; i++) printf("      ");
	for (int i = st; i <= end; i++) printf("%5d ", arr[i]);
	printf("\n");
}

int* randomize(int size) {
	int* pArr = (int*)calloc(size, sizeof(int)); //동적 할당, 값 0 초기화
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
	return pArr;
}

void quick(int* arr, int st, int end) {
	if (st >= end) return; 	// 재귀 사용시 종단 조건 필수

	int L = st, R = end, pivot = arr[(st + end) / 2]; // 기준점, 교차점 pivot
	while (L <= R) {
		while (arr[L] < pivot) L++;
		while (arr[R] > pivot) R--;
		if (L <= R) {
			swap(int, arr[L], arr[R]);
			L++, R--;
		}
	}
	display_sort(arr, st, end);

	quick(arr, st, R);
	quick(arr, L, end);
}

int main() {
	int size, * arr = NULL;
	printf("배열 크기 입력 : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** 정렬 전 자료 출력 ***\n");
	display(arr, size);
	quick(arr, 0, size - 1);
	printf("\n\n*** 정렬 후 자료 출력 ***\n");
	display(arr, size);
	free(arr); //동적 메모리 해제
	return 0;
}
