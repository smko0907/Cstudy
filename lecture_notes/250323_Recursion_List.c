#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <crtdbg.h>

// 단순 연결 리스트 삭제 기능을 재귀함수로 작성

void checkLeak() {
    // 메모리 누수 내역 출력
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    // 프로그램 종료시 누수 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

typedef int list_element;
typedef struct ListNode {
    list_element data;
    struct ListNode* link;
} ListNode;

// 노드 맨 앞 생성
ListNode* insert_first(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("새 노드 동적 할당 실패!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = head;
    return NewNode;
}

// 리스트 출력
void print_list(ListNode* head) {
    printf(" list -> ");
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf("NULL \n");
}

//재귀 함수로 리스트 메모리 해제 작성 
ListNode* freelist(ListNode* head) {
    //// 종단 조건
    //// 아니면 if (!head) 써도 됨.
    //// 아니면 사실 종단 조건 안써도 반복 조건만으로도 충분함.
    //if (head == NULL) return NULL;

    //// 반복 조건
    ////아니면 if(head)나　if(head!=NULL)로　해도됨.
    //freelist(head->link);
    //free(head);

    // ---------------------
    // 앞에서부터 지우는 반복 조건
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
