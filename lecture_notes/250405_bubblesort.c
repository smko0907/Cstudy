//버블 정렬
// sliding window, 부분합 관련

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

void bubble(int* pArr, int size) {
	// 오름차순 버블 정렬 기준.
	//int* swapArr = (int*)calloc(size, sizeof(int));
	//for (int i = 1; i < size; i++) {
	//	// 현재 비교하는 값이 오른쪽(다음)값보다 크면 swap
	//	if (pArr[i] > pArr[i + 1]) {
	//		swapArr[i] = pArr[i + 1];
	//		swapArr[i + 1] = pArr[i];
	//	}
	//	// 현재 비교하는 값이 오른쪽(다음)값보다 작으면 그대로 두기
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
		if (check) return; // check가 1이라면. 즉 swap이 안이루어졌다면 return
		display(pArr, size);
	}
}

void improvedBubble(int* pArr, int size) {

}

int main() {
	int size, * arr = NULL;
	printf("배열 크기 입력 : ");
	scanf("%d", &size);

	arr = randomize(size);
	printf("\n\n*** 정렬 전 자료 출력 ***\n");
	display(arr, size);
	bubble(arr, size);
	//improvedBubble(arr, size);
	printf("\n\n*** 정렬 후 자료 출력 ***\n");
	display(arr, size);
	free(arr); //동적 메모리 해제
	return 0;
}
