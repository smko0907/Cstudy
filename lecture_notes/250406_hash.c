// 해시 함수, 테이블
// 충돌해결책 - 개방 주소법(Open Addressing),선형조사법 Linear Probing)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memory Leak.h"

typedef char* KeyType;
typedef char* ValueType;
typedef enum ElementStatus {
	EMPTY, OCCUPIED, DELETED
} ElementStatus;
typedef struct ElementType {
	KeyType key;
	ValueType value;
	ElementStatus status;
} ElementType;
typedef struct HashTable {
	int occupiedCount;
	int size;
	ElementType* table;
} HashTable;

//해쉬 ADT
HashTable* initHashTable(int TableSize); // 초기화
void set(HashTable** HT, KeyType _key, ValueType _value); // 삽입
ValueType get(HashTable* HT, KeyType _key); // 검색
void erase(HashTable* HT, KeyType _key); // 삭제
void freeHashTable(HashTable* HT); // 해쉬 테이블 삭제

void clear(ElementType* Element); // 저장 공간 삭제
void HashTableResize(HashTable** HT);

// Addess Function
unsigned int HashFunction(KeyType _key) {
	int KeyLength = strlen(_key);
	unsigned int HashValue = 0;
	for (int i = 0; i < KeyLength; i++)
		HashValue = (HashValue << 3) + _key[i];
	return HashValue;
}

// step Function
unsigned int HashFunction2(KeyType _key) {
	int KeyLength = strlen(_key);
	unsigned int HashValue = 0;
	for (int i = 0; i < KeyLength; i++)
		HashValue = (HashValue << 2) + _key[i];
	return HashValue;
}

int main() {
	checkLeak();
	HashTable* T1 = initHashTable(3);
	set(&T1, "금쪽이", "111111");
	set(&T1, "은쪽이", "333333");
	set(&T1, "동쪽이", "555555");
	set(&T1, "철쪽이", "888888");
	set(&T1, "황쪽이", "999999");

	erase(T1, "금쪽이");

	printf("\n\n\n");

	printf("%15s : %15s\n", "금쪽이", get(T1, "금쪽이"));
	printf("%15s : %15s\n", "은쪽이", get(T1, "은쪽이"));
	printf("%15s : %15s\n", "녹쪽이", get(T1, "녹쪽이"));

	printf("\n\n\n");
}

HashTable* initHashTable(int TableSize) {
	HashTable* NewTable = malloc(sizeof(HashTable));
	NewTable->occupiedCount = 0;
	NewTable->size = TableSize;
	NewTable->table = calloc(TableSize, sizeof(ElementType));
	return NewTable;
}

void set(HashTable** HT, KeyType _key, ValueType _value) { //원본을 가르키기 위한 이중포인터 HashTable HT
	// 적재 밀도 계산
	double usage = (*HT)->occupiedCount / (*HT)->size;
	if (usage > 0.5) HashTableResize(HT);

	// key -> HF -> HT
	int adr = HashFunction(_key) % (*HT)->size; //방 번호 계산
	int start = adr; //오버플로우 방지를 위해

	// 빈 방을 찾는 과정
	while ((*HT)->table[adr].status != EMPTY) {
		if ((*HT)->table[adr].status != DELETED ||
			strcmp(_key, (*HT)->table[adr].key) != 0) {
			printf("%15s :  %3d 다음칸으로 이동 ....\n", _key, adr);
			adr = (adr + 1) % (*HT)->size; // 끝에 도달하면

			if (start == adr) {
				HashTableResize(HT);
				return set(HT, _key, _value);
			}
		}
		else {//else if (strcmp(_key, (*HT)->table[adr].key == 0)) {
			(*HT)->table[adr].value = _value;
			return;
		}
	}
	printf("%15s : %3d 칸으로 %15s 저장 완료.\n", _key, adr, _value);

	(*HT)->table[adr].key = _key;
	(*HT)->table[adr].value = _value;
	(*HT)->table[adr].status = OCCUPIED; //empty 에서 occupied로 상태 표현
	(*HT)->occupiedCount++; // 저장개수가 하나 늘었음을 저장
}

void freeHashTable(HashTable* HT) { // 해쉬 테이블 삭제
	free(HT->table);
	free(HT);
}

void HashTableResize(HashTable** HT) { // 해쉬 테이블 확장
	HashTable* NT = initHashTable((*HT)->size * 2);
	printf("HT 크기 확장!\n\n");
	for (int i = 0; i < (*HT)->size; i++)
		if ((*HT)->table[i].status == OCCUPIED)
			set(&NT, (*HT)->table[i].key, (*HT)->table[i].value);

	freeHashTable(*HT);
	*HT = NT;
	printf("확장 완료!!\n\n");

}

ValueType get(HashTable* HT, KeyType _key) {

	// key -> HF -> HT
	int adr = HashFunction(_key) % HT->size; //방 번호 계산
	int start = adr; //오버플로우 방지를 위해

	while (HT->table[adr].status != EMPTY) {
		if (HT->table[adr].status == DELETED ||
			strcmp(_key, HT->table[adr].key) != 0) {
			adr = (adr + 1) % HT->size; // 끝에 도달하면
			if (adr == start) {
				return NULL;
			}
		}
		else {//else if (strcmp(_key, (*HT)->table[adr].key == 0)) {
			return HT->table[adr].value;
		}
	}
	return NULL;
}

void erase(HashTable* HT, KeyType _key) {

	// key -> HF -> HT
	int adr = HashFunction(_key) % HT->size;
	int start = adr;

	while (HT->table[adr].status != EMPTY) {
		if (HT->table[adr].status == DELETED ||
			strcmp(_key, HT->table[adr].key) != 0) {
			adr = (adr + 1) % HT->size; 
			if (adr == start) return;
		}
		else {//else if (strcmp(_key, (*HT)->table[adr].key == 0)) {
			HT->table[adr].key = NULL;
			HT->table[adr].value = NULL;
			HT->table[adr].status = DELETED;
			HT->occupiedCount--;
		}
	}
	return NULL;

}