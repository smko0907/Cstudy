//스택을 활용한 미로탐색 문제

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// 좌표 설정 구조체 
typedef struct point {
    int row;
    int col;
} point;

typedef point StackElement;
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
void printStack(StackType* stack);
void free_stack(StackType* stack);

void hideCursor() {
    CONSOLE_CURSOR_INFO CurInfo; // 커서 옵션 구조체
    CurInfo.dwSize = 1;// 커서 크기 (1~100%)
    CurInfo.bVisible = 0; // false
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);//커서 숨기기
}

void printMap(int** map, int x, int y) {
    for (int i = 0; i < y + 2; i++) {
        for (int j = 0; j < x + 2; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int checkMap(int MapRow, int MapColumn, int row, int col) {
    if (row <= 0 || MapRow <= row) return 0;
    if (col <= 0 || MapColumn <= col) return 0;
    return 1;
}

int main() {
    hideCursor(); // 커서 숨기기
    COORD pos = { 0, 0 };
    while (1) {
        system("cls");
        //미로의크기입력
        int row = 0, column = 0;
        printf("미로의 가로, 세로를 입력하세요. : ");
        scanf("%d %d", &row, &column);
        while (getchar() != '\n');
        //맵 구현 ( 벽 : 1 , 통로 : 0 )
        srand(time(NULL));
        int** map = (int**)malloc((column + 2) * sizeof(int*));
        for (int i = 0; i < column + 2; i++)
            map[i] = (int*)malloc((row + 2) * sizeof(int));
        for (int i = 0; i < column + 2; i++)
            for (int j = 0; j < row + 2; j++) {
                if (i == 0 || i == column + 1 || j == 0 || j == row + 1) map[i][j] = '1'; //겉테두리는1
                else {
                    map[i][j] = rand() % 5 + '0';
                    if (map[i][j] != '1') map[i][j] = '0';
                }
            }
        //입구 : S , 출구 : E
        map[1][0] = 'S';
        map[column][row + 1] = 'E';
        //현재 나의 위치
        map[1][1] = '0';
        map[row][column] = '0';
        point p = { 1, 0 }; // x=0, y=1
        //스택 선언 & 초기화
        StackType* stack = init_stack();
        push(stack, p);
        //길찾기
        while (!is_empty(stack)) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 커서 좌표(0,0) 이동
            printf("미로 찾는 중...\n");
            printMap(map, row, column);
            //전진
            p = pop(stack);
            if (map[p.row][p.col] == 'E') break;
            else if (map[p.row][p.col] == '.') continue;
            else map[p.row][p.col] = '.';

            // left , up , right , down
            int dr[] = { 0, -1, 0, 1 };
            int dc[] = { -1, 0, 1, 0 };

            for (int i = 0; i < _countof(dr); i++) {
                point way4 = { p.row + dr[i], p.col + dc[i] };
                if (checkMap(row + 2, column + 2, way4.row, way4.col) &&
                    map[way4.row][way4.col] != '1' &&
                    map[way4.row][way4.col] != '.') {
                    push(stack, way4);
                }
            }
        }
        system("cls");
        if (map[p.row][p.col] == 'E') {
            printf("미로 찾기 성공!\n");
            map[p.row][p.col] = '.';
        }
        else printf("미로 찾기 실패...\n");
        printMap(map, row, column);
        system("pause");
        //동적할당해제
        free_stack(stack);
        for (int i = 0; i < column + 2; i++) {
            free(map[i]);
        }
        free(map);
    }
}

StackType* init_stack() {
    StackType* stack = (StackType*)malloc(sizeof(StackType));
    if (stack == NULL) { printf("동적 할당 실패!\n"); return NULL; }
    stack->top = 0;
    stack->capacity = 1;
    stack->data = (StackElement*)malloc(stack->capacity * sizeof(StackElement)); // element data[s->capacity];
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
        return;
    }
    if (stack->top < stack->capacity / 2) {
        stack->capacity /= 2;
        StackElement* temp = stack->data;
        stack->data = (StackElement*)realloc(stack->data, stack->capacity * sizeof(StackElement));// element data[s->capacity];
        if (stack->data == NULL) { printf("동적 할당 실패!\n"); free(temp); return; }
    }
    return stack->data[--(stack->top)];
}
StackElement peek(StackType* stack) { //스택 최상단의 데이터 검색, 찾은 데이터 반환
    if (is_empty(stack)) {
        printf("stack is empty\n");
        return;
    }
    else {
        return stack->data[stack->top - 1];
    }
}
void printStack(StackType* stack) {
    if (is_empty(stack)) {
        printf("stack empty\n");
        return;
    }
    for (int i = stack->top - 1; i >= 0; i--) {
        printf("%2d : %7d  \n", i, stack->data[i]);
    }
}
void free_stack(StackType* stack) {
    free(stack->data);
    free(stack);
}
