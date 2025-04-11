#include <stdio.h>
#include <stdlib.h>

typedef int DEQelement;
typedef struct doubly_list {
    DEQelement data;
    struct doubly_list* prev;
    struct doubly_list* next;
} DEQ;

//DEQ ���� �з�
enum statusDEQ {
    NORMAL,
    ONLY_HEADER,
    NOTHING_HEADER,
};

// ��� data ��� �Լ�
void printDEQ(DEQ* deq);
//DEQ �ʱ�ȭ �Լ� (��� ��� �����)
DEQ* initDEQ();
// DEQ ���� Ȯ�� �Լ�
int checkDEQ(DEQ* deq);
//DEQ �տ� ��� �߰�
DEQ* EnqueueHeadDEQ(DEQ* deq, DEQelement value);
//DEQ �ڿ� ��� �߰�
DEQ* EnqueueTailDEQ(DEQ* deq, DEQelement value);
//DEQ �տ� ��� ����
DEQ* DequeueHeadDEQ(DEQ* deq);
//DEQ �ڿ� ��� ����
DEQ* DequeueTailDEQ(DEQ* deq);
//DEQ ��� ã��
DEQ* findElementDEQ(DEQ* deq, DEQelement value);
//DEQ �ִ� ��� ã��
DEQ* findMaxDEQ(DEQ* deq);
//DEQ �ּ� ��� ã��
DEQ* findMinDEQ(DEQ* deq);
// (������ ��) ��� ��� ����
void clearDEQ(DEQ* deq);
// (������ ����) ��� ��� ����
void freeDEQ(DEQ* deq);

int main() {
    DEQ* deq1 = initDEQ();

    for (int i = 10; i <= 30; i += 10) {
        EnqueueHeadDEQ(deq1, i);
        printDEQ(deq1);
    }
    printf("MAX : %d, MIN : %d \n\n", findMaxDEQ(deq1)->data, findMinDEQ(deq1)->data);

    for (int i = 40; i <= 60; i += 10) {
        EnqueueTailDEQ(deq1, i);
        printDEQ(deq1);
    }
    printf("MAX : %d, MIN : %d \n\n", findMaxDEQ(deq1)->data, findMinDEQ(deq1)->data);

    DEQ* search1 = findElementDEQ(deq1, 5);
    if (search1 != NULL) printf("%d OK.\n", search1->data);
    else printf(" 5 FAIL.\n");
    DEQ* search2 = findElementDEQ(deq1, 10);
    if (search2 != NULL) printf("%d OK.\n", search2->data);
    else printf("10 FAIL.\n");
    DEQ* search3 = findElementDEQ(deq1, 15);
    if (search3 != NULL) printf("%d OK.\n", search3->data);
    else printf("15 FAIL.\n");
    DEQ* search4 = findElementDEQ(deq1, 20);
    if (search4 != NULL) printf("%d OK.\n", search4->data);
    else printf("20 FAIL.\n");

    for (int i = 0; i < 3; i++)
        DequeueHeadDEQ(deq1);
    DequeueTailDEQ(deq1);
    printDEQ(deq1);
    printf("MAX : %d, MIN : %d \n\n", findMaxDEQ(deq1)->data, findMinDEQ(deq1)->data);

    clearDEQ(deq1);
    printDEQ(deq1);

    freeDEQ(deq1);
}
// ��� data ��� �Լ�
void printDEQ(DEQ* deq) {
    printf("Header -> ");
    for (DEQ* pNode = deq->next; pNode != deq; pNode = pNode->next) {
        printf("[%3d] -> ", pNode->data);
    }
    printf("Header\n");
}
//DEQ �ʱ�ȭ �Լ� (��� ��� �����)
DEQ* initDEQ() {
    DEQ* header = (DEQ*)malloc(sizeof(DEQ));
    header->data = 0;
    header->next = header;
    header->prev = header;
    return header;
}
// DEQ ���� Ȯ�� �Լ�
int checkDEQ(DEQ* deq) {
    if (deq == NULL) return NOTHING_HEADER;
    else if (deq == deq->next) return ONLY_HEADER;
    else return NORMAL;
}
//DEQ �տ� ��� �߰�
DEQ* EnqueueHeadDEQ(DEQ* deq, DEQelement value) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    DEQ* newnode = (DEQ*)malloc(sizeof(DEQ));
    newnode->data = value;
    newnode->next = deq->next;
    newnode->prev = deq;
    deq->next->prev = newnode;
    deq->next = newnode;
    return deq;
}
//DEQ �ڿ� ��� �߰�
DEQ* EnqueueTailDEQ(DEQ* deq, DEQelement value) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    DEQ* newnode = (DEQ*)malloc(sizeof(DEQ));
    newnode->data = value;
    newnode->next = deq;
    newnode->prev = deq->prev;
    deq->prev->next = newnode;
    deq->prev = newnode;
    return deq;
}
//DEQ �տ� ��� ����
DEQ* DequeueHeadDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* deleteNode = deq->next;
    deq->next = deleteNode->next;
    deleteNode->next->prev = deq;
    free(deleteNode);
    return deq;
}
//DEQ �ڿ� ��� ����
DEQ* DequeueTailDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* deleteNode = deq->prev;
    deq->prev = deleteNode->prev;
    deleteNode->prev->next = deq;
    free(deleteNode);
    return deq;
}
//DEQ ��� ã��
DEQ* findElementDEQ(DEQ* deq, DEQelement value) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    for (DEQ* pNode = deq->next; pNode != deq; pNode = pNode->next) {
        if (value == pNode->data) {
            return pNode;
        }
    }
    return NULL;
}
//DEQ �ִ� ��� ã��
DEQ* findMaxDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* Max = deq->next;
    for (DEQ* pNode = deq->next; pNode != deq; pNode = pNode->next) {
        if (Max->data < pNode->data) {
            Max = pNode;
        }
    }
    return Max;
}
//DEQ �ּ� ��� ã��
DEQ* findMinDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* Min = deq->next;
    for (DEQ* pNode = deq->next; pNode != deq; pNode = pNode->next) {
        if (Min->data > pNode->data) {
            Min = pNode;
        }
    }
    return Min;
}
// (������ ��) ��� ��� ����
void clearDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    for (DEQ* pNode = deq->next; pNode != deq;) {
        DEQ* deleteNode = pNode;
        pNode = pNode->next;
        free(deleteNode);
    }
    deq->next = deq->prev = deq;
}
// (������ ����) ��� ��� ����
void freeDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return;
    clearDEQ(deq);
    free(deq);
}
