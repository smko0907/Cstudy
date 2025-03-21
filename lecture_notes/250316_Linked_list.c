#include <stdio.h>
#include <stdlib.h>
#include <Memory Leak.h>

// list 구조체 (구성 요소)
typedef int list_element;
typedef struct ListNode{
    list_element data;
    struct ListNode* link
} ListNode;

ListNode* insertFront(ListNode* head, list_element value) {
    ListNode* NewNode = malloc(sizeof(ListNode)); //ListNode NewNode;
    NewNode -> data = value; //n1.data = 9;
    NewNode -> link = head; //n1.link = list1; // NULL;
    // head = NewNode; //list1 = &n1;
    return NewNode;
}

ListNode* insertBack(ListNode* head, list_element value){
    ListNode* NewNode = malloc(sizeof(ListNode));
    NewNode->data = value;
    NewNode->link = NULL;
    // node == 0
    if(head == NULL) return NewNode;
    ListNode* findNode = head;
    while (findNode->link != NULL)
        findNode = findNode->link;
    findNode->link = NewNode;
    return head;
}

ListNode* removeFront(ListNode* head){
    if (head == NULL) return NULL;
    ListNode* remove = head;
    head = head->link;
    free(remove);
    return head;
}

ListNode* removeBack(ListNode* head){
    if (head == NULL) return NULL;
    ListNode* prev = head;
    if (prev->link == NULL){
        free(head);
        return NULL;
    }
    while (prev->link->link != NULL)
        prev = prev->link;
    free(prev->link);
    prev->link = NULL;
    return head;
}

void printList(ListNode* head){
    for(ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        printf("[%3d] -> ", pNode->data);
    printf("NULL\n\n");
}

ListNode* concat(ListNode* head1, ListNode* head2){
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    ListNode* Back = head1;
    while (Back->link != NULL)
        Back = Back->link;
    Back->link = head2;
    return head1;
}

ListNode* freeList(ListNode* head) {
    while (head/* != NULL*/) {
        //ListNode* remove = head;
        //head = head->link;
        //free(remove);
        head = removeFront(head);
    }
    return NULL;
}

int main(){
    checkLeak();
    // 9 약수 리스트 만들기
    ListNode* list1 = NULL;
    for (int i = 1; i <= 12; i++)
        if (12 % i == 0)
            list1 = insertBack(list1, i);

    ListNode* list2 = NULL;
    for (int i = 1; i <= 66; i++)
        if (66 % i == 0)
            list2 = insertBack(list2, i);


    // list1 = insertFront(list1, 9);
    // list1 = insertFront(list1, 3);
    // list1 = insertFront(list1, 1);

    // ListNode n1;
    // n1.data = 9;
    // n1.link = list1; //NULL;
    // list1 = &n1;

    // ListNode n2;
    // n2.data = 3;
    // n2.link = list1; // &n1;
    // list1 = &n2;

    // ListNode n3;
    // n3.data = 1;
    // n3.link = list1; //&n2;
    // list1 = &n3;
    
    // printList(list1);
    // list1 = removeFront(list1);
    // printList(list1);
    // list1 = removeBack(list1);
    // printList(list1);
    // list1 = reverse(list1);

    printList(list1);
    printList(list2);

    list1 = concat(list1, list2);
    printList(list1);

    // for (ListNode* pNode = list1; pNode != NULL; pNode = pNode->link)
    //     printf("[%3d] -> ", pNode -> data);
    // print("\n\n");


}