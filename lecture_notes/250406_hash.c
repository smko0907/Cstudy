// �ؽ� �Լ�, ���̺�
// �浹�ذ�å - ���� �ּҹ�(Open Addressing),��������� Linear Probing)

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

//�ؽ� ADT
HashTable* initHashTable(int TableSize); // �ʱ�ȭ
void set(HashTable** HT, KeyType _key, ValueType _value); // ����
ValueType get(HashTable* HT, KeyType _key); // �˻�
void erase(HashTable* HT, KeyType _key); // ����
void freeHashTable(HashTable* HT); // �ؽ� ���̺� ����

void clear(ElementType* Element); // ���� ���� ����
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
	set(&T1, "������", "111111");
	set(&T1, "������", "333333");
	set(&T1, "������", "555555");
	set(&T1, "ö����", "888888");
	set(&T1, "Ȳ����", "999999");

	erase(T1, "������");

	printf("\n\n\n");

	printf("%15s : %15s\n", "������", get(T1, "������"));
	printf("%15s : %15s\n", "������", get(T1, "������"));
	printf("%15s : %15s\n", "������", get(T1, "������"));

	printf("\n\n\n");
}

HashTable* initHashTable(int TableSize) {
	HashTable* NewTable = malloc(sizeof(HashTable));
	NewTable->occupiedCount = 0;
	NewTable->size = TableSize;
	NewTable->table = calloc(TableSize, sizeof(ElementType));
	return NewTable;
}

void set(HashTable** HT, KeyType _key, ValueType _value) { //������ ����Ű�� ���� ���������� HashTable HT
	// ���� �е� ���
	double usage = (*HT)->occupiedCount / (*HT)->size;
	if (usage > 0.5) HashTableResize(HT);

	// key -> HF -> HT
	int adr = HashFunction(_key) % (*HT)->size; //�� ��ȣ ���
	int start = adr; //�����÷ο� ������ ����

	// �� ���� ã�� ����
	while ((*HT)->table[adr].status != EMPTY) {
		if ((*HT)->table[adr].status != DELETED ||
			strcmp(_key, (*HT)->table[adr].key) != 0) {
			printf("%15s :  %3d ����ĭ���� �̵� ....\n", _key, adr);
			adr = (adr + 1) % (*HT)->size; // ���� �����ϸ�

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
	printf("%15s : %3d ĭ���� %15s ���� �Ϸ�.\n", _key, adr, _value);

	(*HT)->table[adr].key = _key;
	(*HT)->table[adr].value = _value;
	(*HT)->table[adr].status = OCCUPIED; //empty ���� occupied�� ���� ǥ��
	(*HT)->occupiedCount++; // ���尳���� �ϳ� �þ����� ����
}

void freeHashTable(HashTable* HT) { // �ؽ� ���̺� ����
	free(HT->table);
	free(HT);
}

void HashTableResize(HashTable** HT) { // �ؽ� ���̺� Ȯ��
	HashTable* NT = initHashTable((*HT)->size * 2);
	printf("HT ũ�� Ȯ��!\n\n");
	for (int i = 0; i < (*HT)->size; i++)
		if ((*HT)->table[i].status == OCCUPIED)
			set(&NT, (*HT)->table[i].key, (*HT)->table[i].value);

	freeHashTable(*HT);
	*HT = NT;
	printf("Ȯ�� �Ϸ�!!\n\n");

}

ValueType get(HashTable* HT, KeyType _key) {

	// key -> HF -> HT
	int adr = HashFunction(_key) % HT->size; //�� ��ȣ ���
	int start = adr; //�����÷ο� ������ ����

	while (HT->table[adr].status != EMPTY) {
		if (HT->table[adr].status == DELETED ||
			strcmp(_key, HT->table[adr].key) != 0) {
			adr = (adr + 1) % HT->size; // ���� �����ϸ�
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