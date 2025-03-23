//������ Ȱ���� �̷�Ž�� ����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// ��ǥ ���� ����ü 
typedef struct point {
    int row;
    int col;
} point;

typedef point StackElement;
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
void printStack(StackType* stack);
void free_stack(StackType* stack);

void hideCursor() {
    CONSOLE_CURSOR_INFO CurInfo; // Ŀ�� �ɼ� ����ü
    CurInfo.dwSize = 1;// Ŀ�� ũ�� (1~100%)
    CurInfo.bVisible = 0; // false
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);//Ŀ�� �����
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
    hideCursor(); // Ŀ�� �����
    COORD pos = { 0, 0 };
    while (1) {
        system("cls");
        //�̷���ũ���Է�
        int row = 0, column = 0;
        printf("�̷��� ����, ���θ� �Է��ϼ���. : ");
        scanf("%d %d", &row, &column);
        while (getchar() != '\n');
        //�� ���� ( �� : 1 , ��� : 0 )
        srand(time(NULL));
        int** map = (int**)malloc((column + 2) * sizeof(int*));
        for (int i = 0; i < column + 2; i++)
            map[i] = (int*)malloc((row + 2) * sizeof(int));
        for (int i = 0; i < column + 2; i++)
            for (int j = 0; j < row + 2; j++) {
                if (i == 0 || i == column + 1 || j == 0 || j == row + 1) map[i][j] = '1'; //���׵θ���1
                else {
                    map[i][j] = rand() % 5 + '0';
                    if (map[i][j] != '1') map[i][j] = '0';
                }
            }
        //�Ա� : S , �ⱸ : E
        map[1][0] = 'S';
        map[column][row + 1] = 'E';
        //���� ���� ��ġ
        map[1][1] = '0';
        map[row][column] = '0';
        point p = { 1, 0 }; // x=0, y=1
        //���� ���� & �ʱ�ȭ
        StackType* stack = init_stack();
        push(stack, p);
        //��ã��
        while (!is_empty(stack)) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // Ŀ�� ��ǥ(0,0) �̵�
            printf("�̷� ã�� ��...\n");
            printMap(map, row, column);
            //����
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
            printf("�̷� ã�� ����!\n");
            map[p.row][p.col] = '.';
        }
        else printf("�̷� ã�� ����...\n");
        printMap(map, row, column);
        system("pause");
        //�����Ҵ�����
        free_stack(stack);
        for (int i = 0; i < column + 2; i++) {
            free(map[i]);
        }
        free(map);
    }
}

StackType* init_stack() {
    StackType* stack = (StackType*)malloc(sizeof(StackType));
    if (stack == NULL) { printf("���� �Ҵ� ����!\n"); return NULL; }
    stack->top = 0;
    stack->capacity = 1;
    stack->data = (StackElement*)malloc(stack->capacity * sizeof(StackElement)); // element data[s->capacity];
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
        return;
    }
    if (stack->top < stack->capacity / 2) {
        stack->capacity /= 2;
        StackElement* temp = stack->data;
        stack->data = (StackElement*)realloc(stack->data, stack->capacity * sizeof(StackElement));// element data[s->capacity];
        if (stack->data == NULL) { printf("���� �Ҵ� ����!\n"); free(temp); return; }
    }
    return stack->data[--(stack->top)];
}
StackElement peek(StackType* stack) { //���� �ֻ���� ������ �˻�, ã�� ������ ��ȯ
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
