#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <crtdbg.h>

// �ܼ� ���� ����Ʈ ���� ����� ����Լ��� �ۼ�

void checkLeak() {
    // �޸� ���� ���� ���
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    // ���α׷� ����� ���� üũ
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

typedef int list_element;
typedef struct ListNode {
    list_element data;
    struct ListNode* link;
} ListNode;

// ��� �� �� ����
ListNode* insert_first(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = head;
    return NewNode;
}

// ����Ʈ ���
void print_list(ListNode* head) {
    printf(" list -> ");
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf("NULL \n");
}

//��� �Լ��� ����Ʈ �޸� ���� �ۼ� 
ListNode* freelist(ListNode* head) {
    //// ���� ����
    //// �ƴϸ� if (!head) �ᵵ ��.
    //// �ƴϸ� ��� ���� ���� �Ƚᵵ �ݺ� ���Ǹ����ε� �����.
    //if (head == NULL) return NULL;

    //// �ݺ� ����
    ////�ƴϸ� if(head)����if(head!=NULL)�Ρ��ص���.
    //freelist(head->link);
    //free(head);

    // ---------------------
    // �տ������� ����� �ݺ� ����
    if (head) {
        ListNode* next = head->link;
        free(head);
        freelist(next);
    }

    return NULL;
}

int main() {
    checkLeak();
    ListNode* list_head1 = NULL;
    for (int i = 0; i < 110; i += 10) {
        list_head1 = insert_first(list_head1, i);
        printf("list 1");
        print_list(list_head1);
    }
    list_head1 = freelist(list_head1);
    return 0;
}
