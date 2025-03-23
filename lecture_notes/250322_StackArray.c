#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

//stack 구조체 ( 구성 요소 )
typedef int StackElement;
typedef struct StackType {
    StackElement* data; // 스택으로 사용할 배열의 주소
    int capacity; // 스택의 총 저장 용량 (배열의 칸 수)
    int top; // 저장할 자료의 위치(=자료 개수)
} StackType;


//Stack ADT
//ADT(추상적 데이터 유형 : Abstract data type)
//자료 구조를 어떻게 다룰지, 기능적 측면을 서술하고 구체화 과정
StackType* init_stack(); //구성요소 초기화
int is_empty(StackType* stack); //텅 빈 상태 확인
int is_full(StackType* stack); //포화 상태 확인 
int push(StackType* stack, StackElement value);
//가장 위에 value 넣기
StackElement pop(StackType* stack);
//가장 위의 자료 꺼내기
StackElement peek(StackType* stack);//맨 위 값 확인
void print(StackType* stack); //자료 출력
void free_stack(StackType* stack); //스택 제거


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
    // top. 새로 저장할 자료의 위치이자 자료의 개수가 0이면 empty
    if (stack->top == 0) return 1;
    else return 0;
}

int is_full(StackType* stack) {
    if (stack->top == stack->capacity) return 1;
    else return 0;
}

int push(StackType* stack, StackElement value) {
    if (is_full(stack)) {
        // 배열을 확장
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(StackElement));
    }
    // 데이터 추가
    stack->data[stack->top++] = value;
    return 1;
}

StackElement pop(StackType* stack) {
    if (is_empty(stack)) return 0;
    return stack->data[--stack->top]; // 현재 가르키고 있는 top의 하나 아래 칸을 pop해와라
}

StackElement peek(StackType* stack) {
    if (is_empty(stack)) return 0;
    return stack->data[stack->top - 1];
}

void free_stack(StackType * stack){
    // 할당받은 것의 역순으로 메모리 해제
    free(stack->data);
    free(stack);
}

void print(StackType* stack) {
    for (int i = stack->top - 1; i >= 0; i--)
        printf("%3d : [%5d] \n", i, stack->data[i]);
    printf("\n\n");
}