#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum menu { Enq = 1, Deq, End, Ded, Prt };
typedef int QueueElement;
typedef struct Queue {
    QueueElement* data;
    int capacity;
    int front, rear;
    int size;
} CircularQueueType;

// Queue 초기화
CircularQueueType* QueueInit();
// Queue가 저장한 data는 없는지 확인
int QueueIsEmpty(CircularQueueType* queue);
// Queue가 data로 모두 채워져 있는지 확인
int QueueIsFull(CircularQueueType* queue);
// Queue data 추가
void Enqueue(CircularQueueType** queue, QueueElement data);
// Queue 맨 앞의 data 꺼내기
QueueElement Dequeue(CircularQueueType* queue);
// Queue 배열(data 멤버) 확장
void QueueResize(CircularQueueType** queue);
// Queue data 모두 출력
void PrintQueue(CircularQueueType* queue);
// Queue 삭제
void FreeQueue(CircularQueueType* queue);

//DeQue 삽입 & 삭제 위치 표현
typedef enum direction {
    Rear,
    Front
} Direction;
// Deque data 추가

void Endeque(CircularQueueType** queue, QueueElement data, Direction pos);
// Deque data 꺼내기

QueueElement Dedeque(CircularQueueType* queue, Direction pos);

int main(void) {
    srand((unsigned)time(NULL));
    int menu = 0, de_F_R = 0;
    QueueElement value;
    CircularQueueType* queue = QueueInit();
    for (int i = 10; i < 100; i += 20) Enqueue(&queue, i);
    while (1) {
        printf("1. Queue enqueue\n");
        printf("2. Queue dequeue\n");
        printf("3. Deque endeque\n");
        printf("4. Deque dedeque\n");
        printf("5. Print Queue\n");
        printf("메뉴를 입력 하세요. :");
        scanf("%d", &menu);
        while (getchar() != '\n');
        switch (menu) {
        case Enq:
            printf("값을 입력하세요. : ");
            scanf("%d", &value);
            while (getchar() != '\n');
            Enqueue(&queue, value);
            printf("%d 값을 넣었습니다.\n\n", value);
            break;
        case Deq:
            printf("값을 출력합니다.\n");
            printf("%d\n\n", Dequeue(queue));
            break;
        case End:
            printf("Front 1 / Rear 0 (전단 1 / 후단 0) : ");
            scanf("%d", &de_F_R);
            while (getchar() != '\n');
            printf("값을 입력하세요. : ");
            scanf("%d", &value);
            while (getchar() != '\n');
            Endeque(&queue, value, de_F_R);
            printf("%d 값을 넣었습니다.\n\n", value);
            break;
        case Ded:
            printf("Front 1 / Rear 0 (전단 1 / 후단 0) : ");
            scanf("%d", &de_F_R);
            printf("값을 출력합니다.\n");
            printf("%d\n\n", Dedeque(queue, de_F_R));
            break;
        case Prt:
            PrintQueue(queue);
            break;
        default:
            FreeQueue(queue);
            exit(0);
        }
    }
    return 0;
}
CircularQueueType* QueueInit() {
    CircularQueueType* newqueue = (CircularQueueType*)malloc(sizeof(CircularQueueType));
    if (newqueue == NULL) exit(1);
    newqueue->front = newqueue->rear = newqueue->size = 0;
    newqueue->capacity = 1;
    newqueue->data = (QueueElement*)malloc(newqueue->capacity * sizeof(QueueElement));
    return newqueue;
}
int QueueIsEmpty(CircularQueueType* queue) { return (queue->size == 0); }
int QueueIsFull(CircularQueueType* queue) { return (queue->size == queue->capacity); }
void Enqueue(CircularQueueType** queue, QueueElement data) {
    if (QueueIsFull(*queue)) QueueResize(queue);
    (*queue)->data[(*queue)->rear] = data;
    (*queue)->rear = ((*queue)->rear + 1) % (*queue)->capacity;
    (*queue)->size++;
}
QueueElement Dequeue(CircularQueueType* queue) {
    if (QueueIsEmpty(queue)) { printf(" Queue is empty.\n"); return 0; }
    QueueElement data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}
void QueueResize(CircularQueueType** queue) {
    CircularQueueType* newqueue = QueueInit();
    newqueue->capacity = (*queue)->capacity * 2;
    if ((newqueue->data = (CircularQueueType*)realloc(newqueue->data, newqueue->capacity * sizeof(QueueElement))) == NULL) exit(1);
    while (!QueueIsEmpty(*queue))
        Enqueue(&newqueue, Dequeue((*queue)));
    FreeQueue(*queue);
    *queue = newqueue;
}
void PrintQueue(CircularQueueType* queue) {
    printf(" Queue -> ");
    for (int i = 0, j = queue->front; i < queue->size; i++, j = (j + 1) % queue->capacity)
        printf("%4d -> ", queue->data[j]);
    printf(" End\n\n");
}
void FreeQueue(CircularQueueType* queue) {
    free(queue->data);
    free(queue);
}
void Endeque(CircularQueueType** queue, QueueElement data, Direction pos) {
    if (QueueIsFull(*queue)) QueueResize(queue);
    if (pos == Rear) {
        (*queue)->data[(*queue)->rear] = data;
        (*queue)->rear = ((*queue)->rear + 1) % (*queue)->capacity;
    }
    else {
        (*queue)->front = (0 <= (*queue)->front - 1) ? (*queue)->front - 1 : (*queue)->capacity - 1;
        (*queue)->data[(*queue)->front] = data;
    }
    (*queue)->size++;
}
QueueElement Dedeque(CircularQueueType* queue, Direction pos) {
    if (QueueIsEmpty(queue)) { printf(" Queue is empty.\n"); return 0; }
    QueueElement data;
    if (pos == Front) {
        data = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
    }
    else {
        queue->rear = (0 <= queue->rear - 1) ? queue->rear - 1 : queue->capacity - 1;
        data = queue->data[queue->rear];
    }
    queue->size--;
    return data;
}
