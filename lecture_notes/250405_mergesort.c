// �պ� ����

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
	int* pArr = (int*)calloc(size, sizeof(int)); //���� �Ҵ�, �� 0 �ʱ�ȭ
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
	return pArr;
}

void merge(int* arr, int* temp, int st, int mid, int end) {
	for (int i = st; i <= end; i++)
		temp[i] = arr[i];
	// ������ �� L, ������ �� R, �����ؾ��� ��ġ S (sort)
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
		int mid = (st + end) / 2; // ������ ���
		divide(arr, temp, st, mid); // left �迭
		divide(arr, temp, mid + 1, end); // right �迭 (mid�� ��ġ�� �ȵ�)
		merge(arr, temp, st, mid, end);
		display_sort(arr, st, end);
	}
}

void mergeSort(int* arr, int size) {
	// ���ġ �� ���� ������ �迭 �ʿ�
	int* temp = malloc(size * sizeof(int));
	divide(arr, temp, 0, size - 1); // st(start) = 0����, end = size-1����
	free(temp);
}

int main() {
	int size, * arr = NULL;
	printf("�迭 ũ�� �Է� : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	mergeSort(arr, size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr); //���� �޸� ����
	return 0;
}
