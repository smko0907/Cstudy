//list를 활용한 stack 구현

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ListElement;
typedef struct ListNode {
    ListElement data;
    struct ListNode* link;
} ListNode;

typedef ListNode StackElement;
typedef struct StackType {
    StackElement* StackHead; //Stack List 포인터
    int Size; // 현재 저장한 데이터의 개수
} StackType;

StackType* init_stack();
int is_empty(StackType* stack);
int push(StackType* stack, ListElement value);
ListElement pop(StackType* stack);
void free_stack(StackType* stack);
void print(StackType* stack);

int main() {
    srand((unsigned)time(NULL));
    int menu = 0, end = 0;
    ListElement value;
    StackType* s = init_stack();
    for (int i = 0; i < 5; i++) push(s, rand() % 5000 + 1);
    while (1) {
        printf("1. 스택 Push\n");
        printf("2. 스택 Pop\n");
        printf("3. 스택 data print\n");
        printf("메뉴를 입력 하세요. :");
        scanf("%d", &menu);
        while (getchar() != '\n');
        switch (menu) {
        case 1:
            printf("값을 입력하세요. : ");
            scanf("%d", &value);
            while (getchar() != '\n');
            push(s, value);
            printf("%d 값을 넣었습니다.\n", value);
            break;
        case 2:
            printf("Pop 합니다.\n");
            printf("%d 값을 반환 합니다.\n", pop(s));
            break;
        case 3:
            printf("저장된 stack 값\n");
            print(s);
            break;
        default:
            free_stack(s);
            exit(0);
        }
    }
}
StackType* init_stack() {
    StackType* stack = (StackType*)malloc(sizeof(StackType));
    if (stack == NULL) { printf("동적 할당 실패!\n"); return NULL; }
    stack->StackHead = NULL;
    stack->Size = 0;
    return stack;
}
int is_empty(StackType* stack) {
    return (stack->Size == 0); // stack->StackHead == NULL;
}
int push(StackType* stack, ListElement value) {
    StackElement* NewNode = (StackElement*)malloc(sizeof(StackElement));
    if (NewNode == NULL) { printf("동적 할당 실패!\n"); return 0; }
    NewNode->data = value;
    NewNode->link = stack->StackHead;
    stack->StackHead = NewNode;
    stack->Size++;
    return 1;
}
ListElement pop(StackType* stack) {
    if (is_empty(stack)) {
        printf("stack is empty. pop error!\n");
        return 0;
    }
    stack->Size--;
    StackElement* DeleteNode = stack->StackHead;
    stack->StackHead = DeleteNode->link;
    ListElement temp = DeleteNode->data;
    free(DeleteNode);
    return temp;
}
ListElement peek(StackType* stack) { //스택 최상단의 데이터 검색, 찾은 데이터 반환
    if (is_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    }
    return stack->StackHead->data;
}
void print(StackType* stack) {
    if (is_empty(stack)) {
        printf("stack is empty\n");
        return;
    }
    printf(" list -> ");
    for (StackElement* pNode = stack->StackHead; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf("NULL \n");
}
void free_stack(StackType* stack) {
    for (StackElement* pNode = stack->StackHead, *DeleteNode = NULL; pNode != NULL;) {
        DeleteNode = pNode;
        pNode = pNode->link;
        free(DeleteNode);
    }
    free(stack);
}