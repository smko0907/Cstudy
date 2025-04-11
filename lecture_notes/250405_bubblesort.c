//���� ����
// sliding window, �κ��� ����

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

void bubble(int* pArr, int size) {
	// �������� ���� ���� ����.
	//int* swapArr = (int*)calloc(size, sizeof(int));
	//for (int i = 1; i < size; i++) {
	//	// ���� ���ϴ� ���� ������(����)������ ũ�� swap
	//	if (pArr[i] > pArr[i + 1]) {
	//		swapArr[i] = pArr[i + 1];
	//		swapArr[i + 1] = pArr[i];
	//	}
	//	// ���� ���ϴ� ���� ������(����)������ ������ �״�� �α�
	//}
	//return swapArr;

	// --------------------------------------------
	for (int re = 0; re < size - 1; re++) {
		int check = 1;
		for (int start = 1; start < size - re; start++) {
			if (pArr[start - 1] > pArr[start])
				swap(int, pArr[start - 1], pArr[start]);
				check = 0;
		}
		if (check) return; // check�� 1�̶��. �� swap�� ���̷�����ٸ� return
		display(pArr, size);
	}
}

void improvedBubble(int* pArr, int size) {

}

int main() {
	int size, * arr = NULL;
	printf("�迭 ũ�� �Է� : ");
	scanf("%d", &size);

	arr = randomize(size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	bubble(arr, size);
	//improvedBubble(arr, size);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr); //���� �޸� ����
	return 0;
}
