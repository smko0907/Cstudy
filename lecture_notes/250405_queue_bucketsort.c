#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}

typedef int QueueElement;
typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;
typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;
LinkedQueueType* QueueInit();// Queue �ʱ�ȭ
int QueueIsEmpty(LinkedQueueType* queue);// Queue�� Node�� ������ Ȯ��
void Enqueue(LinkedQueueType* queue, QueueElement data);// Queue Node ����
QueueElement Dequeue(LinkedQueueType* queue);// Queue Node ����
void PrintQueue(LinkedQueueType* queue);// Queue Node ���
void FreeQueue(LinkedQueueType* queue);// Queue ����

void display(int* arr, int size) {
    for (int i = 0; i < size; i++) printf("%5d ", arr[i]);
    printf("\n");
}
void display_sort(int* arr, int st, int end) {
    for (int i = 0; i < st; i++) printf("      ");
    for (int i = st; i <= end; i++) printf("%5d ", arr[i]);
    printf("\n");
}
int* randomize(int size) {
    int* pArr = (int*)calloc(size, sizeof(int)); //���� �Ҵ�, �� 0 �ʱ�ȭ
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) pArr[i] = rand() % 1000;
    return pArr;
}
void merge(int* arr, int* temp, int st, int mid, int end) {
    for (int i = st; i <= end; i++)  temp[i] = arr[i];
    int Left = st, Right = mid + 1, Sort = st;
    while (Left <= mid && Right <= end) {
        if (temp[Left] < temp[Right]) arr[Sort++] = temp[Left++];
        else arr[Sort++] = temp[Right++];
    }
    while (Left <= mid) arr[Sort++] = temp[Left++];
    while (Right <= end) arr[Sort++] = temp[Right++];
}
void divide(int* arr, int* temp, int st, int end) {
    if (st < end) {
        int mid = (st + end) / 2;
        divide(arr, temp, st, mid);
        divide(arr, temp, mid + 1, end);
        merge(arr, temp, st, mid, end);
        display_sort(arr, st, end);
    }
}
void mergeSort(int* arr, int size) {
    int* temp = (int*)malloc(sizeof(int) * size);
    divide(arr, temp, 0, size - 1);
    free(temp);
}
void quick(int* arr, int st, int end) {
    int left = st, right = end, pivot = arr[(st + end) / 2];
    while (left <= right) {
        while (arr[left] < pivot)  left++;
        while (pivot < arr[right])  right--;
        if (left <= right) {
            swap(int, arr[left], arr[right]);
            left++;
            right--;
        }
    }
    display_sort(arr, st, end);
    if (st < right) quick(arr, st, right);
    if (left < end)  quick(arr, left, end);
}
void bucket(int* arr, int size) {
    int Max = arr[0];
    for (int i = 0; i < size; i++)
        if (Max < arr[i]) Max = arr[i];
    int* count = (int*)calloc(Max + 1, sizeof(int));
    for (int i = 0; i < size; i++) count[arr[i]]++;
    for (int i = 0, j = 0; i < size; i++) {
        while (count[j] == 0) j++;
        count[j]--;
        arr[i] = j;
    }
    free(count);
}
void bucket_queue(int* arr, int size) {
    int digit = 0; // �ڸ��� == �ݺ�Ƚ��
    for (int i = 0; i < size; i++)
        while (arr[i] / (int)pow(10, digit))
            digit++; // �ڸ��� ����

    LinkedQueueType* Qbucket[10];

    for (int i = 0; i < 10; i++)
        Qbucket[i] = QueueInit();

    for (int repeat = 0; repeat < digit; repeat++) {

        for (int i = 0; i < size; i++)
            Enqueue(Qbucket[(arr[i] / (int)pow(10, repeat)) % 10], arr[i]);

        for (int i = 0, j = 0; i < size; i++) {
            while (QueueIsEmpty(Qbucket[j]))j++;
            arr[i] = Dequeue(Qbucket[j]);
        }
        display(arr, size);
    }

    for (int i = 0; i < 10; i++)
        FreeQueue(Qbucket[i]);
}
int main() {
    int size, * arr = NULL;
    printf("�迭 ũ�� �Է� : ");
    scanf("%d", &size);
    arr = randomize(size);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    mergeSort(arr, size);
    //quick(arr, 0, size - 1);
    //bucket(arr, size);
    //bucket_queue(arr, size);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    free(arr); //���� �޸� ����
}

LinkedQueueType* QueueInit() {
    LinkedQueueType* newqueue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));
    if (newqueue == NULL) exit(1);
    newqueue->front = newqueue->rear = NULL;
    return newqueue;
}
int QueueIsEmpty(LinkedQueueType* queue) { return (queue->front == NULL); }
void Enqueue(LinkedQueueType* queue, QueueElement data) {
    QueueNode* NewNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (NewNode == NULL) { printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); }
    NewNode->data = data;
    NewNode->link = NULL;
    if (QueueIsEmpty(queue)) {//��尡 ���� ���
        queue->front = NewNode;
        queue->rear = NewNode;
    }
    else {//��� 1�� �̻�
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
    printf(" Queue -> ");
    for (QueueNode* pNode = queue->front; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf(" NULL\n\n");
}
void FreeQueue(LinkedQueueType* queue) {
    for (QueueNode* pNode = queue->front; pNode != NULL; ) {
        QueueNode* DeleteNode = pNode;
        pNode = pNode->link;
        free(DeleteNode);
    }
    free(queue);
}
