#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

//Double list 구조체 ( 구성 요소 )
typedef int DoubleListElement;
typedef struct DoubleListNode {
    DoubleListElement data;
    struct DoubleListNode* Llink;
    struct DoubleListNode* Rlink;
} DoubleListNode;

//이중 연결 리스트(Doubly Linked List) ADT
DoubleListNode* DoubleInitial(); // 초기화 (헤더 노드 생성)
// 노드 생성
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item);
DoubleListNode* DoubleInsertLast(DoubleListNode* head, DoubleListElement item);
// 노드 삭제 
DoubleListNode* DoubleDeleteFirst(DoubleListNode* head);
DoubleListNode* DoubleDeleteLast(DoubleListNode* head);
//리스트 결합 list1 + list2
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);
void DoubleDisplay(DoubleListNode* head); // 리스트 정방향 출력
void DoubleDisplayReverse(DoubleListNode* head); // 리스트 역방향 출력
void FreeDoubleList(DoubleListNode* head); // 리스트 전체 삭제


int main() {
    checkLeak();
    DoubleListNode* list1 = DoubleInitial();
    DoubleInsertFirst(list1, 9); // 노드 추가
    DoubleInsertFirst(list1, 3);
    DoubleInsertFirst(list1, 1);

    DoubleListNode* list2 = DoubleInitial();
    DoubleInsertLast(list2, 10);
    DoubleInsertLast(list2, 20);
    DoubleInsertLast(list2, 30);

    //DoubleDeleteFirst(list1); //1 삭제
    //DoubleDeleteFirst(list1); //3 삭제
    //DoubleDeleteFirst(list1); //9 삭제

    //DoubleDeleteLast(list2); //30 삭제
    //DoubleDeleteLast(list2); //20 삭제
    //DoubleDeleteLast(list2); //10 삭제


    DoubleConcat(list1, list2);

    DoubleDisplay(list1);
    DoubleDisplayReverse(list1);

    FreeDoubleList(list1);
    FreeDoubleList(list2);
}

DoubleListNode* DoubleInitial() {
    DoubleListNode* HEADER = malloc(sizeof(DoubleListNode));
    HEADER->Rlink = HEADER;
    HEADER->Llink = HEADER;
    HEADER->data = 0;
    return HEADER;
}

DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item) {
    DoubleListNode* NewNode = malloc(sizeof(DoubleListNode));
    NewNode->data = item; // 새로 메모리 할당받아 item 저장
    //if (head == head->Rlink) {
    //    NewNode->Rlink = head;
    //    NewNode->Llink = head;
    //    head->Rlink = NewNode;
    //    head->Llink = NewNode;
    //}
    //else { //if 조건문 없이 실행시 시간복잡도 O(1)
        NewNode->Llink = head;
        NewNode->Rlink = head->Rlink; //NewNode가 다음 노드를 가르키고 있음
        head->Rlink->Llink = NewNode; 
        head->Rlink = NewNode;
    //}
    return head;
}

DoubleListNode* DoubleInsertLast(DoubleListNode* head, DoubleListElement item) {
    DoubleListNode* NewNode = malloc(sizeof(DoubleListNode));
    NewNode->data = item;
    // 단순 연결 리스트와 달리 이중 연결 리스트는
    // InsertLast도 시간복잡도면에서 O(1)
    NewNode->Llink = head->Llink;
    NewNode->Rlink = head;
    head->Llink->Rlink = NewNode;
    head->Llink = NewNode;
    head->data++;
    return head;
}

DoubleListNode* DoubleDeleteFirst(DoubleListNode* head){
    //header node만 있다면
    if (head == head->Rlink) return head;
    //삭제할 대상이 있다면
    DoubleListNode* remove = head->Rlink;
    remove->Llink->Rlink = remove->Rlink; // node2 link -> header node
    remove->Rlink->Llink = remove->Llink;
    free(remove);
    //시간복잡도 O(1)
    return head;
}

DoubleListNode* DoubleDeleteLast(DoubleListNode* head) {
    //시간복잡도 O(1)
    if (head == head->Rlink) return head;
    DoubleListNode* remove = head->Llink;
    remove->Llink->Rlink = remove->Rlink;
    remove->Rlink->Llink = remove->Llink;
    free(remove);
    return head;
}

DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {
    // head1의 마지막 노드를 head2 node1 노드와 연결
    // head2 마지막 노드를 head1 노드와 연결. head2는 자기자신 가르키게
    DoubleListNode* head1Tail = head1->Llink;
    DoubleListNode* head2Front = head2->Rlink;
    DoubleListNode* head2Tail = head2->Llink;

    // head1Tail & head2Front
    head1Tail->Rlink = head2Front;
    head2Front->Llink = head1Tail;

    // head1 & head2Tail
    head2Tail->Rlink = head1;
    head1->Llink = head2Tail;

    // head2 init
    head2->Llink = head2;
    head2->Rlink = head2;

    return head1;
}


void DoubleDisplay(DoubleListNode* head) {
    // 정방향 출력
    for (DoubleListNode* p = head->Rlink; p != head; p = p->Rlink)
        printf("<- %3d ->", p->data);
    printf("\n\n");
}

void DoubleDisplayReverse(DoubleListNode* head) {
    // 역방향 출력
    for (DoubleListNode* p = head->Llink; p != head; p = p->Llink)
        printf("<- %3d ->", p->data);
    printf("\n\n");
}

void FreeDoubleList(DoubleListNode* head) {
    while (head->Rlink != head) // head가 자기자신이 아니라면 즉 노드가 있다면 삭제
        DoubleDeleteFirst(head);
    free(head);
}