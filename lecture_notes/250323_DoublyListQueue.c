#include <stdio.h>
#include <stdlib.h>

typedef int DEQelement;
typedef struct doubly_list {
    DEQelement data;
    struct doubly_list* prev;
    struct doubly_list* next;
} DEQ;

//DEQ 상태 분류
enum statusDEQ {
    NORMAL,
    ONLY_HEADER,
    NOTHING_HEADER,
};

// 노드 data 출력 함수
void printDEQ(DEQ* deq);
//DEQ 초기화 함수 (헤더 노드 만들기)
DEQ* initDEQ();
// DEQ 상태 확인 함수
int checkDEQ(DEQ* deq);
//DEQ 앞에 노드 추가
DEQ* EnqueueHeadDEQ(DEQ* deq, DEQelement value);
//DEQ 뒤에 노드 추가
DEQ* EnqueueTailDEQ(DEQ* deq, DEQelement value);
//DEQ 앞에 노드 삭제
DEQ* DequeueHeadDEQ(DEQ* deq);
//DEQ 뒤에 노드 삭제
DEQ* DequeueTailDEQ(DEQ* deq);
//DEQ 노드 찾기
DEQ* findElementDEQ(DEQ* deq, DEQelement value);
//DEQ 최대 노드 찾기
DEQ* findMaxDEQ(DEQ* deq);
//DEQ 최소 노드 찾기
DEQ* findMinDEQ(DEQ* deq);
// (헤더노드 외) 모든 노드 제거
void clearDEQ(DEQ* deq);
// (헤더노드 포함) 모든 노드 제거
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
// 노드 data 출력 함수
void printDEQ(DEQ* deq) {
    printf("Header -> ");
    for (DEQ* pNode = deq->next; pNode != deq; pNode = pNode->next) {
        printf("[%3d] -> ", pNode->data);
    }
    printf("Header\n");
}
//DEQ 초기화 함수 (헤더 노드 만들기)
DEQ* initDEQ() {
    DEQ* header = (DEQ*)malloc(sizeof(DEQ));
    header->data = 0;
    header->next = header;
    header->prev = header;
    return header;
}
// DEQ 상태 확인 함수
int checkDEQ(DEQ* deq) {
    if (deq == NULL) return NOTHING_HEADER;
    else if (deq == deq->next) return ONLY_HEADER;
    else return NORMAL;
}
//DEQ 앞에 노드 추가
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
//DEQ 뒤에 노드 추가
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
//DEQ 앞에 노드 삭제
DEQ* DequeueHeadDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* deleteNode = deq->next;
    deq->next = deleteNode->next;
    deleteNode->next->prev = deq;
    free(deleteNode);
    return deq;
}
//DEQ 뒤에 노드 삭제
DEQ* DequeueTailDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return NULL;
    if (checkDEQ(deq) == ONLY_HEADER) return NULL;
    DEQ* deleteNode = deq->prev;
    deq->prev = deleteNode->prev;
    deleteNode->prev->next = deq;
    free(deleteNode);
    return deq;
}
//DEQ 노드 찾기
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
//DEQ 최대 노드 찾기
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
//DEQ 최소 노드 찾기
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
// (헤더노드 외) 모든 노드 제거
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
// (헤더노드 포함) 모든 노드 제거
void freeDEQ(DEQ* deq) {
    if (checkDEQ(deq) == NOTHING_HEADER) return;
    clearDEQ(deq);
    free(deq);
}
