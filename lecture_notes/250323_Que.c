#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

//Queue ����ü ( ���� ��� )
typedef int QueueElement;
typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;
typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;

//Queue ADT
LinkedQueueType* QueueInit(); //�ʱ�ȭ
int QueueIsEmpty(LinkedQueueType* queue);  //Node�� ������ Ȯ��
void Enqueue(LinkedQueueType* queue, QueueElement data);//Node ����
QueueElement Dequeue(LinkedQueueType* queue);// Node�� �ڷ� ������
void PrintQueue(LinkedQueueType* queue);// Node ���
void FreeQueue(LinkedQueueType* queue); //Queue ����

//Deque ���� & ���� ��ġ ǥ��
typedef enum direction {
    Rear,
    Front
}Direction;

// Deque ADT [ Direction pos: Front(1) & Rear (0) ����]
void Endeque(LinkedQueueType* queue, QueueElement data, Direction pose);
QueueElement Dedeque(LinkedQueueType* queue, Direction pos);


int main() {
    checkLeak();
    LinkedQueueType* Q = QueueInit();

    Enqueue(Q, 9);
    Enqueue(Q, 3);
    Enqueue(Q, 1);

    printf("Dequeue: %d\n\n", Dequeue(Q));

    Endeque(Q, 77, Front);
    Endeque(Q, 77, Rear);

    PrintQueue(Q);

    FreeQueue(Q);
}

LinkedQueueType* QueueInit() {
    LinkedQueueType* NewQueue = malloc(sizeof(LinkedQueueType));
    NewQueue->front = NULL;
    NewQueue->rear = NULL;
    return NewQueue;
}

int QueueIsEmpty(LinkedQueueType* queue) {
    if (queue->front == NULL && queue->rear == NULL) return 1;
    else return 0;
}

void Enqueue(LinkedQueueType* queue, QueueElement data) {
    QueueNode* NewNode = malloc(sizeof(QueueNode));
    NewNode->data = data;
    NewNode->link = NULL;
    // ���ο� node�� ������
    if (QueueIsEmpty(queue)) {
        queue->front = NewNode;
        queue->rear = NewNode;
    }
    // node�� ������. node >= 1
    else {
        queue->rear->link = NewNode;
        queue->rear = NewNode;
    }
}

QueueElement Dequeue(LinkedQueueType* queue) {
    if (QueueIsEmpty(queue)) { printf(" Queue is empty.\n"); return 0; }
    QueueNode* DeleteNode = queue->front;
    QueueElement data = DeleteNode->data;
    queue->front = queue->front->link;
    if (queue->front == NULL) //��尡 1���� ���
        queue->rear = NULL;
    free(DeleteNode);
    return data;
}

void PrintQueue(LinkedQueueType* queue) {
    for (QueueNode* p = queue->front; p; p = p->link)
        printf("[%3d] -> ", p->data);
    printf("NULL \n\n");
}

void FreeQueue(LinkedQueueType* queue) {
    while (!QueueIsEmpty(queue))
        Dequeue(queue);
    free(queue);
}

void Endeque(LinkedQueueType* queue, QueueElement data, Direction pose) {
    QueueNode* NewNode = malloc(sizeof(QueueNode));
    NewNode->data = data;
    NewNode->link = NULL;
    // Node == 0
    if (QueueIsEmpty(Queue)) {
        queue->front = NewNode;
        queue->rear = NewNode;
    }
    // pos == Front
    else if (pos == Front) {
        NewNode->link = queue->front;
        queue->front = NewNode;
    }

    // pose == Rear
    else if (pos == Rear) {
        queue->rear->link = NewNode;
        queue->rear = NewNode;
    }
}

