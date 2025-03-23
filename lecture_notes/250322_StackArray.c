#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

//stack ����ü ( ���� ��� )
typedef int StackElement;
typedef struct StackType {
    StackElement* data; // �������� ����� �迭�� �ּ�
    int capacity; // ������ �� ���� �뷮 (�迭�� ĭ ��)
    int top; // ������ �ڷ��� ��ġ(=�ڷ� ����)
} StackType;


//Stack ADT
//ADT(�߻��� ������ ���� : Abstract data type)
//�ڷ� ������ ��� �ٷ���, ����� ������ �����ϰ� ��üȭ ����
StackType* init_stack(); //������� �ʱ�ȭ
int is_empty(StackType* stack); //�� �� ���� Ȯ��
int is_full(StackType* stack); //��ȭ ���� Ȯ�� 
int push(StackType* stack, StackElement value);
//���� ���� value �ֱ�
StackElement pop(StackType* stack);
//���� ���� �ڷ� ������
StackElement peek(StackType* stack);//�� �� �� Ȯ��
void print(StackType* stack); //�ڷ� ���
void free_stack(StackType* stack); //���� ����


int main() {
    checkLeak();
    StackType* s1 = init_stack();

    push(s1, 9);
    push(s1, 3);
    push(s1, 1);

    printf("POP : %d\n\n", pop(s1));
    printf("PEEK : %d\n\n", peek(s1));

    print(s1);
    free_stack(s1);
}


StackType* init_stack() {
    StackType* NewStack = malloc(sizeof(StackType));
    NewStack->top = 0;
    NewStack->capacity = 1;
    NewStack->data = malloc(NewStack->capacity * sizeof(StackElement));
    return NewStack;
}

int is_empty(StackType* stack) {
    // top. ���� ������ �ڷ��� ��ġ���� �ڷ��� ������ 0�̸� empty
    if (stack->top == 0) return 1;
    else return 0;
}

int is_full(StackType* stack) {
    if (stack->top == stack->capacity) return 1;
    else return 0;
}

int push(StackType* stack, StackElement value) {
    if (is_full(stack)) {
        // �迭�� Ȯ��
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(StackElement));
    }
    // ������ �߰�
    stack->data[stack->top++] = value;
    return 1;
}

StackElement pop(StackType* stack) {
    if (is_empty(stack)) return 0;
    return stack->data[--stack->top]; // ���� ����Ű�� �ִ� top�� �ϳ� �Ʒ� ĭ�� pop�ؿͶ�
}

StackElement peek(StackType* stack) {
    if (is_empty(stack)) return 0;
    return stack->data[stack->top - 1];
}

void free_stack(StackType * stack){
    // �Ҵ���� ���� �������� �޸� ����
    free(stack->data);
    free(stack);
}

void print(StackType* stack) {
    for (int i = stack->top - 1; i >= 0; i--)
        printf("%3d : [%5d] \n", i, stack->data[i]);
    printf("\n\n");
}