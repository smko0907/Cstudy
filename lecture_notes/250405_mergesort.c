// 합병 정렬

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

void merge(int* arr, int* temp, int st, int mid, int end) {
	for (int i = st; i <= end; i++)
		temp[i] = arr[i];
	// 왼쪽의 값 L, 오른쪽 값 R, 저장해야할 위치 S (sort)
	int L = st, R = mid + 1, S = st;
	while (L <= mid || R <= end) {
		if (L > mid) arr[S++] = temp[R++];
		else if (R > end) arr[S++] = temp[L++];
		else if (temp[L] < temp[R]) arr[S++] = temp[L++];
		else arr[S++] = temp[R++];
	}
}

void divide(int* arr, int* temp, int st, int end) {
	if (st < end) {
		int mid = (st + end) / 2; // 나눠서 재귀
		divide(arr, temp, st, mid); // left 배열
		divide(arr, temp, mid + 1, end); // right 배열 (mid가 겹치면 안됨)
		merge(arr, temp, st, mid, end);
		display_sort(arr, st, end);
	}
}

void mergeSort(int* arr, int size) {
	// 재배치 후 새로 저장할 배열 필요
	int* temp = malloc(size * sizeof(int));
	divide(arr, temp, 0, size - 1); // st(start) = 0번방, end = size-1번방
	free(temp);
}

int main() {
	int size, * arr = NULL;
	printf("배열 크기 입력 : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** 정렬 전 자료 출력 ***\n");
	display(arr, size);
	mergeSort(arr, size);
	printf("\n\n*** 정렬 후 자료 출력 ***\n");
	display(arr, size);
	free(arr); //동적 메모리 해제
	return 0;
}
