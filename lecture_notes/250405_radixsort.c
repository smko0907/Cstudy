// 버킷 (기수) 정렬 
// 단점: 공간복잡도 안좋음. 마이너스, 실수 값은 쓸 수 없음
// 그러나 요즘은 메모리 많이 차지해도 문제 X


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

//void bucket(int* arr, int size) {
//	int count = arr[0];
//	for (int i = 0; i < size; i++)
//		count = max(count, arr[i]);
//
//	int* B = calloc(count + 1, sizeof(int)); //bucket 배열
//
//	for (int i = 0; i < size; i++) {
//		B[arr[i]]++; // 버킷에 저장
//	}
//
//	for (int i = 0, bi = 0; i < size; i++) {
//		while (!B[bi]) bi++; // B 배열안에 내용이 있으면 (0이 아니라면) 멈춰.
//		arr[i] = bi;
//		B[bi]--;
//	}
//
//	free(B);
//}


void bucket(int* arr, int size, int radix) {
	int digit = 0; //정렬할 최대 값의 자리수 (= 반복횟수) 찾기
	for (int i = 0; i < size; i++)
		while (arr[i] / (int)pow(radix, digit))
			digit++;
	// 값을 저장할 임시 배열
	int* temp = (int*)malloc(size * sizeof(int));
	if (temp == NULL) exit(1);
	// 자리수 분할한 값의 수량 저장 == temp 배열에 저장할 위치 파악
	int* counts = (int*)malloc(radix * sizeof(int));
	if (counts == NULL) exit(1);
	// 자리수 만큼 반복
	for (int repeat = 0; repeat < digit; repeat++) {
		// counts 배열 비우기
		for (int i = 0; i < radix; i++)
			counts[i] = 0;
		// 정렬 할 값의 자리수 분할 & 수량 파악
		for (int i = 0; i < size; i++)
			counts[(arr[i] / (int)pow(radix, repeat)) % radix]++;
		// 수량으로 temp 배열에 저장할 위치를 누적합으로 계산
		for (int i = 1; i < radix; i++)
			counts[i] += counts[i - 1];
		// 원본 배열의 가장 뒤의 값부터 temp 배열의 할당된 위치로 차례로 저장
		for (int i = size - 1; i >= 0; i--)
			temp[--counts[(arr[i] / (int)pow(radix, repeat)) % radix]] = arr[i];
		// 자리수 별 정렬된 값 원본 배열로 저장
		for (int i = 0; i < size; i++) arr[i] = temp[i];
		display(arr, size);
	}
	free(temp);
	free(counts);
}

int main() {
	int size, * arr = NULL;
	printf("배열 크기 입력 : ");
	scanf("%d", &size);
	arr = randomize(size);
	printf("\n\n*** 정렬 전 자료 출력 ***\n");
	display(arr, size);
	bucket(arr, size);
	printf("\n\n*** 정렬 후 자료 출력 ***\n");
	display(arr, size);
	free(arr); //동적 메모리 해제
	return 0;
}