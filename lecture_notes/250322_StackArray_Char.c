//버퍼에 문자열을 저장해 뒤집는 코드 (stack)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char StackElement;
typedef struct StackType {
    StackElement* data;//스택의 저장 공간을 가리키는 포인터
    int capacity; // 스택의 최대 저장 가능 개수
    int top; // 현재 저장한 데이터의 개수
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
        printf("문자열 입력 [최대 256개, 종료 end 입력]\n");
        printf(" 입력 : ");
        gets(buf);
        if (strcmp(buf, "end") == 0) break;
        for (int i = 0; buf[i] != '\0'; i++) push(stack, buf[i]);
        for (int i = 0; !is_empty(stack); i++) buf[i] = pop(stack);
        printf(" 출력 : ");
        printf("%s\n", buf);
    }
    free_stack(stack);
    printf(" 프로그램 종료... \n\n");
}
StackType* init_stack() {
    StackType* stack = (StackType*)malloc(sizeof(StackType));
    if (stack == NULL) { printf("동적 할당 실패!\n"); return NULL; }
    stack->top = 0;
    stack->capacity = 1;
    stack->data = (StackElement*)malloc(stack->capacity * sizeof(StackElement));
    // element data[s->capacity];
    if (stack->data == NULL) { printf("동적 할당 실패!\n"); free(stack); return NULL; }
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
        if (stack->data == NULL) { printf("동적 할당 실패!\n"); free(temp); return 0; }
        // realloc() : 이미 할당한 공간의 크기를 바꿀 때 realloc 함수를 사용
        // (void *) realloc(void* _Block, size_t _Size) 재할당 할 메모리 주소, 용량
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
        if (stack->data == NULL) { printf("동적 할당 실패!\n"); free(temp); return 0; }
    }
    return stack->data[--(stack->top)];
}
StackElement peek(StackType* stack) { //스택 최상단의 데이터 검색, 찾은 데이터 반환
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
