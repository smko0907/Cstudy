// ��Ŷ (���) ���� 
// ����: �������⵵ ������. ���̳ʽ�, �Ǽ� ���� �� �� ����
// �׷��� ������ �޸� ���� �����ص� ���� X


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

//void bucket(int* arr, int size) {
//	int count = arr[0];
//	for (int i = 0; i < size; i++)
//		count = max(count, arr[i]);
//
//	int* B = calloc(count + 1, sizeof(int)); //bucket �迭
//
//	for (int i = 0; i < size; i++) {
//		B[arr[i]]++; // ��Ŷ�� ����
//	}
//
//	for (int i = 0, bi = 0; i < size; i++) {
//		while (!B[bi]) bi++; // B �迭�ȿ� ������ ������ (0�� �ƴ϶��) ����.
//		arr[i] = bi;
//		B[bi]--;
//	}
//
//	free(B);
//}


void bucket(int* arr, int size, int radix) {
	int digit = 0; //������ �ִ� ���� �ڸ��� (= �ݺ�Ƚ��) ã��
	for (int i = 0; i < size; i++)
		while (arr[i] / (int)pow(radix, digit))
			digit++;
	// ���� ������ �ӽ� �迭
	int* temp = (int*)malloc(size * sizeof(int));
	if (temp == NULL) exit(1);
	// �ڸ��� ������ ���� ���� ���� == temp �迭�� ������ ��ġ �ľ�
	int* counts = (int*)malloc(radix * sizeof(int));
	if (counts == NULL) exit(1);
	// �ڸ��� ��ŭ �ݺ�
	for (int repeat = 0; repeat < digit; repeat++) {
		// counts �迭 ����
		for (int i = 0; i < radix; i++)
			counts[i] = 0;
		// ���� �� ���� �ڸ��� ���� & ���� �ľ�
		for (int i = 0; i < size; i++)
			counts[(arr[i] / (int)pow(radix, repeat)) % radix]++;
		// �������� temp �迭�� ������ ��ġ�� ���������� ���
		for (int i = 1; i < radix; i++)
			counts[i] += counts[i - 1];
		// ���� �迭�� ���� ���� ������ temp �迭�� �Ҵ�� ��ġ�� ���ʷ� ����
		for (int i = size - 1; i >= 0; i--)
			temp[--counts[(arr[i] / (int)pow(radix, repeat)) % radix]] = arr[i];
		// �ڸ��� �� ���ĵ� �� ���� �迭�� ����
		for (int i = 0; i < size; i++) arr[i] = temp[i];
		display(arr, size);
	}
	free(temp);
	free(counts);
}

int main() {
	int size, * arr = NULL;
	printf("�迭 ũ�� �Է� : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	bucket(arr, size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr); //���� �޸� ����
	return 0;
}