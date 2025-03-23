#include <stdio.h>
#include <stdlib.h>
#include "Memory Leak.h"

//Double list ����ü ( ���� ��� )
typedef int DoubleListElement;
typedef struct DoubleListNode {
    DoubleListElement data;
    struct DoubleListNode* Llink;
    struct DoubleListNode* Rlink;
} DoubleListNode;

//���� ���� ����Ʈ(Doubly Linked List) ADT
DoubleListNode* DoubleInitial(); // �ʱ�ȭ (��� ��� ����)
// ��� ����
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item);
DoubleListNode* DoubleInsertLast(DoubleListNode* head, DoubleListElement item);
// ��� ���� 
DoubleListNode* DoubleDeleteFirst(DoubleListNode* head);
DoubleListNode* DoubleDeleteLast(DoubleListNode* head);
//����Ʈ ���� list1 + list2
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);
void DoubleDisplay(DoubleListNode* head); // ����Ʈ ������ ���
void DoubleDisplayReverse(DoubleListNode* head); // ����Ʈ ������ ���
void FreeDoubleList(DoubleListNode* head); // ����Ʈ ��ü ����


int main() {
    checkLeak();
    DoubleListNode* list1 = DoubleInitial();
    DoubleInsertFirst(list1, 9); // ��� �߰�
    DoubleInsertFirst(list1, 3);
    DoubleInsertFirst(list1, 1);

    DoubleListNode* list2 = DoubleInitial();
    DoubleInsertLast(list2, 10);
    DoubleInsertLast(list2, 20);
    DoubleInsertLast(list2, 30);

    //DoubleDeleteFirst(list1); //1 ����
    //DoubleDeleteFirst(list1); //3 ����
    //DoubleDeleteFirst(list1); //9 ����

    //DoubleDeleteLast(list2); //30 ����
    //DoubleDeleteLast(list2); //20 ����
    //DoubleDeleteLast(list2); //10 ����


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
    NewNode->data = item; // ���� �޸� �Ҵ�޾� item ����
    //if (head == head->Rlink) {
    //    NewNode->Rlink = head;
    //    NewNode->Llink = head;
    //    head->Rlink = NewNode;
    //    head->Llink = NewNode;
    //}
    //else { //if ���ǹ� ���� ����� �ð����⵵ O(1)
        NewNode->Llink = head;
        NewNode->Rlink = head->Rlink; //NewNode�� ���� ��带 ����Ű�� ����
        head->Rlink->Llink = NewNode; 
        head->Rlink = NewNode;
    //}
    return head;
}

DoubleListNode* DoubleInsertLast(DoubleListNode* head, DoubleListElement item) {
    DoubleListNode* NewNode = malloc(sizeof(DoubleListNode));
    NewNode->data = item;
    // �ܼ� ���� ����Ʈ�� �޸� ���� ���� ����Ʈ��
    // InsertLast�� �ð����⵵�鿡�� O(1)
    NewNode->Llink = head->Llink;
    NewNode->Rlink = head;
    head->Llink->Rlink = NewNode;
    head->Llink = NewNode;
    head->data++;
    return head;
}

DoubleListNode* DoubleDeleteFirst(DoubleListNode* head){
    //header node�� �ִٸ�
    if (head == head->Rlink) return head;
    //������ ����� �ִٸ�
    DoubleListNode* remove = head->Rlink;
    remove->Llink->Rlink = remove->Rlink; // node2 link -> header node
    remove->Rlink->Llink = remove->Llink;
    free(remove);
    //�ð����⵵ O(1)
    return head;
}

DoubleListNode* DoubleDeleteLast(DoubleListNode* head) {
    //�ð����⵵ O(1)
    if (head == head->Rlink) return head;
    DoubleListNode* remove = head->Llink;
    remove->Llink->Rlink = remove->Rlink;
    remove->Rlink->Llink = remove->Llink;
    free(remove);
    return head;
}

DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {
    // head1�� ������ ��带 head2 node1 ���� ����
    // head2 ������ ��带 head1 ���� ����. head2�� �ڱ��ڽ� ����Ű��
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
    // ������ ���
    for (DoubleListNode* p = head->Rlink; p != head; p = p->Rlink)
        printf("<- %3d ->", p->data);
    printf("\n\n");
}

void DoubleDisplayReverse(DoubleListNode* head) {
    // ������ ���
    for (DoubleListNode* p = head->Llink; p != head; p = p->Llink)
        printf("<- %3d ->", p->data);
    printf("\n\n");
}

void FreeDoubleList(DoubleListNode* head) {
    while (head->Rlink != head) // head�� �ڱ��ڽ��� �ƴ϶�� �� ��尡 �ִٸ� ����
        DoubleDeleteFirst(head);
    free(head);
}