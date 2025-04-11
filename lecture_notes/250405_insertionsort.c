// ���� ����

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}

void display(int* pArr, int size) {
	for (int i = 0; i < size; i++) printf("%5d", pArr[i]);
	printf("\n");
}

int* randomize(int size) {
	int* pArr = (int*)calloc(size, sizeof(int)); //���� �Ҵ�, �� 0 �ʱ�ȭ
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
	return pArr;
}

//void insertion(int* pArr, int size) {
//	for (int i = 1; i < size; i++) {
//		for (int curr = i; curr-1 >=0; curr--) {
//			if (pArr[curr - 1] > pArr[curr])
//				swap(int, pArr[curr - 1], pArr[curr]);
//				printf("������:");
//				display(pArr, size);
//		}
//		printf("nȸ ���� �Ϸ�:");
//		display(pArr, size); 
//		printf("----------\n");
//	}
//}
// --------------------------------------------
// �Ʒ��� ����� ����

void insertion(int* pArr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = i; j - 1 >= 0 && (pArr[j - 1] > pArr[j]); j--)
			swap(int, pArr[j - 1], pArr[j]);
		display(pArr, size);
	}
}


int main() {
	int size, * arr = NULL;
	printf("�迭 ũ�� �Է� : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	insertion(arr, size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr); //���� �޸� ����
}
