//���ۿ� ���ڿ��� ������ ������ �ڵ� (stack)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char StackElement;
typedef struct StackType {
    StackElement* data;//������ ���� ������ ����Ű�� ������
    int capacity; // ������ �ִ� ���� ���� ����
    int top; // ���� ������ �������� ����
}StackType;

StackType* init_stack();
int is_empty(StackType* stack);
int is_full(StackType* stack);
int push(StackType* stack, StackElement value);
StackElement pop(StackType* stack);
StackElement peek(StackType* stack);
void print(StackType* stack);
void free_stack(StackType* stack);

int main() {
    char buf[257];
    StackType* stack = init_stack();
    while (1) {
        printf("���ڿ� �Է� [�ִ� 256��, ���� end �Է�]\n");
        printf(" �Է� : ");
        gets(buf);
        if (strcmp(buf, "end") == 0) break;
        for (int i = 0; buf[i] != '\0'; i++) push(stack, buf[i]);
        for (int i = 0; !is_empty(stack); i++) buf[i] = pop(stack);
        printf(" ��� : ");
        printf("%s\n", buf);
    }
    free_stack(stack);
    printf(" ���α׷� ����... \n\n");
}
StackType* init_stack() {
    StackType* stack = (StackType*)malloc(sizeof(StackType));
    if (stack == NULL) { printf("���� �Ҵ� ����!\n"); return NULL; }
    stack->top = 0;
    stack->capacity = 1;
    stack->data = (StackElement*)malloc(stack->capacity * sizeof(StackElement));
    // element data[s->capacity];
    if (stack->data == NULL) { printf("���� �Ҵ� ����!\n"); free(stack); return NULL; }
    return stack;
}
int is_empty(StackType* stack) {
    return (stack->top == 0);
}
int is_full(StackType* stack) {
    return (stack->top == stack->capacity);
}
int push(StackType* stack, StackElement value) {
    if (is_full(stack)) {
        stack->capacity *= 2;
        StackElement* temp = stack->data;
        stack->data = (StackElement*)realloc(stack->data, stack->capacity * sizeof(StackElement));// element data[s->capacity];
        if (stack->data == NULL) { printf("���� �Ҵ� ����!\n"); free(temp); return 0; }
        // realloc() : �̹� �Ҵ��� ������ ũ�⸦ �ٲ� �� realloc �Լ��� ���
        // (void *) realloc(void* _Block, size_t _Size) ���Ҵ� �� �޸� �ּ�, �뷮
    }
    stack->data[(stack->top)++] = value;// data[top++]=value;
    return 1;
}
StackElement pop(StackType* stack) {
    if (is_empty(stack)) {
        printf("stack empty error\n");
        return 0;
    }
    if (stack->top < stack->capacity / 2) {
        stack->capacity /= 2;
        StackElement* temp = stack->data;
        stack->data = (StackElement*)realloc(stack->data, stack->capacity * sizeof(StackElement));// element data[s->capacity];
        if (stack->data == NULL) { printf("���� �Ҵ� ����!\n"); free(temp); return 0; }
    }
    return stack->data[--(stack->top)];
}
StackElement peek(StackType* stack) { //���� �ֻ���� ������ �˻�, ã�� ������ ��ȯ
    if (is_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    }
    return stack->data[stack->top - 1];
}
void print(StackType* stack) {
    if (is_empty(stack)) {
        printf("stack empty\n");
        return;
    }
    for (int i = stack->top - 1; i >= 0; i--) {
        printf("%2d : %7c  \n", i, stack->data[i]);
    }
}
void free_stack(StackType* stack) {
    free(stack->data);
    free(stack);
}
