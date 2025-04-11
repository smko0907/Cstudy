// ������
// O(n log n)  �ð����⵵
// �պ� ���İ� �������� ���� �迭�� ������ �ʱ� ������ �������⵵�� 1�� ���� ȿ���� ����.

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

void quick(int* arr, int st, int end) {
	if (st >= end) return; 	// ��� ���� ���� ���� �ʼ�

	int L = st, R = end, pivot = arr[(st + end) / 2]; // ������, ������ pivot
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
	printf("�迭 ũ�� �Է� : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	quick(arr, 0, size - 1);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr); //���� �޸� ����
	return 0;
}
